#include <stdio.h>
#include "objectcode.h"

#define ASSEMBLE
#ifdef ASSEMBLE
#define adebug(...) printf(__VA_ARGS__)
#else
#define adebug(...) assert(1)
#endif


extern InterCodes intercodeshead;
FILE* fs;
#define code(format,args...) fprintf(fs,format,##args)
Reg mipreg[32];
int use_reg1,use_reg2;  //；为了保证同一条运算分配的寄存器不冲突
char* regname[32]={
    "$0","$1",      
    "$v0","$v1",   //表达式求值或函数结果 2-3
    "$a0","$a1","$a2","$a3",   //函数参数 4-7
    "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",  //8-15
    "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7", //16-23
    "$t8","$t9",                                     //24-25
    "$k0","$k1",
    "$gp","$sp","$fp","$ra"
};
void reg_init(){
    for(int i=0;i<32;i++){
        mipreg[i].free = 0;
        mipreg[i].offset = 0;
        mipreg[i].var_num = 0;
    }
}
extern Element* Hashtable[HASHSIZE+1];
extern int tmpcnt;
int varcnt;  //变量个数
Var* varsymbol; //变量位置描述符
void var_init(){
    varcnt = 0;
    for(int i=0;i<HASHSIZE+1;i++){
        if(Hashtable[i]!=NULL){
            Element* e = Hashtable[i];
            while(e!=NULL){
                if(e->type->kind == BASIC || e->type->kind == ARRAY || e->type->kind == STRUCTVAR){
                    varcnt++;
                    e->varnum = varcnt;
                }
                e=e->next;
            }
        }
    }
    varsymbol = (Var *)malloc(sizeof(Var[varcnt+tmpcnt+1]));
    printf("varnum: %d\n",varcnt+tmpcnt+1);
    for(int i=1;i<varcnt+tmpcnt+1;i++){
        varsymbol[i].offset=0;
        varsymbol[i].reg = 0;
    }
}
Operandlist* paramlist;
void param_init(){
    paramlist = malloc(sizeof(Operandlist));
    paramlist->next = NULL;
}
void param_insert(Operand op){    //函数参数列表采用头插法
    Operandlist* tmp = malloc(sizeof(Operandlist));
    tmp->op = op;
    tmp->next = paramlist->next;
    paramlist->next = tmp;
}
void param_free(){
    paramlist->next=NULL;
}
void obj_init(){
    reg_init();
    var_init();
    param_init();
    baseblock_split();
}

int Sp_offset = 0;
void objectcode(char* filename){
    obj_init();
    gen_mipcode(filename);
}

int findnum(Operand op){
    if(op->kind == VARIABLE_OP || op->kind == GETADDR_OP || op->kind == GETVAL_OP){
        Element* e = Search(op->u.name);

        return e->varnum; 
    }else if(op->kind == TMPVAR_OP || op->kind == GETADDRTMP_OP || op->kind == GETVALTMP_OP){
        return varcnt+op->tmp_num;
    }
    assert(0);
    return 0;
    
}
void regcheck(int knum){
    for(int i=8;i<26;i++){
        if(mipreg[i].free && mipreg[i].var_num > varcnt){
            int num = mipreg[i].var_num;
            if(varsymbol[num].lastuse<knum) reg_spill(i); 
        }
    }
}

