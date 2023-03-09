
%{

    #include <stdio.h>
    #include <string.h>
    #include "syntax.tab.h"
    int yycolumn = 1;

%}
%option yylineno
digit   [0-9]
letter  [_a-zA-Z]
%%
"//"                         {char c =input();
                              while(c!='\n')c=input();}                         //单行注释
"/*"([^*]|\*+[^*/])*\*+"/"   {}                                                 //多行注释
\n                           {yycolumn = 1;}
[\r\t" "]+                   {}                                                 //空格等

(0|[1-9]{digit}*)            {printf("INT       : %s\n",yytext);yylval.type_int = atoi(yytext);
                              return INT;}                                      //INT是无符号，不以0开头就行

0[0-7]+                      {printf("8INT      : %s\n",yytext);
                              return INT;
                              }                                                 //8
0(x|X)([0-9A-Fa-f])*         {printf("16INT     : %s\n",yytext);
                              return INT;
                             }               //16

{digit}+\.{digit}+           {printf("FLOAT     : %s\n",yytext);
                              yylval.type_float = atof(yytext);
                              return FLOAT;}


({digit}+\.{digit}+|\.{digit}+|{digit}+\.)(e|E)[-+]?{digit}*        {printf("FLOATE    : %s\n",yytext);return FLOAT;}
";"                          {printf("SEMI      : %s\n",yytext);return SEMI;} 
","                          {printf("COMMA     : %s\n",yytext);return COMMA;}
>=|<=|>|<|==|!=              {printf("RELOP     : %s\n",yytext);return RELOP;}
"="                          {printf("ASSIGNOP  : %s\n",yytext);return ASSIGNOP;} 
"+"                          {printf("PLUS      : %s\n",yytext);return PLUS;}
"-"                          {printf("MINUS     : %s\n",yytext);return MINUS;}
"*"                          {printf("STAR      : %s\n",yytext);return STAR;}
"/"                          {printf("DIV       : %s\n",yytext);return DIV;}
"&&"                         {printf("AND       : %s\n",yytext);return AND;}
"||"                         {printf("OR        : %s\n",yytext);return OR;}
"."                          {printf("DOT       : %s\n",yytext);return DOT;}
"!"                          {printf("NOT       : %s\n",yytext);return NOT;}
("int"|"float")              {printf("TYPE      : %s\n",yytext);return TYPE;}
"("                          {printf("LP        : %s\n",yytext);return LP;}
")"                          {printf("RP        : %s\n",yytext);return RP;}
"["                          {printf("LB        : %s\n",yytext);return LB;}
"]"                          {printf("RB        : %s\n",yytext);return RB;}
"{"                          {printf("LC        : %s\n",yytext);return LC;}
"}"                          {printf("RC        : %s\n",yytext);return RC;}
"struct"                     {printf("STRUCT    : %s\n",yytext);return STRUCT;}
"return"                     {printf("RETURN    : %s\n",yytext);return RETURN;}
"if"                         {printf("IF        : %s\n",yytext);return IF;}
"else"                       {printf("ELSE      : %s\n",yytext);return ELSE;}
"while"                      {printf("WHILE     : %s\n",yytext);return WHILE;}
{letter}({digit}|{letter})*  {printf("ID        : %s\n",yytext);
                              yylval.type_string = yytext;
                              return ID;}               //标识符：52个大写字母或小写字母、10个数字和一个下划线字符组成的字符串，不能数字开头,为了去除保留字，最后再匹配
.                            {printf("Error type A at Line %d: Mysterious characters \'%s\'\n",yylineno, yytext);}
%%
