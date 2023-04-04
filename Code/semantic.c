#include "semantic.h"

#define Error(n,line) printf("Error type %d at Line %d:",n,line)

//extern struct treenode;
Element* Hashtable[HASHSIZE];

unsigned int hash_pjw(char* name){
    unsigned int val =0,i;
    for(;*name;++name){
        val = (val<<2)+*name;
        if(i = val & ~0x3fff)  val = (val ^ (i >> 12)) & 0x3fff;
    }
    return val;
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
    s->next = Hashtable[key];
    Hashtable[key] = s;

}
void Delete(Element *s){
    unsigned int key=hash_pjw(s->name);

}

void semantic(Tnode *s){
    
}
int judge(Tnode* s,int num,...){
    va_list valist;
    va_start(valist,num);
    Tnode* cur=s->firstchild;
    for(int i=0;i<num;i++){
        char* tmp = va_arg(valist,char*);
        if(strcmp(cur->name,tmp)!=0) return 0;
        cur=cur->nextbro;
        if(cur==NULL) return 0;
    }
    return 1;
}
void Program(Tnode* s){
    assert(strcmp(s->name,"Program")==0);
    if(!strcmp(s->firstchild->name,"ExtDeflist")) Extdeflist(s->firstchild);
}
void Extdeflist(Tnode *s){
    assert(strcmp(s->name,"ExtDeflist")==0);
    Tnode* cur = s->firstchild;
    if(!strcmp(cur->name,"ExtDef")) Extdef(cur);
    cur = cur->nextbro;
    if(cur!=NULL){
        if(!strcmp(cur->name,"ExtDeflist")) Extdeflist(cur);
    }
}
void Extdef(Tnode* s){
    assert(strcmp(s->name,"ExtDef")==0);
    Tnode* cur = s->firstchild;
    Type* def=NULL;
    if(!strcmp(cur->name,"Specifier")) {
        def = Specifier(cur);
        if(def == NULL) return;  //appear error
    }
    if(def->kind == STRUCTURE) def->kind = STRUCTVAR;
    cur = cur->nextbro;
    if(cur!=NULL){
        if(!strcmp(cur->name,"SEMI")){
            return;
        }else if(!strcmp(cur->name,"ExtDecList")){
            //Specifier ExtDecList SEMI
            Extdeclist(cur,def);
        }else{
            //Specifier FunDec CompSt
            FieldList* f=Fundec(cur,def);
            cur = cur->nextbro;
            Compst(cur,f);
        }
    }
}
FieldList* Fundec(Tnode* s,Type* t){
    assert(strcmp(s->name,"FunDec"));
    Tnode* cur = s->firstchild;
    Element* e = Search(cur->s_val);
    if(e!=NULL){
        Error(4,cur->line); //函数出现重复定义（即同样的函数名出现了不止一次定义
        return NULL;
    }else{
        Type* fun = malloc(sizeof(Type));
        fun->kind = FUNC;
        fun->u.func.retval=t;
        fun->u.func.num=0;
        cur = childth_node(s,3);
        if(!strcmp(cur->name,"VarList")){
            FieldList *l = Varlist(cur);
            fun->u.func.args = l;
            while(l!=NULL){
                fun->u.func.num++;
                l=l->next;
            }
        }
        e = malloc(sizeof(Element));
        e->name = s->firstchild->s_val;
        e->type = fun;
        Insert(e);
        FieldList* ret = malloc(sizeof(FieldList));
        ret->name = e->name;
        ret->type = fun;
        return ret;
    }
}
FieldList* Varlist(Tnode* s){
    assert(strcmp(s->name,"VarList"));
    Tnode* cur = s->firstchild;
    FieldList *l = malloc(sizeof(FieldList));
    l = Paramdec(cur);
    cur = cur->nextbro;
    if(cur!=NULL){
        cur = cur->nextbro;
        l->next = Varlist(cur);
    }
    return l;
}
FieldList* Paramdec(Tnode* s){
    assert(strcmp(s->name,"ParamDec"));
    Tnode* cur = s->firstchild;
    Type *def = Specifier(cur);
    cur = cur->nextbro;

    return Vardec(cur,def);
}
void Extdeclist(Tnode* s,Type* t){
    assert(strcmp(s->name,"ExtDecList")==0);
    Tnode *cur=s->firstchild;
    if(!strcmp(cur->name,"VarDec")){ Vardec(cur,t);}
    cur = cur->nextbro;
    if(cur!=NULL){
        // VarDec COMMA ExtDecList
        assert(strcmp(cur->name,"COMMA"));
        cur=cur->nextbro;
        if(cur!=NULL) Extdeclist(cur,t);
    }
}
FieldList* Vardec(Tnode* s,Type* t){
    assert(strcmp(s->name,"VarDec")==0);
    Tnode *cur = s->firstchild;
    if(!strcmp(cur->name,"ID")){
        Element* e=Search(cur->s_val);
        if(e!=NULL){
            switch (t->kind){
            case BASIC:
            case STRUCTVAR:
            case ARRAY:
                Error(3,cur->line);//变量出现重复定义，或变量与前面定义过的结构体名字重复。
                break;
            case STRUCTURE:   //???????????????
                Error(16,cur->line);//结构体的名字与前面定义过的结构体或变量的名字重复。
                break;
            default:
                break;
            }
            
        }else{
            e = malloc(sizeof(Element));
            e->name = cur->s_val;
            e->type = t;
            Insert(e);
        }
        FieldList* ret = malloc(sizeof(FieldList));
        ret->name = cur->s_val;
        ret->type = t;
        return ret;
    }else{
        int size = childth_node(s,3)->i_val;
        Type* new_t = malloc(sizeof(new_t));
        new_t->kind = ARRAY;
        new_t->u.array.size=size;
        new_t->u.array.elem=t;
        return Vardec(cur,new_t);
    }
}
Type* Specifier(Tnode* s){
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
    assert(strcmp(s->name,"StructSpecifier")==0);
    Tnode* cur = s->firstchild;
    assert(strcmp(s->name,"STRUCT")==0);
    cur=cur->nextbro;
    if(!strcmp(cur->name,"Tag")){
        // STRUCT Tag
        char *id = Tag(cur);
        Element* e = Search(id);
        if(e==NULL){
            Error(17,s->line);   //直接使用未定义过的结构体来定义变量。
            return NULL;
        }else{
            Type* ret = e->type;
            assert(ret->kind==STRUCTURE);
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
                t->u.structure = Deflist(node,t);
                Insert(e);
                return t;
            }
        }else{
            Type* t = malloc(sizeof(Type));
            t->kind = STRUCTURE;
            Tnode* node = childth_node(s,3);
            t->u.structure = Deflist(node,t);
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

}
FieldList* Deflist(Tnode* s,Type* t){

}