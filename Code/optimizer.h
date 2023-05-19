#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
typedef struct Operand_* Operand;
typedef struct Operand_ Operand_d;
typedef struct InterCode_* InterCode;
typedef struct InterCode_ InterCode_d;
typedef struct BasicBlock_ BasicBlock_d;
typedef struct BasicBlock_* BasicBlock;
typedef struct DAGNode_ DAGNode_d;
typedef struct DAGNode_* DAGNode;
//操作数的定义
struct Operand_ {
    enum { VARIABLE_OP,TMPVAR_OP,CONSTANT_OP,GETADDR_OP, GETVAL_OP,LABEL_OP,FUNC_OP} kind;
    union {
        int no;//变量v、临时t、标号label的序号
        char* name;//函数名
        int value;//常量CONSTANT的数值
        Operand op;//取地址和解引用使用的操作数
    } u;
};
//中间代码链表的数据结构定义
struct InterCode_{
    enum { LABEL_IR,FUNC_IR,ASSIGN_IR,ADD_IR,SUB_IR,MUL_IR,DIV_IR,GOTO_IR,IFGOTO_IR,RETURN_IR,DEC_IR,ARG_IR,CALL_IR,PARAM_IR,READ_IR,WRITE_IR } kind; //指令类型,_IR防止重命名
    Operand op[3];//操作数（指针）op[0]是result
    union{
        char* relop;
        int decsize;
    }e;//附加信息,relop的内容
    struct InterCode_ *prev;
    struct InterCode_ *next;
};

//基本块的数据结构
struct BasicBlock_ {
    int no;//序号
    struct InterCode_* codehead;//中间代码的链表头
    struct InterCode_* codetail;//中间代码的链表头
    int prenum;//前驱数量
    struct BasicBlock_ **prev;//前驱很多,用数组
    struct BasicBlock_ *next[2]; //后驱的基本块最多就两个（因为IF），记录两个指针
};

struct DAGNode_{
    enum {
        ASSIGN_NODE, ADD_NODE, SUB_NODE, MUL_NODE, DIV_NODE, LEAF_NODE
    } kind; // 节点的类型
    Operand op;//节点上的操作数
    DAGNode leftchild,rightchild;//左右子树
};
void readinput(char* filename);
void optimize();
void printoutput(char *filename);
