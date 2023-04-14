#include "semantic.h"

#define Error(n,line) printf("Error type %d at Line %d:\n",n,line)
//#define CHECKHASHTABLE
#ifdef CHECKHASHTABLE
#define PRINTTABLE printhash();
#else
#define PRINTTABLE assert(1)
#endif
//#define SEMANTIC
#ifdef SEMANTIC
#define sdebug(...) printf(__VA_ARGS__)
#else
#define sdebug(...) assert(1)
#endif
#define CHECK printf("here\n")
//清除该作用域中定义的变量
#define CLEARSCOPE(f) \
    if(f!=NULL){      \
        FieldList* tmp=f; \
        while(tmp!=NULL){  \
            Element* e = Search(tmp->name);\
            Delete(e);    \
            tmp=tmp->next; \
        }\
    }
//extern struct treenode;
Element* Hashtable[HASHSIZE+1];
int Dep;  //用于实现作用与
unsigned int hash_pjw(char* name){
    unsigned int val =0,i;
    for(;*name;++name){
        val = (val<<2)+*name;
        if(i = val & ~0x3fff)  val = (val ^ (i >> 12)) & 0x3fff;
    }
    return val;
}
void inithash(){
    for(int i=0;i<= HASHSIZE;i++){
        Hashtable[i]=NULL;
    }
}
void printhash(){
    printf("|--------------------------|\n");
    printf("| HASHTABLE ELEMENT        |\n"); //26
    printf("|--------------------------|\n");
    printf("| %-8s| %-5s| %-6s  |\n","name","type","line");
    printf("|--------------------------|\n");
    for(int i=0;i<= HASHSIZE;i++){
        if(Hashtable[i]!=NULL){
            Element* e = Hashtable[i];
            while(e!=NULL){
    printf("| %-8s| %-5d| %-6d  |\n",e->name,e->type->kind,e->line);
                e = e->next;
            }
        }
    }
    printf("|--------------------------|\n");
    printf("\n");
}
FieldList* creatFieldList(char* s,Type* t,FieldList* ne){
    FieldList* f = malloc(sizeof(FieldList));
    f->name = s;
    f->next = ne;
    f->type = t;
    return f;
}
Element* createlement(char* n,Type* t,int d,int l){
    Element* e = malloc(sizeof(Element));
    e->name=n;
    e->type=t;
    e->dep=d;
    e->line=l;
    return e;
}
Element* Search(char* name){
    unsigned int key=hash_pjw(name);
    Element head;
    head.next = Hashtable[key];
    Element* cur = &head;
    while(cur->next!=NULL){
        if(strcmp(name,cur->next->name)==0) return cur->next;
        cur=cur->next;
    }
    return NULL;
}
void Insert(Element *s){
    unsigned int key=hash_pjw(s->name);
    //CHECK;
    s->next = Hashtable[key];
    Hashtable[key] = s;

}
void Delete(Element *s){
    unsigned int key=hash_pjw(s->name);
    if(Hashtable[key]==s){
        Hashtable[key] = s->next;
        return;
    }
    Element head;
    head.next = Hashtable[key];
    Element* cur = &head;
    while(cur->next!=NULL){
        if(cur->next == s){
            cur->next = s->next;
            break;
        }
    }
}
int equvilence(Type* t1,Type* t2){
    //数组等价
    //结构体等价
    //函数定义声明等价
    assert(t1!=NULL);
    assert(t2!=NULL);
    int flag=1;
    if(t1->kind!=t2->kind){
        flag=0;
        return flag;
    }else{  //t1->kind==t2->kind
        switch(t1->kind){
            case BASIC:
                if(t1->u.basic!=t2->u.basic) flag=0;
                break;
            case ARRAY:
                flag = equvilence(t1->u.array.elem,t2->u.array.elem);
                break;
            case STRUCTVAR:
            {
                FieldList* f1 = t1->u.structure;
                FieldList* f2 = t2->u.structure;
                while(f1!=NULL&&f2!=NULL){
                    if(!equvilence(f1->type,f2->type)) {flag=0;break;}
                    f1=f1->next;
                    f2=f2->next;
                }
                if(f1!=NULL||f2!=NULL) flag=0;
                break;
            }
            case FUNC:
            {
                //判断返回类型
                if(!equvilence(t1->u.func.retval,t2->u.func.retval)) {flag=0;break;}
                //判断函数参数
                if(t1->u.func.num!=t2->u.func.num) {flag=0;break;}
                FieldList* a1 = t1->u.func.args;
                FieldList* a2 = t2->u.func.args;
                while(a1!=NULL&&a2!=NULL){
                    if(!equvilence(a1->type,a2->type)) {flag=0;break;}
                    a1=a1->next;
                    a2=a2->next;
                }
                break;
            }
            default: printf("undefined equvilence\n");
        }
        return flag;
    }

}
void checkfunc(FieldList* f){  //检查函数是否定义
    if(f!=NULL){
        while(f!=NULL){
            Element* e = Search(f->name);
            if(e!=NULL && e->type->kind==FUNC){
                if(e->type->u.func.state!=DEF){
                    Error(18,e->line);//函数进行了声明，但没有被定义。
                    return ;
                }
            }
            f=f->next;
        }
    }
}
int judge(Tnode* s,int num,...){  //判断某个结点的子产生式是否为“”，“”，。。。
    va_list valist;
    va_start(valist,num);
    Tnode* cur=s->firstchild;
    for(int i=0;i<num;i++){
        char* tmp = va_arg(valist,char*);
        if(cur==NULL) return 0;
        //printf("%s\n%s\n",tmp,cur->name);
        if(strcmp(cur->name,tmp)!=0) return 0;
        cur=cur->nextbro;
    }
    va_end(valist);
    if(cur!=NULL) return 0;
    return 1;
}

