#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern void yyrestart(FILE*);
extern int yylex();//调用yylex()进行词法分析
extern int yyparse();
extern struct treenode* root;
extern void dfs(struct treenode* ,int);
extern int errorflag;
extern int yydebug;//用于bison调试
int main(int argc, char** argv){
    if (argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f){
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);//yyrestart(f)函数是Flex提供的库函数，它可以让Flex将其输入文件的文件指针yyin设置为f
    //yydebug = 1;//用于bison调试
    yyparse();//对输入文件进行语法分析
    if(!errorflag){
        dfs(root,0);
    }
    return 0;
}