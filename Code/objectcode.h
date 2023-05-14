#include "intercode.h"

typedef struct instruction_ instruction;
typedef struct reg_ Reg;
typedef struct var_ Var;
typedef struct Operandlist_ Operandlist;
struct instruction_{
    enum{
        ITYPE,RTYPE,JTYPE,
    }kind;
};

struct reg_{
    //char* name;
    int free; //0 free 1 alloc
    int offset; //相对于$fp的偏移量 
    int var_num; //所分配的变量名
};
struct var_{
    int reg;
    int offset;
    int nextuse;
    int lastuse;
};
struct Operandlist_{
    Operand op;
    Operandlist* next;
};

typedef struct Baseblock_ Baseblock;

struct Baseblock_{
    InterCodes begin;
    InterCodes end;
};
void reg_init();
void var_init();
void param_init();
void param_insert(Operand op);
void param_free();
void obj_init();
int findnum(Operand op);
void reg_spill(int regnum);
void reg_free(int regnum);
int reg_allocate(Operand op);
void baseblock_split();
void objectcode(char* filename);
void gen_mipcode(char* filename);
void useanaly(Operand op,int knum);

