#include"optimizer.h"
#define OPTIMIZER
#ifdef OPTIMIZER
#define odebug(...) printf(__VA_ARGS__)
#else
#define odebug(...) assert(1)
#endif
#define TODO assert(0);
#define MAX_BLOCK_NUM 400
BasicBlock* bb;//存放基本块指针的数组
int blocknum = 0;//基本块数量
FILE *f;
//指定BasicBlock中插入新的一条Intercode
InterCode AddInterCode(BasicBlock block,int codekind,Operand op0,Operand op1,Operand op2){//往一个basicblock中插入一行中间代码
    InterCode head = block->codehead;
    InterCode tail = block->codetail;
    InterCode newcode = (InterCode) malloc(sizeof(struct InterCode_));
    newcode->kind = codekind;
    if(op0!=NULL)newcode->op[0] = op0;
    if(op1!=NULL)newcode->op[1] = op1;
    if(op2!=NULL)newcode->op[2] = op2;
    newcode->next = NULL;
    if(head == NULL){
        newcode->prev = NULL;
        head = newcode;
        tail = head;
    }
    else{
        tail->next = newcode;
        newcode->prev = tail;
        tail = newcode;
    }
    return newcode;
}
//makeop 利用变量名的特性根据名字得到op
Operand makeop(char *name){
    assert(name!=NULL);
    int opdebug = 1;
    if(opdebug)odebug("In opdebug: name = %s\n",name);
    Operand op = (Operand)malloc(sizeof(Operand_d));
    char *s;
    switch(name[0]){
        case 't':
            op->kind=TMPVAR_OP;
            sscanf(name,"t%d",&op->u.no);
            break;
        case 'v':
            op->kind=VARIABLE_OP;
            sscanf(name,"v%d",&op->u.no);
            break;
        case '&':
            op->kind=GETADDR_OP;
            sscanf(name,"&%s",s);
            op->u.op = makeop(s);
            break;
        case '*':
            op->kind=GETVAL_OP;
            sscanf(name,"*%s",s);
            op->u.op = makeop(s);
            break;
        case '#':
            op->kind=CONSTANT_OP;
            sscanf(name,"#%d",&op->u.value);
            break;
        default:
            assert(0);
    }
    return op;
}
void readinput(char* filename){
//输入模块读取输入文件信息到数据结构
    odebug("-----Read Input Begin-----\n");
    int rdebug = 1;
    char buf[500];//读取一行
    //一个获取要开辟多大的基本块数组的trick：先遍历一遍代码看看有多少goto、return，这些是结尾，所以数量不超过这个值
    f = fopen(filename, "r");
    if (!f){
        printf("cannot open file : %s\n",filename);
        return;
    }
    while(fgets(buf,500,f)!=NULL){//读入一行到buf
        if(buf[0]=='G'||buf[0]=='L'||buf[0]=='I'||buf[0]=='C'||buf[0]=='R'&&buf[2]=='T')blocknum++;
    }
    fclose(f);
    if(rdebug)odebug("guess blocknum:%d\n",blocknum);
    //下面正式读入
    bb = (BasicBlock*)malloc(sizeof(BasicBlock)*blocknum*2);//申请bb数组空间
    int linenum = 0;//记录行数
    int blockno = 0;//记录块序号
    BasicBlock curb = NULL;//当前块的指针
    f = fopen(filename, "r");
    while(fgets(buf,500,f)!=NULL){//读入一行到buf
        linenum++;
        if(rdebug)odebug("Line %d : %s\n",linenum,buf);
        int linelen = strlen(buf);//长度
        //每次都先申请好待用的op避免冗余代码
        Operand op0 = (Operand)malloc(sizeof(Operand_d));
        Operand op1 = (Operand)malloc(sizeof(Operand_d));
        Operand op2 = (Operand)malloc(sizeof(Operand_d));
        //如果当前块为空,或者是label就新增一个
        if(curb==NULL||buf[0]=='L'){
            //if(rdebug)odebug(" (new bb) ");
            curb = (BasicBlock)malloc(sizeof(BasicBlock_d));
            bb[blockno]=curb;//记录到数组里,编号从0开始
            curb->no = blockno;
            curb->codehead=NULL;
            curb->codetail=NULL;
            curb->prev=NULL;
            curb->next[0]=NULL;
            curb->next[1]=NULL;
            blockno++;
        }
        //下面对该行解析出指令内容
        if(buf[0]=='\n'){//空行
            if(rdebug)odebug("null\n");
            continue;
        }
        else if (buf[0]=='F'){//新函数=>新基本块
            if(rdebug)odebug("function: \n");
            op0->kind = FUNC_OP;
            sscanf(buf, "FUNCTION %s :\n", op0->u.name);
            assert(op0->u.name!=NULL);
            AddInterCode(curb,FUNC_IR,op0,NULL,NULL);
        }
        else if (buf[0]=='L'){//新标签=>新基本块
            if(rdebug)odebug("new label\n");
            op0->kind = LABEL_OP;
            sscanf(buf, "LABEL label%d :", &op0->u.no);
            AddInterCode(curb,LABEL_IR,op0,NULL,NULL);
        }
        else if (buf[0]=='G'){//GOTO=>基本块末尾
            if(rdebug)odebug("GOTO\n");
            op0->kind = LABEL_OP;
            sscanf(buf, "GOTO label%d", &op0->u.no);
            AddInterCode(curb,GOTO_IR,op0,NULL,NULL);
            curb=NULL;
        }
        else if (buf[0]=='I'){//IF_GOTO=>基本块末尾
            if(rdebug)odebug("IF_GOTO\n");
            op0->kind = LABEL_OP;
            char *s1;
            char *s2;
            char *s3;
            sscanf(buf, "IF %s %s %s GOTO label%d",s1,s2,s3,&op0->u.no);
            InterCode newcode = AddInterCode(curb,IFGOTO_IR,op0,makeop(s1),makeop(s2));
            newcode->e.relop = s3;
            curb=NULL;
        }
        else if (buf[0]=='R'&&buf[2]=='T'){//RETURN=>基本块末尾
            if(rdebug)odebug("RETURN\n");
            char *s;
            sscanf(buf,"RETURN %s",s);
            op0 = makeop(s);
            AddInterCode(curb,RETURN_IR,op0,NULL,NULL);
            curb = NULL;
        }
        else if (buf[0]=='D'){//DEC
            if(rdebug)odebug("DEC\n");
            char *s;
            int size;
            sscanf(buf,"DEC %s %d",s,&size);
            op0 = makeop(s);
            InterCode newcode = AddInterCode(curb,DEC_IR,op0,NULL,NULL);
            newcode->e.decsize = size;
        }
        else if (buf[0]=='A'){//ARG
            if(rdebug)odebug("ARG\n");
            char *s;
            sscanf(buf,"ARG %s",s);
            op0 = makeop(s);
            AddInterCode(curb,ARG_IR,op0,NULL,NULL);
        }
        else if (buf[0]=='P'){//PARAM
            if(rdebug)odebug("PARAM\n");
            char *s;
            sscanf(buf,"PARAM %s",s);
            op0 = makeop(s);
            AddInterCode(curb,PARAM_IR,op0,NULL,NULL);
        }
        else if (buf[0]=='C'){//CALL在开头？？
            if(rdebug)odebug("CALL\n");
            TODO
        }
        else if (buf[0]=='R'&&buf[2]=='A'){//READ
            if(rdebug)odebug("READ\n");
            char *s;
            sscanf(buf,"READ %s",s);
            op0 = makeop(s);
            AddInterCode(curb,READ_IR,op0,NULL,NULL);
        }
        else if (buf[0]=='W'){//WRITE
            if(rdebug)odebug("WRITE\n");
            char *s;
            sscanf(buf,"WRITE %s",s);
            op0 = makeop(s);
            AddInterCode(curb,WRITE_IR,op0,NULL,NULL);
        }
        else if (buf[0]=='v'||buf[0]=='t'||buf[0]=='*'||buf[0]=='&'){//
            if(rdebug)odebug("ASSIGN...\n");
            char *s1,*s2,*s3;
            int kind = ASSIGN_IR;//默认就是ass
            for(int i = 0;i<linelen;i++){
                if(buf[i]=='+'){
                    kind = ADD_IR;
                    sscanf(buf,"%s := %s + %s",s1,s2,s3);
                    AddInterCode(curb,ADD_IR,makeop(s1),makeop(s2),makeop(s3));
                    break;
                }
                else if(buf[i]=='-'){
                    kind = SUB_IR;
                    sscanf(buf,"%s := %s - %s",s1,s2,s3);
                    AddInterCode(curb,SUB_IR,makeop(s1),makeop(s2),makeop(s3));
                    break;
                }
                else if(buf[i]=='*'&&buf[i+1]==' '){
                    kind = MUL_IR;
                    sscanf(buf,"%s := %s * %s",s1,s2,s3);
                    AddInterCode(curb,MUL_IR,makeop(s1),makeop(s2),makeop(s3));
                    break;
                }
                else if(buf[i]=='/'){
                    kind = DIV_IR;
                    sscanf(buf,"%s := %s / %s",s1,s2,s3);
                    AddInterCode(curb,DIV_IR,makeop(s1),makeop(s2),makeop(s3));
                    break;
                }
                else if(buf[i]=='C'){
                    kind = CALL_IR;
                    sscanf(buf,"%s := CALL %s",s1,s2);
                    op1->kind=FUNC_OP;
                    op1->u.name = s2;
                    AddInterCode(curb,CALL_IR,makeop(s1),op1,NULL);
                    break;
                }
            }
            if(kind == ASSIGN_IR){
                sscanf(buf,"%s := %s",s1,s2);
                AddInterCode(curb,ASSIGN_IR,makeop(s1),makeop(s2),NULL);
            }
        }
        else{
            if(rdebug)odebug("wrong type in line:%d",linenum);
            assert(0);
        }
    }
    fclose(f);
    blocknum = blockno;//真正的块数量
    odebug("-----Read Input Finished!-----\n");
}
void optimize(){
//优化模块主函数
    odebug("-----Optimize Begin-----\n");
    odebug("-----Optimize Finished!-----\n");
}
void PrintOperand(Operand op){
    char* s;int var;
    int opdebug =0;
    switch(op->kind){
        case VARIABLE_OP://用户定义变量名
            if(opdebug)odebug("Print OP VARIABLE\n");
            fprintf(f,"v%d",op->u.no);
            break;
        case TMPVAR_OP://临时变量名，标签名
            if(opdebug)odebug("Print OP TMPVAR\n");
            fprintf(f,"t%d",op->u.no);
            break;
        case CONSTANT_OP://常量
            if(opdebug)odebug("Print OP CONSTANT\n");
            fprintf(f,"#%d",op->u.value);
            break;
        case GETADDR_OP://取地址
            if(opdebug)odebug("Print OP GETADDR_OP\n");
            fprintf(f,"&");
            PrintOperand(op->u.op);
            break;
        case LABEL_OP://解引用
            if(opdebug)odebug("Print OP LABEL_OP\n");
            fprintf(f,"label%d",op->u.no);
            break;
        case GETVAL_OP://解引用
            if(opdebug)odebug("Print OP GETVAL_OP\n");
            fprintf(f,"*");
            PrintOperand(op->u.op);
            break;
        case FUNC_OP://函数名
            if(opdebug)odebug("Print OP FUNCOP\n");
            fprintf(f,"t%s",op->u.name);
            break;
        default:
            printf("Error in PrintOperand:wrong type\n");
            assert(0);
    }
}
void PrintInterCode(InterCode head){
    int pdebug = 0;
    InterCode i = NULL;
    if(head != NULL){i = head;}//遍历链表的结构体指针
    while(i!=NULL){
        switch(i->kind){
            case LABEL_IR:
                if(pdebug)odebug("Print LABEL_IR\n");
                fprintf(f,"LABEL ");
                PrintOperand(i->op[0]);
                fprintf(f," :\n");
                break;
            case FUNC_IR:
                fprintf(f,"\n");
                if(pdebug)odebug("Print FUNC _IR\n");
                fprintf(f,"FUNCTION ");
                PrintOperand(i->op[0]);
                fprintf(f," :\n");
                break;
            case ASSIGN_IR:
                if(pdebug)odebug("Print ASSIGN_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := ");
                PrintOperand(i->op[1]);
                fprintf(f," \n");
                break;
            case ADD_IR:    
                if(pdebug)odebug("Print ADD_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := ");
                PrintOperand(i->op[1]);
                fprintf(f," + ");
                PrintOperand(i->op[2]);
                fprintf(f," \n");
                break;
            case SUB_IR:
                if(pdebug)odebug("Print SUB_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := ");
                PrintOperand(i->op[1]);
                fprintf(f," - ");
                PrintOperand(i->op[2]);
                fprintf(f," \n");
                break;
            case MUL_IR:
                if(pdebug)odebug("Print MUL_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := ");
                PrintOperand(i->op[1]);
                fprintf(f," * ");
                PrintOperand(i->op[2]);
                fprintf(f," \n");
                break;
            case DIV_IR:
                if(pdebug)odebug("Print DIV_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := ");
                PrintOperand(i->op[1]);
                fprintf(f," / ");
                PrintOperand(i->op[2]);
                fprintf(f," \n");
                break;
            case GOTO_IR:
                if(pdebug)odebug("Print GOTO_IR\n");
                fprintf(f,"GOTO ");
                PrintOperand(i->op[0]);
                fprintf(f," \n");
                break;
            case IFGOTO_IR:
                if(pdebug)odebug("Print IFGOTO_IR\n");
                fprintf(f,"IF ");
                PrintOperand(i->op[0]);
                fprintf(f," %s ",i->e.relop);
                PrintOperand(i->op[1]);
                fprintf(f," ");
                PrintOperand(i->op[2]);
                fprintf(f," \n");
                break;
            case RETURN_IR:
                if(pdebug)odebug("Print RETURN_IR\n");
                fprintf(f,"RETURN ");
                PrintOperand(i->op[0]);
                fprintf(f," \n");
                break;
            case DEC_IR:
                if(pdebug)odebug("Print DEC_IR\n");
                fprintf(f,"DEC ");
                PrintOperand(i->op[0]);
                fprintf(f," ");
                PrintOperand(i->op[1]);
                fprintf(f," \n");
                break;
            case ARG_IR:
                if(pdebug)odebug("Print ARG_IR\n");
                fprintf(f,"ARG ");
                PrintOperand(i->op[0]);
                fprintf(f," \n");
                break;
            case CALL_IR://op0 := CALL op1 
                if(pdebug)odebug("Print CALL_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := CALL ");
                PrintOperand(i->op[1]);
                fprintf(f," \n");
                break;
            case PARAM_IR:
                if(pdebug)odebug("Print PARAM_IR\n");
                fprintf(f,"PARAM ");
                PrintOperand(i->op[0]);
                fprintf(f," \n");
                break;
            case READ_IR:
                if(pdebug)odebug("Print READ_IR\n");
                fprintf(f,"READ ");
                PrintOperand(i->op[0]);
                fprintf(f," \n");
                break;
            case WRITE_IR:
                if(pdebug)odebug("Print WRITE_IR\n");
                fprintf(f,"WRITE ");
                PrintOperand(i->op[0]);
                fprintf(f," \n");
                break;
            default:
                printf("Error in print intercode:unknown kind\n");
        }
        i = i->next;
    }
}
void printoutput(char *filename){
//输出模块打印优化后中间代码
    odebug("-----Print output Begin-----\n");
    FILE *f = fopen(filename, "w");
        if (!f){
            printf("cannot open file : %s\n",filename);
            return;
        }
    for(int i = 0;i<blocknum;i++){
        if(bb[i]!=NULL){
            if(bb[i]->codehead!=NULL)PrintInterCode(bb[i]->codehead);
        }
    }
    fclose(f);
    odebug("-----Print output Finished!-----\n");
}
