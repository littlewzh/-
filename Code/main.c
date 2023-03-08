#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE* yyin;
extern int yylex();
int main(int argc, char **argv){
    if(argc>1){
        if(!(yyin = fopen(argv[1],"r"))){
            perror(argv[1]);
            return 1;
        }
    }
    //yyparse();
    yylex();
    return 0;
}