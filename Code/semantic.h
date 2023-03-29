#include "N_tree.h"
#define HASHSIZE 1024
typedef struct Type_ Type;
typedef struct FieldList_ FieldList;
typedef struct Element_ Element;
struct Type_{
    enum {
        BASIC,
        ARRAY,
        STRUCTURE,
        FUNC
    } kind;
    union{
        int basic;  //基本数据类型 int float
        struct{    //数组类型包括元素类型和大小
            Type* elem;
            int size;
        } array;
        FieldList* structure;
        struct{
            int num;
            Type* retval;
            FieldList* args;
            int state;       //该函数当前的状态：声明/定义
        }func;
    } u;
};
struct FieldList_{
    char* name;    //域的名字
    Type* type;     //域的类型
    FieldList* next;//下一个
};
struct Element_{
    char* name;
    Type* type;
    Element* next;
    int dep;          //符号的深度
};


//hash table
unsigned int hash_pjw(char* );
Element* Search(char* );
void Insert(Element* );
void Delete(Element* );

//SDT
void semantic(Tnode* );