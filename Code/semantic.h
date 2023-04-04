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
        STRUCTVAR,
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
            int num;         //参数个数
            Type* retval;    //返回类型
            FieldList* args; //参数类型
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
void Program(Tnode* s);
void Extdeflist(Tnode *s);
void Extdef(Tnode* s);
FieldList* Fundec(Tnode* s,Type* t);
FieldList* Varlist(Tnode* s);
FieldList* Paramdec(Tnode* s);
void Extdeclist(Tnode* s,Type* t);
FieldList* Vardec(Tnode* s,Type* t);
Type* Specifier(Tnode* s);
Type* Structspecifier(Tnode* s);
char* Tag(Tnode* s);
char* Opttag(Tnode* s);
void Compst(Tnode* s,FieldList* f);
FieldList* Deflist(Tnode* s,Type* t);