void reg_spill(int regnum){
    if(mipreg[regnum].free==0) return ; //该寄存器为空
    mipreg[regnum].free = 0;
    int var = mipreg[regnum].var_num;
    mipreg[regnum].var_num = 0;
    varsymbol[var].reg = 0;
    if(varsymbol[var].offset==0){          //第一次存到栈中
        code("addi $sp, $sp, -4\n");
        Sp_offset += 4; 
        code("sw %s, 0($sp)\n",regname[regnum]);
        varsymbol[var].offset = Sp_offset;
    }else{
        code("sw %s, %d($fp)\n",regname[regnum],-varsymbol[var].offset);
    }
    
}
void reg_free(int regnum){
    mipreg[regnum].free = 0;
    mipreg[regnum].var_num = 0;
}
int reg_allocate(Operand op){
    int varnum = findnum(op);
    //adebug("varnum: %d\n",varnum);
    if(varsymbol[varnum].reg!=0) return varsymbol[varnum].reg;  //该变量已有寄存器
    for(int i=8;i<26;i++){                       //该变量没有寄存器
        if(mipreg[i].free == 0){
            if(varsymbol[varnum].offset!=0){
                code("lw $%d, %d($fp)\n",i,-varsymbol[varnum].offset);
            }
            mipreg[i].free = 1;
            mipreg[i].var_num = varnum;
            varsymbol[varnum].reg = i;
            return i;
        }
    }
    //分析基本块，分析变量使用信息
    // 此时没有空闲的寄存器
    //???????位于同一个三地址代码中的几个变量不能分配一个寄存器
    for(int i=8;i<26;i++){
        if(i!=use_reg1 && i!=use_reg2){
            reg_spill(i);
            mipreg[i].free = 1;
            mipreg[i].var_num = varnum;
            varsymbol[varnum].reg = i;
            return i;
        }
    }
    assert(0);
    int res = 0;int far = 0;
    for(int i=8;i<26;i++){            //找到离当前使用最远的变量寄存器
        int k = mipreg[i].var_num;
        if(varsymbol[k].nextuse>far){
            far = varsymbol[k].nextuse;
            res = i;
        } 
    }
    reg_spill(res);
    mipreg[res].free=1;
    mipreg[res].var_num = varnum;
    varsymbol[varnum].reg = res;
    return res;
}
void useanaly(Operand op,int knum){
    if(op==NULL) return;
    if(op->kind == CONSTANT_OP) return ;
    if(op->kind == TMPVAR_OP|| op->kind == GETADDRTMP_OP||op->kind == GETVALTMP_OP){
        int varnum = findnum(op);
        varsymbol[varnum]. lastuse= knum;
    }
}
void baseblock_split(){
    InterCodes p = intercodeshead->next;
    intercodeshead->startflag = 1;
    intercodeshead->endflag = 0;
    int k=1;
    int flag=0;
    while(p!=NULL){
        k++;
        p->startflag=0;
        p->endflag=0;
        if(flag) p->startflag = 1;
        flag=0;
        InterCode i = p->code;
        i->intercodenum = k;
        switch(i->kind){
            case LABEL_IR:
                p->startflag=1;
                break;
            case FUNC_IR://函数入口
                p->startflag=1;
                break;
            case ASSIGN_IR:
            {
                useanaly(i->op[0],k);
                useanaly(i->op[1],k);
                break;
            }
                
            case ADD_IR:case SUB_IR:case MUL_IR:case DIV_IR:
                useanaly(i->op[0],k);
                useanaly(i->op[1],k);
                useanaly(i->op[2],k);
            
                break;
            case GOTO_IR:
                flag=1;
                break;
            case IFGOTO_IR://IF t1 op t2 GOTO,trick是拆分成两条第二条当成GOTO ，但这里不打换行
                useanaly(i->op[0],k);
                useanaly(i->op[2],k);
                k--;
                break;
            case RETURN_IR:case DEC_IR:case ARG_IR:case PARAM_IR:
                useanaly(i->op[0],k);
                break;
            case CALL_IR://op0 := CALL op1 
            case READ_IR:
            case WRITE_IR:
                useanaly(i->op[0],k);
                break;
            default:
                printf("Error in print intercode:unknown kind\n");
        }
        p = p->next;
    }
}