void semantic(Tnode *s){
    Dep=0;
    inithash();
    Program(s);
    PRINTTABLE;
}

void Program(Tnode* s){
    sdebug("program\n");
    assert(strcmp(s->name,"Program")==0);
    Dep++;
    FieldList* f=NULL;
    if(!strcmp(s->firstchild->name,"ExtDefList")) f=Extdeflist(s->firstchild);
    Dep--;
    //CHECK;
    checkfunc(f);
    assert(Dep==0);
}
FieldList* Extdeflist(Tnode *s){
    sdebug("Extdeflist\n");
    assert(strcmp(s->name,"ExtDefList")==0);
    Tnode* cur = s->firstchild;
    FieldList* f= NULL;
    if(!strcmp(cur->name,"ExtDef")) f=Extdef(cur);
    cur = cur->nextbro;
    if(cur!=NULL){
        assert(!strcmp(cur->name,"ExtDefList"));
        if(f==NULL){return Extdeflist(cur);}
        else{
            FieldList* tmp=f;
            while(tmp->next!=NULL) tmp=tmp->next;
            tmp->next = Extdeflist(cur);
        }
    }
    return f;
}
FieldList* Extdef(Tnode* s){
    sdebug("Extdef\n");
    assert(strcmp(s->name,"ExtDef")==0);
    Tnode* cur = s->firstchild;
    Type* def=NULL;
    if(!strcmp(cur->name,"Specifier")) {
        def = Specifier(cur);
        if(def == NULL) return NULL;  //appear error
    }
    if(def->kind == STRUCTURE) def->kind = STRUCTVAR;
    cur = cur->nextbro;
    if(cur!=NULL){
        if(!strcmp(cur->name,"SEMI")){
            return NULL;
        }else if(!strcmp(cur->name,"ExtDecList")){
            //Specifier ExtDecList SEMI
            return Extdeclist(cur,def);
        }else{
            FieldList* f=NULL;
            if(!strcmp(cur->nextbro->name,"SEMI")){
            //Specifier FunDec SEMI
                f=Fundec(cur,def,0); //声明
                PRINTTABLE;
                if(f!=NULL){ CLEARSCOPE(f->type->u.func.args)} //作用域相关
            }else{
            //Specifier FunDec CompSt
                f=Fundec(cur,def,1);  //定义
                if(f==NULL) return NULL;
                cur = cur->nextbro;
                Compst(cur,f);
                PRINTTABLE;
                if(f!=NULL){ CLEARSCOPE(f->type->u.func.args)}  //作用域相关
               //CHECK;
            }
            return f;
        }
    }
}
FieldList* Fundec(Tnode* s,Type* t,int state){  //state==1 定义；state==0 声明
    sdebug("Fundec\n");
    assert(strcmp(s->name,"FunDec")==0);
    Tnode* cur = s->firstchild;
    Element* e = Search(cur->s_val);
    if(e!=NULL){    //hash表里有相同的函数名
        if(e->type->kind==FUNC && e->type->u.func.state==DEF){
            if(state){
                Error(4,cur->line); //函数出现重复定义（即同样的函数名出现了不止一次定义
                return NULL;
            }else{
                Type* t1=e->type;              //符号表里的函数类型
                Type* t2 = malloc(sizeof(Type));  //分析当前节点的函数类型
                t2->kind = FUNC;
                t2->u.func.retval=t;
                t2->u.func.num=0;
                cur = childth_node(s,3);
                if(!strcmp(cur->name,"VarList")){
                    FieldList *l = Varlist(cur);
                    t2->u.func.args = l;
                    while(l!=NULL){
                        t2->u.func.num++;
                        l=l->next;
                    }
                }
                if(!equvilence(t1,t2)){
                    Error(19,cur->line);//函数的多次声明互相冲突（即函数名一致，但返回类型、形参数量
                    return NULL;                    //或者形参类型不一致），或者声明与定义之间互相冲突。
                }
                //e->type->u.func.state = state ? DEF:DEC_UNDEF;
                t1->u.func.args = t2->u.func.args;
                FieldList* ret = creatFieldList(e->name,t1,NULL); //构造返回类型（函数名，函数类型）
                return ret;
            }
            
        }else if(e->type->kind==FUNC &&e->type->u.func.state==DEC_UNDEF){
            Type* t1=e->type;              //符号表里的函数类型
            Type* t2 = malloc(sizeof(Type));  //分析当前节点的函数类型
            t2->kind = FUNC;
            t2->u.func.retval=t;
            t2->u.func.num=0;
            cur = childth_node(s,3);
            if(!strcmp(cur->name,"VarList")){
                FieldList *l = Varlist(cur);
                t2->u.func.args = l;
                while(l!=NULL){
                    t2->u.func.num++;
                    l=l->next;
                }
            }
            if(!equvilence(t1,t2)){
                Error(19,cur->line);//函数的多次声明互相冲突（即函数名一致，但返回类型、形参数量
                return NULL;                    //或者形参类型不一致），或者声明与定义之间互相冲突。
            }
            e->type->u.func.state = state ? DEF:DEC_UNDEF;
            t1->u.func.args = t2->u.func.args;
            FieldList* ret = creatFieldList(e->name,t1,NULL); //构造返回类型（函数名，函数类型）
            return ret;
        }else{
            assert(1);
        }
    }else{  //hash表里没有该符号名
        Type* fun = malloc(sizeof(Type));
        fun->kind = FUNC;
        fun->u.func.retval=t;
        fun->u.func.num=0;
        fun->u.func.state = state ? DEF:DEC_UNDEF;
        cur = childth_node(s,3);
        if(!strcmp(cur->name,"VarList")){   //该函数有变量
            Dep++;                          //继续分析函数的参数，此时作用域+1
            FieldList *l = Varlist(cur);
            Dep--;
            fun->u.func.args = l;
            while(l!=NULL){
                fun->u.func.num++;
                l=l->next;
            }
        }
        e = createlement(s->firstchild->s_val,fun,Dep,cur->line);
        Insert(e);   //将该符号插入符号表
        FieldList* ret = creatFieldList(e->name,fun,NULL); //构造返回类型（函数名，函数类型）
        return ret;
    }
}
FieldList* Varlist(Tnode* s){
    sdebug("Varlist\n");
    assert(strcmp(s->name,"VarList")==0);
    Tnode* cur = s->firstchild;
    FieldList *l = NULL;
    l = Paramdec(cur);
    cur = cur->nextbro;
    if(cur!=NULL){
        cur = cur->nextbro;
        l->next = Varlist(cur);
    }
    return l;
}
FieldList* Paramdec(Tnode* s){
    sdebug("Paramdec\n");
    assert(strcmp(s->name,"ParamDec")==0);
    Tnode* cur = s->firstchild;
    Type *def = Specifier(cur);
    cur = cur->nextbro;
    return Vardec(cur,def,0);
}
FieldList* Extdeclist(Tnode* s,Type* t){
    sdebug("Extdeclist\n");
    assert(strcmp(s->name,"ExtDecList")==0);
    Tnode *cur=s->firstchild;
    FieldList* f=NULL;
    if(!strcmp(cur->name,"VarDec")){ f=Vardec(cur,t,0);}
    cur = cur->nextbro;
    if(cur!=NULL){
        // VarDec COMMA ExtDecList
        cur=cur->nextbro;
        assert(strcmp(cur->name,"ExtDecList"));
        if(f==NULL) {return Extdeclist(cur,t);}
        else{
            f->next = Extdeclist(cur,t);
        }
    }
    return f;
}
FieldList* Vardec(Tnode* s,Type* t,int flag){ //flag==1 结构体 ；flag==0 函数体
    sdebug("Vardec\n");
    assert(strcmp(s->name,"VarDec")==0);
    Tnode *cur = s->firstchild;
    if(!strcmp(cur->name,"ID")){         
        Element* e=Search(cur->s_val);
        if(e!=NULL){                 //在哈希表中查到同名符号
            switch (t->kind){        //分析当前符号的类型
            case BASIC:
            case STRUCTVAR:
            case ARRAY:
            {   //当前符号为变量类型（普通变量，数组变量，结构体变量）
                //assert(e->dep>Dep);
                if(e->dep == Dep || e->type->kind==STRUCTURE){  //当前变量与之前的符号位于同一层作用域，或着之前的符号为结构体名
                    if(flag==0) Error(3,cur->line);//变量出现重复定义，或变量与前面定义过的结构体名字重复。
                    else Error(15,cur->line);  //结构体中域名重复定义（指同一结构体中）
                    break;
                }else{           //此时虽然符号名重复，但由于作用域的影响，不冲突
                    assert(e->dep<Dep);   
                    Element* new_e = createlement(cur->s_val,t,Dep,cur->line);
                    Insert(new_e);    //插入符号表
                    FieldList* ret = creatFieldList(cur->s_val,t,NULL);//构造返回类性（ID+类型）
                    return ret;
                }
            }
            case STRUCTURE:   //???????????????
                Error(16,cur->line);//结构体的名字与前面定义过的结构体或变量的名字重复。
                break;
            default:
                break;
            }
            return NULL;
        }else{             //在哈希表中没有同名符号
            e = createlement(cur->s_val,t,Dep,cur->line);
            Insert(e);
            FieldList* ret = creatFieldList(cur->s_val,t,NULL);
            return ret;
        }
        assert(0);
    }else{  //数组类型变量
        int size = childth_node(s,3)->i_val;
        Type* new_t = malloc(sizeof(new_t));
        new_t->kind = ARRAY;
        new_t->u.array.size=size;
        new_t->u.array.elem=t;
        return Vardec(cur,new_t,flag);
    }
}
Type* Specifier(Tnode* s){
    sdebug("Specifier\n");
    assert(strcmp(s->name,"Specifier")==0);
    Tnode* cur = s->firstchild;
    Type* t = NULL;
    if(!strcmp(cur->name,"TYPE")){
        t = malloc(sizeof(Type));
        if(!strcmp(cur->s_val,"int")){
            t->kind = BASIC;
            t->u.basic = 1;   //int
        }else{
            t->kind = BASIC;
            t->u.basic = 2;   //float
        }
    }else if(!strcmp(cur->name,"StructSpecifier")){
        t = Structspecifier(cur);
    }
    return t;
}
Type* Structspecifier(Tnode* s){
    sdebug("Structspecifier\n");
    assert(strcmp(s->name,"StructSpecifier")==0);
    Tnode* cur = s->firstchild;
    assert(strcmp(cur->name,"STRUCT")==0);
    cur=cur->nextbro;
    if(!strcmp(cur->name,"Tag")){
        // STRUCT Tag
        char *id = Tag(cur);
        Element* e = Search(id);
        if(e==NULL){
            Error(17,s->line);   //直接使用未定义过的结构体来定义变量。
            return NULL;
        }else{
            Type* ret = malloc(sizeof(Type));  //构造返回类型
            ret->kind = STRUCTVAR;
            ret->u.structure = e->type->u.structure;
            assert(e->type->kind==STRUCTURE);
            return ret;
        }
    }else{
        // STRUCT OptTag LC DefList RC
        if(!strcmp(cur->name,"OptTag")){  //OptTag != NULL
            char *id = Opttag(cur);
            Element* e = Search(id);
            if(e!=NULL){
                Error(16,cur->line);  //结构体的名字与前面定义过的结构体或变量的名字重复
                return NULL;
            }else{
                Type* t = malloc(sizeof(Type));
                t->kind = STRUCTURE;
                Tnode* node = childth_node(s,4);
                Dep++;
                t->u.structure = Deflist(node,t,1);
                Dep--;
                PRINTTABLE;
                CLEARSCOPE(t->u.structure)
                e = createlement(id,t,Dep,cur->line);
                Insert(e);
                //CHECK;
                Type* ret = malloc(sizeof(Type));
                ret->kind = STRUCTVAR;
                ret->u.structure = t->u.structure;
                return ret;
            }
        }else{
            Type* t = malloc(sizeof(Type));
            t->kind = STRUCTURE;
            Tnode* node = childth_node(s,3);
            Dep++;
            t->u.structure = Deflist(node,t,1);
            Dep--;
            PRINTTABLE;
            CLEARSCOPE(t->u.structure)
            return t;
        }
    }
}
char* Tag(Tnode* s){
    assert(strcmp(s->name,"Tag")==0);
    Tnode* cur = s->firstchild;
    assert(strcmp(cur->name,"ID")==0);
    return cur->s_val;
}
char* Opttag(Tnode* s){
    assert(strcmp(s->name,"OptTag")==0);
    Tnode* cur = s->firstchild;
    assert(strcmp(cur->name,"ID")==0);
    return cur->s_val;
}
void Compst(Tnode* s,FieldList* f){
    sdebug("Compst\n");
    assert(strcmp(s->name,"CompSt")==0);
    Dep++;
    Tnode* cur = s->firstchild;
    cur = cur->nextbro;
    FieldList* h=NULL;
    if(!strcmp(cur->name,"DefList")) h=Deflist(cur,f->type,0);
    else if(!strcmp(cur->name,"StmtList")) Stmtlist(cur,f->type);
    cur = cur->nextbro;
    if(cur!=NULL){
        if(!strcmp(cur->name,"StmtList")) Stmtlist(cur,f->type);
    }
    Dep--;
    PRINTTABLE;
    CLEARSCOPE(h)
}
FieldList* Deflist(Tnode* s,Type* t,int flag){
    sdebug("Deflist\n");
    assert(strcmp(s->name,"DefList")==0);
    Tnode* cur = s->firstchild;
    FieldList* f = NULL;
    if(!strcmp(cur->name,"Def")) f=Def(cur,t,flag);
    cur = cur->nextbro;
    if(cur != NULL){
        assert(!strcmp(cur->name,"DefList"));
        if(f==NULL) {return Deflist(cur,t,flag);}
        else{
            FieldList* tmp =f;
            while(tmp->next!=NULL) tmp=tmp->next;
            tmp->next = Deflist(cur,t,flag);
            //CHECK;
        }
    }
    return f;
}
FieldList* Def(Tnode* s,Type* t,int flag){
    sdebug("Def\n");
    assert(strcmp(s->name,"Def")==0);
    Tnode* cur = s->firstchild;
    Type* def = NULL;
    if(!strcmp(cur->name,"Specifier")) {
        def = Specifier(cur);
        if(def==NULL) return NULL;
    }
    if(def->kind==STRUCTURE) def->kind==STRUCTVAR;
    cur = cur->nextbro;
    if(cur!=NULL){
        assert(strcmp(cur->name,"DecList")==0);
        //CHECK;
        return Declist(cur,def,flag);
    }
    
}
FieldList* Declist(Tnode* s,Type* t,int flag){
    sdebug("Declist\n");
    assert(strcmp(s->name,"DecList")==0);
    Tnode* cur = s->firstchild;
    FieldList *f=NULL;
    if(!strcmp(cur->name,"Dec")) f = Dec(cur,t,flag);
    cur = cur->nextbro;
    if(cur!=NULL){
        cur = cur->nextbro;
        assert(!strcmp(cur->name,"DecList"));
        if(f==NULL) {return Declist(cur,t,flag);}
        else{
            f->next = Declist(cur,t,flag);
        }
    }
    //CHECK;
    return f;
}
FieldList* Dec(Tnode* s,Type* t,int flag){
    sdebug("Dec\n");
    assert(strcmp(s->name,"Dec")==0);
    Tnode* cur = s->firstchild;
    FieldList* f=NULL;
    if(!strcmp(cur->name,"VarDec")){
        f=Vardec(cur,t,flag);
    }
    cur=cur->nextbro;
    if(cur!=NULL){
        if(flag) {Error(15,cur->line);return f;}//结构体中域名重复定义（指同一结构体中），或在定义时对域进
                                    //行初始化（例如struct A { int a = 0; }）。
        //Error
        Type* tt = Exp(cur->nextbro);
        if(tt!=NULL){
            if(!equvilence(tt,f->type)){
                Error(5,cur->line);
            }
        }
    }
    
    return f;
}
void Stmtlist(Tnode* s,Type* t){
    sdebug("Stmtlist\n");
    assert(strcmp(s->name,"StmtList")==0);
    Tnode* cur = s->firstchild;
    if(!strcmp(cur->name,"Stmt")) Stmt(cur,t);
    cur = cur->nextbro;
    if(cur!=NULL){
        Stmtlist(cur,t);
    }
}
void Stmt(Tnode* s,Type* t){
    sdebug("Stmt\n");
    assert(strcmp(s->name,"Stmt")==0);
    Tnode* cur = s->firstchild;
    FieldList* f =malloc(sizeof(FieldList));
    f->type=t;
    if(!strcmp(cur->name,"Exp")){
        Exp(cur);//
    }else if(!strcmp(cur->name,"CompSt")){
        Compst(cur,f);//
    }else if(!strcmp(cur->name,"RETURN")){
        //
        Type* tt = Exp(cur->nextbro);
        if(!equvilence(tt,t->u.func.retval)){
            Error(8,cur->line);   //return语句的返回类型与函数定义的返回类型不匹配。
        }
    }else if(!strcmp(cur->name,"IF")){
        //
        Type* tt = Exp(childth_node(s,3));
        if(tt!=NULL&&(tt->kind!=BASIC||tt->u.basic!=1)){
            Error(7,cur->line);
        }
        cur = childth_node(s,5);
        Stmt(cur,t);
        cur=cur->nextbro;
        if(cur!=NULL){
            cur=cur->nextbro;
            assert(strcmp(cur->name,"Stmt")==0);
            Stmt(cur,t);
        }
    }else{//WHILE
        assert(strcmp(cur->name,"WHILE"));
        //
        Type* tt = Exp(childth_node(s,3));
        if(tt->kind!=BASIC||tt->u.basic!=1){
            Error(7,cur->line);
        }
        Stmt(childth_node(s,5),t);
    }
}
Type* Exp(Tnode* s){
    sdebug("Exp\n");
    assert(strcmp(s->name,"Exp")==0);
    Tnode* cur = s->firstchild;
    if(!strcmp(cur->name,"INT")){
        Type* t = malloc(sizeof(Type));
        t->kind = BASIC;
        t->u.basic = 1;
        return t;
    }else if(!strcmp(cur->name,"FLOAT")){
        Type* t = malloc(sizeof(Type));
        t->kind = BASIC;
        t->u.basic = 2;
        return t;
    }else if(!strcmp(cur->name,"LP")){
        cur = cur->nextbro;
        return Exp(cur);
    }else if(!strcmp(cur->name,"ID")){
        if(cur->nextbro==NULL){       //ID 
            char *id = cur->s_val;
            Element* e = Search(id);
            if(e ==NULL ){
                Error(1,cur->line);   //变量在使用时未经定义。
                return NULL;
            }else{
                return e->type;
            }
        }else{
            if(!strcmp(childth_node(s,3)->name,"Args")){  //ID LP Args RP
                char *id = cur->s_val;
                Element* e = Search(id);
                if(e==NULL){
                    Error(2,cur->line);//函数在调用时未经定义或声明。
                    return NULL;
                }else{
                    switch(e->type->kind){
                        case BASIC:case STRUCTVAR:case ARRAY:
                            Error(11,cur->line);//对普通变量使用“(…)”或“()”（函数调用）操作符。
                            return NULL;
                            break;
                        case FUNC:{
                            Tnode* tmp=childth_node(s,3);
                            FieldList* f=Args(tmp);
                            if(f==NULL) return NULL;
                            FieldList* ff = e->type->u.func.args;
                            int flag=0;
                            while(f!=NULL&&ff!=NULL){         //判断函数的实参和形参是否等价
                                if(!equvilence(f->type,ff->type)) flag=1;
                                f=f->next;
                                ff=ff->next;
                            }
                            if(f!=NULL||ff!=NULL) flag=1;
                            if(flag){
                                Error(9,cur->line); //函数调用时实参与形参的数目或类型不匹配。
                                return NULL;
                            }
                            break;
                        }
                            
                        default: sdebug("Undefined error\n");return NULL;
                    }
                    return e->type->u.func.retval;
                }
            }else{                        //ID LP RP 
                char *id = cur->s_val;
                Element* e = Search(id);
                if(e==NULL){
                    Error(2,cur->line);//函数在调用时未经声明和定义。
                    return NULL;
                }else{
                    switch(e->type->kind){
                        case BASIC:case STRUCTVAR:case ARRAY:
                            Error(11,cur->line);//对普通变量使用“(…)”或“()”（函数调用）操作符。
                            return NULL;
                            break;
                        case FUNC:
                            if(e->type->u.func.num!=0){
                                Error(8,cur->line); //函数调用时实参与形参的数目或类型不匹配。
                                return NULL;
                            }
                            break;
                        default: sdebug("Undefined error\n");return NULL;
                    }
                    return e->type->u.func.retval;
                }
            }
            
        }
    }else if(!strcmp(cur->name,"MINUS")){
        Type* tt = Exp(cur->nextbro);
        if(tt==NULL) return NULL;
        if(tt->kind!=BASIC){
            Error(7,cur->line);
            return NULL;
        }
        return tt;
    }else if(!strcmp(cur->name,"NOT")){
        cur = cur->nextbro;
        assert(strcmp(cur->name,"Exp"));
        Type* t = Exp(cur);
        if(t==NULL) return NULL;
        if(t->kind!=BASIC || t->u.basic!=1){
            Error(7,cur->line);
            return NULL;
        }
        return t;
    }else if(!strcmp(cur->name,"Exp")){
        Tnode* op=cur->nextbro;
        if(!strcmp(op->name,"LB")){
            Type* tt = Exp(op->nextbro);
            if(tt == NULL) return NULL;
            if(tt->kind!=BASIC || tt->u.basic!=1){
                Error(12,cur->line);  //数组访问操作符“[…]”中出现非整数（例如a[1.5]）。
                return NULL;
            }
            Type* t = Exp(cur);
            if(t == NULL) return NULL;
            if(t->kind!=ARRAY){
                Error(10,cur->line);  //对非数组型变量使用“[…]”（数组访问）操作符。
                return NULL;
            }
            return t->u.array.elem;
        }else if(!strcmp(op->name,"DOT")){
            char* id=op->nextbro->s_val;
            Type* t=Exp(cur);
            if(t==NULL){return NULL;}
            if(t->kind!=STRUCTVAR){
                //CHECK;
                Error(13,cur->line);  //对非结构体型变量使用“.”操作符。
                return NULL;
            }else{
                FieldList* struc = t->u.structure;
                int flag=1;
                while(struc!=NULL){
                    if(strcmp(struc->name,id)==0) {flag=0;break;}
                    struc = struc->next;
                }
                if(flag){
                    Error(14,cur->line);//访问结构体中未定义过的域。
                    return NULL;
                }
                return struc->type;
            }
        }else if(!strcmp(op->name,"OR")||!strcmp(op->name,"AND")){
            Type* t1 = Exp(cur);
            Type* t2 = Exp(op->nextbro);
            if(t1==NULL || t2==NULL){return NULL;}
            if(t1->kind!=BASIC || t1->u.basic!=1 || t2->kind!=BASIC||t2->u.basic!=1){
                Error(7,cur->line);
                return NULL;
            }
            return t1;

        }else if(!strcmp(op->name,"RELOP")){
            Type* t1 = Exp(cur);
            Type* t2 = Exp(op->nextbro);
            if(t1==NULL || t2==NULL){return NULL;}
            if(t1->kind!=BASIC || t2->kind!=BASIC){
                Error(7,cur->line);
                return NULL;
            }
            Type* ret = malloc(sizeof(Type));
            ret->kind = BASIC;
            ret->u.basic = 1;   //  比较运算返回int类型
            return t1;

        }else if(!strcmp(op->name,"PLUS")||!strcmp(op->name,"MINUS") ||!strcmp(op->name,"STAR") ||!strcmp(op->name,"DIV")){
            Type* t1 = Exp(cur);
            Type* t2 = Exp(op->nextbro);
            if(t1==NULL || t2==NULL){return NULL;}
            if((equvilence(t1,t2))&&(t1->kind==BASIC)){
                return t1;
            }
            Error(7,cur->line);
            return NULL;
        }else if(!strcmp(op->name,"ASSIGNOP")){  //赋值运算 ，比较复杂
            if((judge(cur,1,"ID")==0)&&(judge(cur,4,"Exp","LB","Exp","RB")==0)&&(judge(cur,3,"Exp","DOT","ID")==0)){
                Error(6,cur->line); //赋值号左边出现一个只有右值的表达式。
                return NULL;
            }
            Type* t1 = Exp(cur);
            Type* t2 = Exp(op->nextbro);
            if(t1==NULL || t2==NULL){return NULL;}
            if(!equvilence(t1,t2)){
                //此处的类型匹配还需要考虑数组和结构体
                Error(5,cur->line);  //赋值号两边的表达式类型不匹配。
                return NULL;
            }
            return t1;
            //error 6
        }else{
            printf("Undefined error:%d\n",cur->line);
            return NULL;
        }

    }
    printf("Undefined error:%d\n",cur->line);
    return NULL;
}
FieldList* Args(Tnode* s){
    sdebug("Args\n");
    assert(strcmp(s->name,"Args")==0);
    Tnode* cur = s->firstchild;
    Type* t = Exp(cur);
    if(t==NULL) return NULL;
    FieldList *f = malloc(sizeof(FieldList));
    f->type=t;
    cur=cur->nextbro;
    if(cur!=NULL){
        cur=cur->nextbro;
        f->next = Args(cur);
    }
    return f;
}