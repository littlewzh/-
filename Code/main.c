#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE* yyin;
extern int yylex();
int main(int argc, char **argv){
    if(argc>1){
        if(!(yyin = fopen(argv[1],"r"))){//yyin是输入文件指针
            perror(argv[1]);
            return 1;
        }
    }
    yylex();
    return 0;
}