void gen_mipcode(char* filename){
    fs = fopen(filename, "w");
    if (!fs){
        printf("cannot open file : %s\n",filename);
        return;
    }
    adebug("start assemble\n");
    fprintf(fs,".data\n_prompt: .asciiz \"Enter an integer:\" \n_ret: .asciiz \"\\n\"\n.globl main\n.text\n\nread:\nli $v0, 4  \nla $a0, _prompt \n syscall \nli $v0, 5 \nsyscall   \njr $ra   \n\nwrite:   \nli $v0, 1   \nsyscall   \nli $v0, 4  \nla $a0, _ret  \nsyscall   \nmove $v0, $0  \njr $ra\n\n");
    InterCodes p = NULL;
    if(intercodeshead != NULL){p = intercodeshead;}//遍历链表的结构体指针
    while(p!=NULL){
        /*int spillflag=0;
        if(p->next!=NULL && p->startflag){  //这是本基本快的最后一条语句
            if(p->code->kind == GOTO_IR){  //本条为跳转指令
                for(int i=8;i<26;i++){
                    reg_spill(i);
                }

            }
        }*/
        InterCode i = p->code;
        //printf("%d\n",i->intercodenum);
        use_reg1 = 0;
        use_reg2 = 0;
        switch (i->kind){
        
        case READ_IR:{
            
            int reg = reg_allocate(i->op[0]);

            //printf("reg: %d\n",reg);
            fprintf(fs,"addi $sp, $sp, -4\n");
            fprintf(fs,"sw $ra, 0($sp)\n");
            fprintf(fs,"jal read\n");
            fprintf(fs,"lw $ra, 0($sp)\n");
            fprintf(fs,"addi $sp, $sp, 4\n");
            fprintf(fs,"move $%d, $v0\n",reg);
            break;
        }
        case WRITE_IR:{
            int reg = reg_allocate(i->op[0]);
            fprintf(fs,"move $a0, $%d\n",reg);
            fprintf(fs,"addi $sp, $sp, -4\n");
            fprintf(fs,"sw $ra, 0($sp)\n");
            fprintf(fs,"jal write\n");
            fprintf(fs,"lw $ra, 0($sp)\n");
            fprintf(fs,"addi $sp, $sp, 4\n");
            break;
        }
        case DEC_IR:{
            int size = i->op[1]->u.value;
            code("addi $sp, $sp, %d\n",-size);
            Sp_offset += size;
            int reg1 = reg_allocate(i->op[0]);
            code("move $%d, $sp\n",reg1);
            int varnum = findnum(i->op[0]);
            code("addi $sp, $sp, -4\n");
            Sp_offset+=4;
            code("sw $%d, 0($sp)\n",reg1);
            varsymbol[varnum].offset = Sp_offset;
            break;
        }
        case ASSIGN_IR:{
            Operand left = i->op[0];
            Operand right = i->op[1];
            int reg1 = reg_allocate(left);
            use_reg1 = reg1;
            if(left->kind == VARIABLE_OP || left->kind == TMPVAR_OP){
                switch (right->kind)
                {
                case CONSTANT_OP:
                {
                    
                    code("li $%d, %d\n",reg1,right->u.value);
                    break;
                }     
                case VARIABLE_OP:
                case TMPVAR_OP:
                {
                    int reg2 = reg_allocate(right);
                    code("move $%d, $%d\n",reg1,reg2);
                    break;
                }
                case GETVAL_OP:
                case GETVALTMP_OP:
                {
                    int reg2 = reg_allocate(right);
                    code("lw $%d, 0($%d)\n",reg1,reg2);
                    break;
                }
                case GETADDR_OP:
                case GETADDRTMP_OP:
                {
                    int reg2 = reg_allocate(right);
                    code("move $%d, $%d\n",reg1,reg2);
                    break;
                }
                default:
                    break;
                }
            }else if(left->kind == GETVAL_OP || left->kind == GETVALTMP_OP){
                int reg2;
                if(right->kind == CONSTANT_OP){
                    code("li $v0, %d\n",right->u.value);
                    reg2=2;
                }else{
                    reg2 = reg_allocate(right);
                }
                    code("sw $%d, 0($%d)\n",reg2,reg1);
            }else{
                assert(0);
            }
            break;
        }    
        case ADD_IR:{
            int reg1 = reg_allocate(i->op[0]);
            use_reg1 = reg1;
            Operand op1,op2;
            if(i->op[1]->kind == CONSTANT_OP) {
                op1 = i->op[2];
                op2 = i->op[1];
            }
            else{
                op1 = i->op[1];
                op2 = i->op[2];
            } 
            if(op2->kind == CONSTANT_OP){
                int reg2 = reg_allocate(op1);
                code("addi $%d, $%d, %d\n",reg1,reg2,op2->u.value);
            }else{
                int reg2 = reg_allocate(op1);
                use_reg2 = reg2;
                int reg3 = reg_allocate(op2);
                code("add $%d, $%d, $%d\n",reg1,reg2,reg3);
            }
            break;
        }
        case SUB_IR:{
            int reg1 = reg_allocate(i->op[0]);
            use_reg1 = reg1;
            Operand op1,op2;
            if(i->op[1]->kind == CONSTANT_OP) {
                op1 = i->op[2];
                op2 = i->op[1];
            }
            else{
                op1 = i->op[1];
                op2 = i->op[2];
            } 
            if(op2->kind == CONSTANT_OP){
                int reg2 = reg_allocate(op1);
                code("addi $%d, $%d, -%d\n",reg1,reg2,op2->u.value);
            }else{
                int reg2 = reg_allocate(op1);
                use_reg2 = reg2;
                int reg3 = reg_allocate(op2);
                code("sub $%d, $%d, $%d\n",reg1,reg2,reg3);
            }
            break;
        }
        case MUL_IR:{
            int reg1 = reg_allocate(i->op[0]);
            use_reg1 = reg1;
            int reg2,reg3;
            Operand op1,op2;
            if(i->op[1]->kind == CONSTANT_OP){
                code("li $v0, %d\n",i->op[1]->u.value);
                reg2 = 2;
            }else{
                reg2 = reg_allocate(i->op[1]);
            }
            use_reg2 = reg2;
            if(i->op[2]->kind == CONSTANT_OP){
                code("li $v1, %d\n",i->op[2]->u.value);
                reg3 = 3;
            }else{
                reg3 = reg_allocate(i->op[2]);
            }
            code("mul $%d, $%d, $%d #%s\n",reg1,reg2,reg3,i->op[0]->u.name);
            break;
        }
        case DIV_IR:{
            int reg1 = reg_allocate(i->op[0]);
            use_reg1 = reg1;
            int reg2,reg3;
            Operand op1,op2;
            if(i->op[1]->kind == CONSTANT_OP){
                code("li $v0, %d\n",i->op[1]->u.value);
                reg2 = 2;
            }else{
                reg2 = reg_allocate(i->op[1]);
            }
            use_reg2 = reg2;
            if(i->op[2]->kind == CONSTANT_OP){
                code("li $v1, %d\n",i->op[2]->u.value);
                reg3 = 3;
            }else{
                reg3 = reg_allocate(i->op[2]);
            }
            code("div $%d, $%d\n",reg2,reg3);
            code("mflo $%d\n",reg1);
            break;
        }
        case LABEL_IR:{
            if(p->prev->code->kind!=GOTO_IR){
                for(int i=8;i<26;i++){
                    reg_spill(i);
                }
            }
            char* label = i->op[0]->u.name;//analy_Operand(i->op[0]); 
            code("%s :\n",label);
            if(i->op[0]->tmp_num!=0) Sp_offset = i->op[0]->tmp_num;
            for(int i=8;i<26;i++){
                if(mipreg[i].free){
                    mipreg[i].free = 0;
                    int varnum = mipreg[i].var_num;
                    varsymbol[varnum].reg = 0;
                }
            }
            break; 
        }
        case GOTO_IR:{
            for(int i=8;i<26;i++){
                    reg_spill(i);
            }

            code("j %s\n",i->op[0]->u.name);
            break;
        }
            
        case IFGOTO_IR:{
            int reg1 ,reg2;
            if(i->op[0]->kind == CONSTANT_OP){
                code("li $v0, %d\n",i->op[0]->u.value);
                reg1 = 2;
            }else{
                reg1 = reg_allocate(i->op[0]);
            }
            use_reg1 = reg1;
            if(i->op[2]->kind == CONSTANT_OP){
                code("li $v1, %d\n",i->op[2]->u.value);
                reg2 = 3;
            }else{
                reg2 = reg_allocate(i->op[2]);
            }
            for(int i=8;i<26;i++){
                    reg_spill(i);
            }
            if(!strcmp(i->op[1]->u.name,"==")){

                fprintf(fs,"beq $%d, $%d, ",reg1,reg2);
            }else if(!strcmp(i->op[1]->u.name,"!=")){
                fprintf(fs,"bne $%d, $%d, ",reg1,reg2);
            }else if(!strcmp(i->op[1]->u.name,">")){
                fprintf(fs,"bgt $%d, $%d, ",reg1,reg2);
            }else if(!strcmp(i->op[1]->u.name,"<")){
                fprintf(fs,"blt $%d, $%d, ",reg1,reg2);
            }else if(!strcmp(i->op[1]->u.name,">=")){
                fprintf(fs,"bge $%d, $%d, ",reg1,reg2);
            }else if(!strcmp(i->op[1]->u.name,"<=")){
                fprintf(fs,"ble $%d, $%d, ",reg1,reg2);
            }else{
                assert(0);
            }
            p = p->next;
            i = p->code;
            fprintf(fs,"%s\n",i->op[0]->u.name);
            i->op[0]->tmp_num = Sp_offset;
            if(p->next->code->kind == GOTO_IR){
                p->next->code->op[0]->tmp_num = Sp_offset;
            }
            break;
        }
        case ARG_IR:{
            param_insert(i->op[0]);
            break;
        }
        case CALL_IR:{        //??????????
            for(int i=8;i<26;i++){
                reg_spill(i);
            }
            //压参
            int reg = reg_allocate(i->op[0]);
            int karg = 0;
            Operandlist* cur = paramlist->next;
            while(cur!=NULL){
                karg++;
                if(karg<=4){
                    int tmp = karg-1+4;
                    //reg_spill(tmp);
                    int rreg;
                    if(cur->op->kind == CONSTANT_OP){
                        rreg=2;
                        code("li $v0, %d\n",cur->op->u.value);
                    }else{
                        int num = findnum(cur->op);
                        code("lw $v0, %d($fp)\n",-varsymbol[num].offset);
                        rreg=2;
                    }
                    
                    //mipreg[tmp].var_num = findnum(cur->op);
                    code("move $%d, $%d\n",karg+3,rreg);

                }else{
                    int rreg;
                    if(cur->op->kind == CONSTANT_OP){
                        rreg=2;
                        code("li $v0, %d\n",cur->op->u.value);
                    }else{
                        int num = findnum(cur->op);
                        code("lw $v0, %d($fp)\n",-varsymbol[num].offset);
                        rreg= 2;
                    }
                    code("addi $sp, $sp, -4\n");
                    code("sw $%d, 0($sp)\n",rreg);
                }
                cur=cur->next;
            }
            param_free();
            fprintf(fs,"addi $sp, $sp, -8\n");
            fprintf(fs,"sw $fp, 0($sp)\n");
            fprintf(fs,"sw $ra, 4($sp)\n");
            //code("move $fp, $sp\n");
            fprintf(fs,"jal %s\n",i->op[1]->u.name);
            fprintf(fs,"addi $sp, $sp, 4\n");
            fprintf(fs,"lw $ra, 0($sp)\n");
            fprintf(fs,"addi $sp, $sp, 4\n");
            //fprintf(fs,"addi $sp, $fp, -%d\n",Sp_offset);
            fprintf(fs,"move $%d, $v0\n",reg);
            //printf("heh4\n");
            break;
        }
        case FUNC_IR:{    //??????????????/大问题
            code("%s :\n",i->op[0]->u.name);
            code("move $fp, $sp\n");
            for(int i=8;i<26;i++){
                if(mipreg[i].free){
                    mipreg[i].free = 0;
                    int varnum = mipreg[i].var_num;
                    varsymbol[varnum].reg = 0;
                }
            }
            Sp_offset = 0;
            int cout = 0;
            int totalcout = Search(i->op[0]->u.name)->type->u.func.num;
            p = p->next;
            while(p->code->kind == PARAM_IR){
                cout++;
                if(cout<=4){
                    int reg = reg_allocate(p->code->op[0]);
                    code("move $%d, $%d\n",reg,cout+3);
                }else{
                    int reg = reg_allocate(p->code->op[0]);
                    code("lw $%d, %d($fp)\n",reg,(totalcout-cout)*4+8);
                }
                p= p->next;
            }
            
            continue;
            break;
        }
        
        case RETURN_IR:{
            if(i->op[0]->kind == CONSTANT_OP){
                fprintf(fs,"li $v0, %d\n",i->op[0]->u.value); 
            }else{
                int reg = reg_allocate(i->op[0]);
                fprintf(fs,"move $v0, $%d\n",reg); 
            }
            for(int i=8;i<26;i++){  //????????
                reg_spill(i);
            }
            fprintf(fs,"move $sp, $fp\n");
            fprintf(fs,"lw $fp, 0($sp)\n");

            fprintf(fs,"jr $ra\n");
            break;
        }
        
        
        
        
       
        default:
            break;
        }
        p = p->next;   
    }
}