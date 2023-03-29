#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
typedef struct treenode Tnode;
typedef struct FieldList_ FieldList;
struct treenode{
	char name[16];
	int line;
	int type;
	struct treenode *firstchild;
	//struct treenode *parent;
	struct treenode *nextbro;
	FieldList *Syn;
	FieldList *Inh;
	union{
		int i_val;
		float f_val;
		char *s_val;
	};
};
Tnode *create_node(char *name,int type,int line);
void insert_node(Tnode *p,Tnode* newn);
void Ninsert(Tnode* p,int n,...);
void dfs(Tnode* s,int dep);
