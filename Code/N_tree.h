#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#ifndef TREENODE
#define TREENODE
struct treenode{
	char name[16];
	int line;
	int type;
	struct treenode *firstchild;
	//struct treenode *parent;
	struct treenode *nextbro;
	union{
		int i_val;
		float f_val;
		char *s_val;
	};
};
typedef struct treenode Tnode;

Tnode *create_node(char *name,int type,int line){
	Tnode* new_node = (Tnode *)malloc(sizeof(Tnode));
	strcpy(new_node->name,name);
	new_node->line = line;
	new_node->type = type;
	new_node ->firstchild = NULL;
	new_node ->nextbro = NULL;
}
void insert_node(Tnode *p,Tnode* new){
	assert(p!=NULL);
	if(p->firstchild==NULL){
		p->firstchild = new;
		return;
	}else{
		Tnode *cur = p->firstchild;
		while(cur->nextbro!=NULL) cur = cur->nextbro;
		cur->nextbro = new;
		return;
	}
}
void Ninsert(Tnode* p,int n,...){
	va_list valist;
	va_start(valist,n);
	for(int i=0;i<n;i++){
		Tnode* tmp = va_arg(valist,Tnode*);
		insert_node(p,tmp);
	}
	va_end(valist);
}
void dfs(Tnode* s,int dep){
	if(s->type==0){
		printf("%*s%s (%d)\n",dep*2,"",s->name,s->line);
	}else{
		printf("%*s%s",dep*2,"",s->name);
		switch(s->type){
			case 258:printf(": %d",s->i_val);break;
			case 259:printf(": %lf",s->f_val);break;
			case 260:printf(": %s",s->s_val);break;
			case 273:printf(": %s",s->s_val);break;
		}
		printf("\n");
	}
	Tnode* cur = s->firstchild;
	while(cur!=NULL){
		dfs(cur,dep+1);
		cur=cur->nextbro;
	}
	return;
}


#endif