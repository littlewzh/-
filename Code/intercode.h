#include"semantic.h"
extern Tnode* root;
typedef struct Operand_* Operand;
typedef struct Operand_ Operand_d;
typedef struct InterCode_* InterCode;
typedef struct InterCode_ InterCode_d;
typedef struct InterCodes_* InterCodes;
//操作数的定义
struct Operand_ {
    enum { VARIABLE_OP,TMPVAR_OP,CONSTANT_OP,NUMBER_OP,GETADDR_OP,GETADDRTMP_OP, GETVAL_OP,GETVALTMP_OP,FUNC_OP} kind;
    union {
        char* name;//变量名字
        int value;//常量数值
    } u;
};
//单条中间代码的数据结构定义
struct InterCode_{
    enum { LABEL_IR,FUNC_IR,ASSIGN_IR,ADD_IR,SUB_IR,MUL_IR,DIV_IR,GOTO_IR,IFGOTO_IR,RETURN_IR,DEC_IR,ARG_IR,CALL_IR,PARAM_IR,READ_IR,WRITE_IR } kind; //指令类型,_IR防止重命名
    Operand op[3];//操作数（指针）op[0]是result
};
//所有的中间代码用双向链表形式存储
struct InterCodes_ {
    struct InterCode_* code; 
    struct InterCodes_ *prev;
    struct InterCodes_ *next; 
};
void InterCodes_init();
void PrintInterCode(char *filename);
void PrintOperand(Operand op);
void Translate_Program(Tnode* s);
void Translate_Extdeflist(Tnode *s);
void Translate_Extdef(Tnode *s);
void Translate_FunDec(Tnode *s);
void Translate_VarList(Tnode *s);
void Translate_CompSt(Tnode *s);
void Translate_DefList(Tnode *s);
void Translate_Def(Tnode *s);
void Translate_DecList(Tnode *s);
void Translate_Dec(Tnode *s);
void Translate_StmtList(Tnode *s);
void Translate_Stmt(Tnode *s);
void Translate_Exp(Tnode *s,Operand place);
int fuckstructsize(Type* t,char* dotname);
int ArraySize(Type* t,int n);
int SizeofType(Type* t);
void Translate_Args(Tnode *s);
void TranslateExpCond(Tnode *s,Operand place);
void Translate_Cond(Tnode *s,Operand L1,Operand L2);
