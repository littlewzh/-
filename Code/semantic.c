#include "semantic.h"


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

