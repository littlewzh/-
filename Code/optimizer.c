#include"optimizer.h"
#define OPTIMIZER
#ifdef OPTIMIZER
#define odebug(...) printf(__VA_ARGS__)
#else
#define odebug(...) assert(1)
#endif
#define TODO assert(0);
#define MAX_BLOCK_NUM 400
#define MAX_VAR_NUM 500
FILE *f;
BasicBlock* bb;//存放基本块指针的数组
int blocknum = 0;//基本块数量
DAGNode* D;//存放基本块指针的数组
int dagsize,dagnum;//size是数组目前大小，num是存放节点数量
//指定BasicBlock中插入新的一条Intercode
InterCode AddInterCode(BasicBlock block,int codekind,Operand op0,Operand op1,Operand op2){//往一个basicblock中插入一行中间代码
    InterCode newcode = (InterCode) malloc(sizeof(struct InterCode_));//本条指令的指针
    newcode->kind = codekind;
    if(op0!=NULL)newcode->op[0] = op0;
    if(op1!=NULL)newcode->op[1] = op1;
    if(op2!=NULL)newcode->op[2] = op2;
    newcode->next = NULL;
    if(block->codehead == NULL){
        newcode->prev = NULL;
        block->codehead = newcode;
        block->codetail = block->codehead;
    }
    else{
        block->codetail->next = newcode;
        newcode->prev = block->codetail;
        block->codetail = newcode;
    }
    return newcode;
}
//makeop 利用变量名的特性根据名字得到op
Operand makeop(char *name){
    assert(name!=NULL);
    int opdebug = 0;
    if(opdebug)odebug("In makeop:   %s\n",name);
    Operand op = (Operand)malloc(sizeof(Operand_d));
    char s[32];
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
//输入模块：读取输入文件信息存储到基本块
void readinput(char* filename){
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
    int blockno = 0;//记录块序号，从0开始
    BasicBlock curb = NULL;//当前块的指针
    f = fopen(filename, "r");
    while(fgets(buf,500,f)!=NULL){//读入一行到buf
        if(buf[0]=='\n'){//空行
            if(rdebug)odebug("null\n");
            continue;
        }
        linenum++;
        if(rdebug)odebug("Line %d : ",linenum);
        int linelen = strlen(buf);//长度
        //每次都先申请好待用的op避免冗余代码
        Operand op0 = (Operand)malloc(sizeof(Operand_d));
        Operand op1 = (Operand)malloc(sizeof(Operand_d));
        Operand op2 = (Operand)malloc(sizeof(Operand_d));
        //如果当前块为空,或者是label就新增一个
        if(curb==NULL||buf[0]=='L'||buf[0]=='F'){
            if(rdebug)odebug(" (new bb) ");
            curb = (BasicBlock)malloc(sizeof(BasicBlock_d));
            bb[blockno]=curb;//记录到数组里,编号从1开始
            curb->no = blockno;
            curb->codehead=NULL;
            curb->codetail=NULL;
            curb->prev=NULL;
            curb->next[0]=NULL;
            curb->next[1]=NULL;
            blockno++;
        }
        //下面对该行解析出指令内容
        char s[32],s1[32],s2[32],s3[32];
        if (buf[0]=='F'){//新函数=>新基本块
            if(rdebug)odebug("function: \n");
            op0->kind = FUNC_OP;
            op0->u.name = malloc(sizeof(char)*linelen);
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
            op2->kind = LABEL_OP;
            char *srelop = (char*)malloc(sizeof(char)*32);//新建一个地址给relop，不然地址会出错
            sscanf(buf, "IF %s %s %s GOTO label%d",s1,srelop,s3,&op2->u.no);
            InterCode newcode = AddInterCode(curb,IFGOTO_IR,makeop(s1),makeop(s3),op2);
            newcode->e.relop = srelop;
            curb=NULL;
        }
        else if (buf[0]=='R'&&buf[2]=='T'){//RETURN=>基本块末尾
            if(rdebug)odebug("RETURN\n");
            sscanf(buf,"RETURN %s",s);
            op0 = makeop(s);
            AddInterCode(curb,RETURN_IR,op0,NULL,NULL);
            curb = NULL;
        }
        else if (buf[0]=='D'){//DEC
            if(rdebug)odebug("DEC\n");
            int size;
            sscanf(buf,"DEC %s %d",s,&size);
            op0 = makeop(s);
            InterCode newcode = AddInterCode(curb,DEC_IR,op0,NULL,NULL);
            newcode->e.decsize = size;
        }
        else if (buf[0]=='A'){//ARG
            if(rdebug)odebug("ARG\n");
            sscanf(buf,"ARG %s",s);
            op0 = makeop(s);
            AddInterCode(curb,ARG_IR,op0,NULL,NULL);
        }
        else if (buf[0]=='P'){//PARAM
            if(rdebug)odebug("PARAM\n");
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
            sscanf(buf,"READ %s",s);
            op0 = makeop(s);
            AddInterCode(curb,READ_IR,op0,NULL,NULL);
        }
        else if (buf[0]=='W'){//WRITE
            if(rdebug)odebug("WRITE\n");
            sscanf(buf,"WRITE %s",s);
            op0 = makeop(s);
            AddInterCode(curb,WRITE_IR,op0,NULL,NULL);
        }
        else if (buf[0]=='v'||buf[0]=='t'||buf[0]=='*'||buf[0]=='&'){//
            if(rdebug)odebug("ASSIGN...\n");
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
                    op1->kind = FUNC_OP;
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
//删除code指令，返回nextcode
InterCode DeleteSingleCode(InterCode code){
    if(code->prev==NULL){//表头
        code->next->prev = NULL;
        code = code->next;
    }
    else if (code->next==NULL){//表尾
        code->prev->next = NULL;
        code = NULL;
    }
    else{
        code->prev->next = code->next;
        code->next->prev = code->prev;
        code = code->next;
    }
    return code;
}
//对于单条指令的优化：加减乘除和IFGOTO
InterCode OptimizeSingleCode(InterCode code){
    Operand op0 = code->op[0];
    Operand op1 = code->op[1];
    Operand op2 = code->op[2];
    //下面做单条优化
    switch (code->kind)
    {
    case ADD_IR:
        if(op1->kind==CONSTANT_OP&&op2->kind==CONSTANT_OP){
            //立即数直接运算并赋值
            code->kind = ASSIGN_IR;
            op1->u.value = op1->u.value + op1->u.value;
            code->op[2] = NULL;
        }
        else if(op1->kind==CONSTANT_OP&&op1->u.value==0){
            //0改为赋值
            code->kind = ASSIGN_IR;
            code->op[1] = op2;
            code->op[2] = NULL;
        }
        else if(op2->kind==CONSTANT_OP&&op2->u.value==0){
            //0改为赋值
            code->kind = ASSIGN_IR;
            code->op[2] = NULL;
        }
        break;
    case SUB_IR:
        if(op1->kind==CONSTANT_OP&&op2->kind==CONSTANT_OP){
            code->kind = ASSIGN_IR;
            op1->u.value = op1->u.value - op1->u.value;
            code->op[2] = NULL;
        }
        else if(op2->kind==CONSTANT_OP&&op2->u.value==0){
            code->kind = ASSIGN_IR;
            code->op[2] = NULL;
        }
        break;
    case MUL_IR:
        if(op1->kind==CONSTANT_OP&&op2->kind==CONSTANT_OP){
            code->kind = ASSIGN_IR;
            op1->u.value = op1->u.value * op1->u.value;
            code->op[2] = NULL;
        }
        else if(op1->kind==CONSTANT_OP&&op1->u.value==1){
            code->kind = ASSIGN_IR;
            code->op[1] = op2;
            code->op[2] = NULL;
        }
        else if(op2->kind==CONSTANT_OP&&op2->u.value==1){
            code->kind = ASSIGN_IR;
            code->op[2] = NULL;
        }
        else if(op1->kind==CONSTANT_OP&&op1->u.value==0){
            code->kind = ASSIGN_IR;
            code->op[2] = NULL;
        }
        else if(op2->kind==CONSTANT_OP&&op2->u.value==0){
            code->kind = ASSIGN_IR;
            code->op[1] = op2;
            code->op[2] = NULL;
        }
        else if(op1->kind==CONSTANT_OP&&op1->u.value==2){
            code->kind = ADD_IR;
            code->op[1] = op2;
        }
        else if(op2->kind==CONSTANT_OP&&op2->u.value==2){
            code->kind = ADD_IR;
            code->op[2] = op1;
        }
        break;
    case DIV_IR:
        if(op1->kind==CONSTANT_OP&&op2->kind==CONSTANT_OP){
            code->kind = ASSIGN_IR;
            op1->u.value = op1->u.value / op1->u.value;
            code->op[2] = NULL;
        }
        else if(op2->kind==CONSTANT_OP&&op2->u.value==1){
            code->kind = ASSIGN_IR;
            code->op[2] = NULL;
        }
        break;
    case IFGOTO_IR://优化有条件跳转：常量传播后可能有两个立即数比较,如果不满足就不用这一条了
        if(op0->kind==CONSTANT_OP&&op1->kind==CONSTANT_OP){
            int v1 = op0->u.value;
            int v2 = op1->u.value;
            if(strcmp(code->e.relop,"==")==0 && v1 == v2||
            strcmp(code->e.relop,">=")==0 && v1 >= v2||
            strcmp(code->e.relop,"<=")==0 && v1 <= v2||
            strcmp(code->e.relop,"!=")==0 && v1 != v2||
            strcmp(code->e.relop,"<")==0 && v1 < v2||
            strcmp(code->e.relop,">")==0 && v1 > v2){
                code->kind=GOTO_IR;
                code->op[0]=op2;
                if(code->next!=NULL){
                    if(code->next->kind = GOTO_IR){
                        DeleteSingleCode(code->next);
                    }
                }
            }
            else{
                DeleteSingleCode(code);
                return NULL;
            }
        }
    default:
        break;
    }
    return code;
}
//比较op名字是否一样，1为还要版本一样
int EquivalenceOP(Operand op1,Operand op2,int flag){
    if(op1->kind==op2->kind){
        if(op1->kind==VARIABLE_OP||op1->kind==TMPVAR_OP){
            if(op1->u.no==op2->u.no&&(!flag||op1->ver==op2->ver))return 1;
        }
        else if(op1->kind==CONSTANT_OP){
            if(op1->u.value==op2->u.value)return 1;
        }
        else if(op1->kind==GETADDR_OP||op1->kind==GETVAL_OP){
            //TODO;可以认为全是不等价的从而不优化
        }
    }
    return 0;
}
int EquivalenceDAG(DAGNode d1,DAGNode d2){
    if(d1->kind==d2->kind){
        if(d1->kind==ADD_NODE||d1->kind==MUL_NODE){
            //交换律下两个操作数不对称等价也可以
            if(EquivalenceOP(d1->leftchild->op,d2->leftchild->op,1)==1&&EquivalenceOP(d1->rightchild->op,d2->rightchild->op,1)==1){
                return 1;
            }
            else if(EquivalenceOP(d1->rightchild->op,d2->leftchild->op,1)==1&&EquivalenceOP(d1->leftchild->op,d2->rightchild->op,1)==1){
                return 1;
            }
        }
        else if(d1->kind==SUB_NODE||d1->kind==DIV_NODE){
            if(EquivalenceOP(d1->leftchild->op,d2->leftchild->op,1)==1&&EquivalenceOP(d1->rightchild->op,d2->rightchild->op,1)==1){
                return 1;
            }
        }
    }
    return 0;
}
//新建DAG节点
DAGNode NewDAGNode(Operand op){
    //数组满了要通过拷贝加倍
    if(dagnum==dagsize){
        DAGNode *newd = (DAGNode*)malloc(sizeof(DAGNode)*dagsize*2);
        for(int i=0;i<dagnum;i++){
            newd[i] = D[i];
        }
        D = newd;
        dagsize*=2;
    }
    //新建一个DAG节点
    DAGNode new = malloc(sizeof(DAGNode_d));
    D[dagnum] = new;
    new->kind = LEAF_NODE;
    new->op = op;
    new->no = dagnum;
    new->used = 0;
    dagnum++;
    return new;
}
//在DAG中找到最新版本op的位置,没有就新建并设置op版本为1
DAGNode SearchOperand(Operand op,int flag){//falg为1表示op是被赋值、为0表示op是使用，2是单纯查查
    DAGNode res=NULL;
    int ver = 0;
    for(int i=0;i<dagnum;i++){
        if(EquivalenceOP(op,D[i]->op,0)&&ver<D[i]->op->ver){
            res = D[i];
            ver = D[i]->op->ver;            
        }
    }
    if(flag==2)return res;//单纯查询直接返回
    if(res==NULL){
        //之前没有的符号
        op->ver = 1;
        res = NewDAGNode(op);
    }
    else {
        if(flag){
            op->ver = res->op->ver+1;
            res = NewDAGNode(op);
        }
        else{
            op->ver = res->op->ver;
        }
    }
    if(flag==1)res->used = 0;
    else if(flag==0)res->used++;
    return res;
}
//在DAG中加入节点
void AddDAGNode(InterCode code){
    Operand op0 = code->op[0];
    Operand op1 = code->op[1];
    Operand op2 = code->op[2];
    DAGNode d0,d1,d2;
    if(code->kind==ASSIGN_IR){
        d0 = SearchOperand(op0,1);
        d0->kind = ASSIGN_NODE;
        d1 = SearchOperand(op1,0);
        d0->leftchild = d1;
    }
    else if(code->kind==ADD_IR||code->kind==SUB_IR||code->kind==MUL_IR||code->kind==DIV_IR){
        d0 = SearchOperand(op0,1);
        if(code->kind==ADD_IR)d0->kind = ADD_NODE;
        if(code->kind==SUB_IR)d0->kind = SUB_NODE;
        if(code->kind==MUL_IR)d0->kind = MUL_NODE;
        if(code->kind==DIV_IR)d0->kind = DIV_NODE;
        d1 = SearchOperand(op1,0);
        d2 = SearchOperand(op2,0);
        d0->leftchild = d1;
        d0->rightchild = d2;
    }
    else if(code->kind==WRITE_IR||code->kind==RETURN_IR||code->kind==ARG_IR){
        //使用了op0
        d0 = SearchOperand(op0,0);
    }
    else if(code->kind==IFGOTO_IR){
        //使用了op0、op1
        d0 = SearchOperand(op0,0);
        d1 = SearchOperand(op1,0);
    }
    else if(code->kind==READ_IR||code->kind==CALL_IR||code->kind==PARAM_IR||code->kind==DEC_IR){
        //给op0赋值了新版本
        d0 = SearchOperand(op0,1);
    }
}
//用基本块B创建出DAG
void CreateDAG(BasicBlock b){
    D = (DAGNode*)malloc(sizeof(DAGNode)*32);
    dagsize = 32;
    dagnum = 0;
    InterCode code = b->codehead;
    while(code!=NULL){
        AddDAGNode(code);
        code = code->next;
    }
}
void debugDAG(){
    for(int i=0;i<dagnum;i++){
        if(D[i]==NULL)continue;
        if(D[i]->op->kind==VARIABLE_OP)odebug("DAGnode %d : %d v%d.%d used:%d\n",i,D[i]->kind,D[i]->op->u.no,D[i]->op->ver,D[i]->used); 
        if(D[i]->op->kind==TMPVAR_OP)odebug("DAGnode %d : %d t%d.%d used:%d\n",i,D[i]->kind,D[i]->op->u.no,D[i]->op->ver,D[i]->used); 
        if(D[i]->op->kind==CONSTANT_OP)odebug("DAGnode %d : %d #%d used:%d\n",i,D[i]->kind,D[i]->op->u.value,D[i]->used); 
    }
}
//把代码中所有有oldop的都替换成newop
void ReplaceOP(InterCode codehead,Operand oldop,Operand newop){
    InterCode code = codehead;
    while (code != NULL)
    {
        if (code->kind == ASSIGN_IR){
            if (EquivalenceOP(code->op[0], oldop, 1)){
                DeleteSingleCode(code);
            }
            if (EquivalenceOP(code->op[1], oldop, 1)){
                code->op[1] = newop;
            }
        }
        else if (code->kind == ADD_IR || code->kind == SUB_IR || code->kind == MUL_IR || code->kind == DIV_IR){
            if (EquivalenceOP(code->op[0], oldop, 1)){
                DeleteSingleCode(code);
            }
            if (EquivalenceOP(code->op[1], oldop, 1)){
                code->op[1] = newop;
            }
            if (EquivalenceOP(code->op[2], oldop, 1)){
                code->op[2] = newop;
            }
        }
        else if (code->kind == RETURN_IR || code->kind == WRITE_IR || code->kind == ARG_IR){
            if (EquivalenceOP(code->op[0], oldop, 1)){
                code->op[0] = newop;
            }
        }
        else if (code->kind == IFGOTO_IR){
            if (EquivalenceOP(code->op[0], oldop, 1)){
                code->op[0] = newop;
            }
            if (EquivalenceOP(code->op[1], oldop, 1)){
                code->op[1] = newop;
            }
        }
        code = code->next;
    }
}
void ConstantFolding(InterCode codehead){
    int flag = 1;
    while(flag){
        flag = 0;
        for(int i=0;i<dagnum;i++){
            DAGNode d0 = D[i];
            if(d0->kind==ASSIGN_NODE){
                if(d0->leftchild->op->kind==CONSTANT_OP){
                    flag = 1;
                    ReplaceOP(codehead,d0->op,d0->leftchild->op);
                    d0->kind = LEAF_NODE;
                    d0->op = d0->leftchild->op;
                }
            }
            else if(d0->kind!=LEAF_NODE){
                if(d0->leftchild->op->kind==CONSTANT_OP&&d0->rightchild->op->kind==CONSTANT_OP){
                    int v1 =d0->leftchild->op->u.value;
                    int v2 =d0->rightchild->op->u.value; 
                    int v;
                    if(d0->kind==ADD_NODE)v=v1+v2;
                    else if(d0->kind==SUB_NODE)v=v1-v2;
                    else if(d0->kind==MUL_NODE)v=v1*v2;
                    else if(d0->kind==DIV_NODE)v=v1/v2;
                    Operand newop=malloc(sizeof(Operand_d));
                    newop->kind=CONSTANT_OP;
                    newop->u.value=v;
                    flag=1;
                    ReplaceOP(codehead,d0->op,newop);
                    d0->kind = LEAF_NODE;
                    d0->op=newop;
                }
            }
        }   
    }
    InterCode code = codehead;
    while(code!=NULL){
        OptimizeSingleCode(code);
        code = code->next;
    }
    
}
void CommonSubexpression(InterCode codehead){
    for(int i=0;i<dagnum;i++){
        if(D[i]->kind==ADD_NODE||D[i]->kind==SUB_NODE||D[i]->kind==MUL_NODE||D[i]->kind==DIV_NODE){
            for(int j=0;j<i;j++){
                if(EquivalenceDAG(D[i],D[j])==1){
                    D[i]->kind = ASSIGN_NODE;
                    D[i]->leftchild = D[j];
                    Operand oldop = D[i]->op;
                    Operand newop = D[j]->op;
                    ReplaceOP(codehead,oldop,newop);
                }
            }
        }
    }
}
void DeadCode(InterCode codehead){
    int flag = 1;//仍然可以消除
    while(flag){
        flag = 0;
        debugDAG();
        for(int i=0;i<dagnum;i++){
            if(D[i]->used==0&&D[i]->kind!=LEAF_NODE){
                if(D[i]->op->kind!=TMPVAR_OP&&D[i]->op->kind!=VARIABLE_OP)continue;
                //这里默认不是最新版本也就是通往外部的才删除，可以优化为检测是否外部活跃
                if(D[i]->op->ver==SearchOperand(D[i]->op,2)->op->ver)continue;
                flag = 1;
                D[i]->leftchild->used--;
                if(D[i]->kind!=ASSIGN_NODE)D[i]->rightchild->used--;
                //删除D[i]的op被赋值的地方
                InterCode code = codehead;
                while(code!=NULL){
                    //oldop只可能出现在op0的位置而且是赋值
                    if(code->kind==ASSIGN_IR||code->kind==ADD_IR||code->kind==SUB_IR||code->kind==MUL_IR||code->kind==DIV_IR){
                        if(EquivalenceOP(code->op[0],D[i]->op,1)==1){
                            DeleteSingleCode(code);
                        }
                    }
                    code = code->next;
                }
                D[i]->used--;//避免再删一次
            }
        }
        if(!flag)return;
    }
}

//对一个基本块的局部优化：建立DAG、常量折叠、无用代码消除、公共子表达式
void LocalOptimize(BasicBlock b){
    odebug("LocalOptimize:Block %d\n",b->no);
    CreateDAG(b);
    debugDAG();
    ConstantFolding(b->codehead);
    CreateDAG(b);
    CommonSubexpression(b->codehead);
    CreateDAG(b);
    DeadCode(b->codehead);
}
void optimize(){
//优化模块主函数
    odebug("-----Optimize Begin-----\n");
    for(int i=0;i<blocknum;i++){
        if(bb[i]!=NULL){
            LocalOptimize(bb[i]);
        }
    }
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
            fprintf(f,"%s",op->u.name);
            break;
        default:
            printf("Error in PrintOperand:wrong type\n");
            assert(0);
    }
}
void PrintInterCode(InterCode head){
    odebug("In PrintInterCode\n");
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
                fprintf(f,"\n");
                break;
            case ADD_IR:    
                if(pdebug)odebug("Print ADD_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := ");
                PrintOperand(i->op[1]);
                fprintf(f," + ");
                PrintOperand(i->op[2]);
                fprintf(f,"\n");
                break;
            case SUB_IR:
                if(pdebug)odebug("Print SUB_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := ");
                PrintOperand(i->op[1]);
                fprintf(f," - ");
                PrintOperand(i->op[2]);
                fprintf(f,"\n");
                break;
            case MUL_IR:
                if(pdebug)odebug("Print MUL_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := ");
                PrintOperand(i->op[1]);
                fprintf(f," * ");
                PrintOperand(i->op[2]);
                fprintf(f,"\n");
                break;
            case DIV_IR:
                if(pdebug)odebug("Print DIV_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := ");
                PrintOperand(i->op[1]);
                fprintf(f," / ");
                PrintOperand(i->op[2]);
                fprintf(f,"\n");
                break;
            case GOTO_IR:
                if(pdebug)odebug("Print GOTO_IR\n");
                fprintf(f,"GOTO ");
                PrintOperand(i->op[0]);
                fprintf(f,"\n");
                break;
            case IFGOTO_IR:
                if(pdebug)odebug("Print IFGOTO_IR\n");
                fprintf(f,"IF ");
                PrintOperand(i->op[0]);
                fprintf(f," %s ",i->e.relop);
                PrintOperand(i->op[1]);
                fprintf(f," GOTO ");
                PrintOperand(i->op[2]);
                fprintf(f,"\n");
                break;
            case RETURN_IR:
                if(pdebug)odebug("Print RETURN_IR\n");
                fprintf(f,"RETURN ");
                PrintOperand(i->op[0]);
                fprintf(f,"\n");
                break;
            case DEC_IR:
                if(pdebug)odebug("Print DEC_IR\n");
                fprintf(f,"DEC ");
                PrintOperand(i->op[0]);
                fprintf(f," %d\n",i->e.decsize);
                break;
            case ARG_IR:
                if(pdebug)odebug("Print ARG_IR\n");
                fprintf(f,"ARG ");
                PrintOperand(i->op[0]);
                fprintf(f,"\n");
                break;
            case CALL_IR://op0 := CALL op1 
                if(pdebug)odebug("Print CALL_IR\n");
                PrintOperand(i->op[0]);
                fprintf(f," := CALL ");
                PrintOperand(i->op[1]);
                fprintf(f,"\n");
                break;
            case PARAM_IR:
                if(pdebug)odebug("Print PARAM_IR\n");
                fprintf(f,"PARAM ");
                PrintOperand(i->op[0]);
                fprintf(f,"\n");
                break;
            case READ_IR:
                if(pdebug)odebug("Print READ_IR\n");
                fprintf(f,"READ ");
                PrintOperand(i->op[0]);
                fprintf(f,"\n");
                break;
            case WRITE_IR:
                if(pdebug)odebug("Print WRITE_IR\n");
                fprintf(f,"WRITE ");
                PrintOperand(i->op[0]);
                fprintf(f,"\n");
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
        //fprintf(f,"Block %d:\n",i);
        if(bb[i]!=NULL){
            if(bb[i]->codehead!=NULL)PrintInterCode(bb[i]->codehead);
        }
    }
    fclose(f);
    odebug("-----Print output Finished!-----\n");
}
