#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
typedef struct Operand_* Operand;
typedef struct Operand_ Operand_d;
typedef struct InterCode_* InterCode;
typedef struct InterCode_ InterCode_d;
typedef struct InterCodes_* InterCodes;
typedef struct BasicBlock_ BasicBlock_d;
typedef struct BasicBlock_* BasicBlock;
//操作数的定义
struct Operand_ {
    enum { VARIABLE_OP,TMPVAR_OP,CONSTANT_OP,GETADDR_OP, GETVAL_OP,LABEL_OP,FUNC_OP} kind;
    union {
        char* name;//变量名
        int value;//常量CONSTANT的数值
        //int no;//变量v临时t等的序号
    } u;
};
//单条中间代码的数据结构定义
struct InterCode_{
    enum { LABEL_IR,FUNC_IR,ASSIGN_IR,ADD_IR,SUB_IR,MUL_IR,DIV_IR,GOTO_IR,IFGOTO_IR,RETURN_IR,DEC_IR,ARG_IR,CALL_IR,PARAM_IR,READ_IR,WRITE_IR } kind; //指令类型,_IR防止重命名
    Operand op[3];//操作数（指针）op[0]是result
    struct InterCodes_ *prev;
    struct InterCodes_ *next;
};
//所有的中间代码用双向链表形式存储
struct InterCodes_ {
    struct InterCode_* code; 
    struct InterCodes_ *prev;
    struct InterCodes_ *next; 
};
//基本块的数据结构：双向链表
struct BasicBlock_ {
    int no;//序号,可以直接是label的序号？
    struct InterCodes_* code;//中间代码的链表头 
    struct BasicBlock_ **prev;//前置基本块有很多
    struct BasicBlock_ *next[2]; //后驱的基本块最多就两个（因为IF），记录两个指针
};
void readinput(char* filename);
void optimize();
void printoutput(char *filename);
