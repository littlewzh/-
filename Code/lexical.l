
%{

    #include <stdio.h>
    #include <string.h>
    #include "syntax.tab.h"
    int yycolumn = 1;
    #define YY_USER_ACTION \
      yylloc.first_line=yylloc.last_line=yylineno; \
      yylloc.first_column=yycolumn; \
      yylloc.last_column=yycolumn+yyleng-1; \
      yycolumn+=yyleng;
    int errorflag=0;
%}
%option yylineno
digit   [0-9]
letter  [_a-zA-Z]



%%
"//"                         {char c =input();while(c!='\n')c=input();}         //单行注释

"/*"([^*]|\*+[^*/])*\*+"/"   {}                                                 //多行注释
\n                           {yycolumn = 1;}
[\r\t" "]+                   {}                                                 //空格等

(0|[1-9]{digit}*)            {printf("INT       : %s\n",yytext);yylval=create_node("INT",INT,yylineno);yylval->i_val = atoi(yytext);return INT;}                                      //INT是无符号，不以0开头就行

0[0-7]+                      {printf("8INT      : %s\n",yytext);return INT;}                                                 //8

0(x|X)([0-9A-Fa-f])*         {printf("16INT     : %s\n",yytext);return INT;}               //16

{digit}+\.{digit}+           {printf("FLOAT     : %s\n",yytext);yylval=create_node("FLOAT",FLOAT,yylineno);yylval->f_val = atof(yytext);return FLOAT;}

({digit}+\.{digit}+|\.{digit}+|{digit}+\.)(e|E)[-+]?{digit}*        {printf("FLOATE    : %s\n",yytext);return FLOAT;}

";"                          {printf("SEMI      : %s\n",yytext);yylval=create_node("SEMI",SEMI,yylineno);return SEMI;} 
","                          {printf("COMMA     : %s\n",yytext);yylval=create_node("COMMA",COMMA,yylineno);return COMMA;}
>=|<=|>|<|==|!=              {printf("RELOP     : %s\n",yytext);yylval=create_node("RELOP",RELOP,yylineno);return RELOP;}
"="                          {printf("ASSIGNOP  : %s\n",yytext);yylval=create_node("ASSIGNOP",ASSIGNOP,yylineno);return ASSIGNOP;} 
"+"                          {printf("PLUS      : %s\n",yytext);yylval=create_node("PLUS",PLUS,yylineno);return PLUS;}
"-"                          {printf("MINUS     : %s\n",yytext);yylval=create_node("MINUS",MINUS,yylineno);return MINUS;}
"*"                          {printf("STAR      : %s\n",yytext);yylval=create_node("STAR",STAR,yylineno);return STAR;}
"/"                          {printf("DIV       : %s\n",yytext);yylval=create_node("DIV",DIV,yylineno);return DIV;}
"&&"                         {printf("AND       : %s\n",yytext);yylval=create_node("AND",AND,yylineno);return AND;}
"||"                         {printf("OR        : %s\n",yytext);yylval=create_node("OR",OR,yylineno);return OR;}
"."                          {printf("DOT       : %s\n",yytext);yylval=create_node("DOT",DOT,yylineno);return DOT;}
"!"                          {printf("NOT       : %s\n",yytext);yylval=create_node("NOT",NOT,yylineno);return NOT;}
("int"|"float")              {printf("TYPE      : %s\n",yytext);yylval=create_node("TYPE",TYPE,yylineno);yylval->s_val=malloc(sizeof(yytext));strcpy(yylval->s_val,yytext);return TYPE;}
"("                          {printf("LP        : %s\n",yytext);yylval=create_node("LP",LP,yylineno);return LP;}
")"                          {printf("RP        : %s\n",yytext);yylval=create_node("RP",RP,yylineno);return RP;}
"["                          {printf("LB        : %s\n",yytext);yylval=create_node("LB",LB,yylineno);return LB;}
"]"                          {printf("RB        : %s\n",yytext);yylval=create_node("RB",RB,yylineno);return RB;}
"{"                          {printf("LC        : %s\n",yytext);yylval=create_node("LC",LC,yylineno);return LC;}
"}"                          {printf("RC        : %s\n",yytext);yylval=create_node("RC",RC,yylineno);return RC;}
"struct"                     {printf("STRUCT    : %s\n",yytext);yylval=create_node("STRUCT",STRUCT,yylineno);return STRUCT;}
"return"                     {printf("RETURN    : %s\n",yytext);yylval=create_node("RETURN",RETURN,yylineno);return RETURN;}
"if"                         {printf("IF        : %s\n",yytext);yylval=create_node("IF",IF,yylineno);return IF;}
"else"                       {printf("ELSE      : %s\n",yytext);yylval=create_node("ELSE",ELSE,yylineno);return ELSE;}
"while"                      {printf("WHILE     : %s\n",yytext);yylval=create_node("WHILE",WHILE,yylineno);return WHILE;}
{letter}({digit}|{letter})*  {printf("ID        : %s\n",yytext);yylval=create_node("ID",ID,yylineno);yylval->s_val=malloc(sizeof(yytext));strcpy(yylval->s_val,yytext);return ID;}               //标识符：52个大写字母或小写字母、10个数字和一个下划线字符组成的字符串，不能数字开头,为了去除保留字，最后再匹配
.                            {errorflag=1;printf("Error type A at Line %d: Mysterious characters \'%s\'\n",yylineno, yytext);}
%%
