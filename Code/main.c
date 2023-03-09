#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern void yyrestart(FILE*);
extern int yylex();
extern int yyparse();
int main(int argc, char** argv){
    if (argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f){
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    return 0;
}