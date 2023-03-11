
%{

    #include <stdio.h>
    #include <string.h>
    #include "syntax.tab.h"
    #include <assert.h>
    int yycolumn = 1;
    #define YY_USER_ACTION \
      yylloc.first_line=yylloc.last_line=yylineno; \
      yylloc.first_column=yycolumn; \
      yylloc.last_column=yycolumn+yyleng-1; \
      yycolumn+=yyleng;
    int errorflag=0;
    #ifdef LOCAL_MACHINE
     #define debug(...) printf(__VA_ARGS__)
    #else
     #define debug(...) assert(1)
    #endif
%}
%option yylineno
digit   [0-9]
letter  [_a-zA-Z]



%%
"//"                         {char c =input();while(c!='\n')c=input();}         //单行注释

"/*"([^*]|\*+[^*/])*\*+"/"   {}                                                 //多行注释
\n                           {yycolumn = 1;}
[\r\t" "]+                   {}                                                 //空格等

(0|[1-9]{digit}*)            {debug("INT       : %s\n",yytext);yylval=create_node("INT",INT,yylineno);yylval->i_val = atoi(yytext);return INT;}                                      //INT是无符号，不以0开头就行

0[0-7]+                      {debug("8INT      : %s\n",yytext);return INT;}                                                 //8

0(x|X)([0-9A-Fa-f])*         {debug("16INT     : %s\n",yytext);return INT;}               //16

{digit}+\.{digit}+           {debug("FLOAT     : %s\n",yytext);yylval=create_node("FLOAT",FLOAT,yylineno);yylval->f_val = atof(yytext);return FLOAT;}

({digit}+\.{digit}+|\.{digit}+|{digit}+\.)(e|E)[-+]?{digit}*        {debug("FLOATE    : %s\n",yytext);return FLOAT;}

";"                          {debug("SEMI      : %s\n",yytext);yylval=create_node("SEMI",SEMI,yylineno);return SEMI;} 
","                          {debug("COMMA     : %s\n",yytext);yylval=create_node("COMMA",COMMA,yylineno);return COMMA;}
>=|<=|>|<|==|!=              {debug("RELOP     : %s\n",yytext);yylval=create_node("RELOP",RELOP,yylineno);return RELOP;}
"="                          {debug("ASSIGNOP  : %s\n",yytext);yylval=create_node("ASSIGNOP",ASSIGNOP,yylineno);return ASSIGNOP;} 
"+"                          {debug("PLUS      : %s\n",yytext);yylval=create_node("PLUS",PLUS,yylineno);return PLUS;}
"-"                          {debug("MINUS     : %s\n",yytext);yylval=create_node("MINUS",MINUS,yylineno);return MINUS;}
"*"                          {debug("STAR      : %s\n",yytext);yylval=create_node("STAR",STAR,yylineno);return STAR;}
"/"                          {debug("DIV       : %s\n",yytext);yylval=create_node("DIV",DIV,yylineno);return DIV;}
"&&"                         {debug("AND       : %s\n",yytext);yylval=create_node("AND",AND,yylineno);return AND;}
"||"                         {debug("OR        : %s\n",yytext);yylval=create_node("OR",OR,yylineno);return OR;}
"."                          {debug("DOT       : %s\n",yytext);yylval=create_node("DOT",DOT,yylineno);return DOT;}
"!"                          {debug("NOT       : %s\n",yytext);yylval=create_node("NOT",NOT,yylineno);return NOT;}
("int"|"float")              {debug("TYPE      : %s\n",yytext);yylval=create_node("TYPE",TYPE,yylineno);yylval->s_val=malloc(sizeof(yytext));strcpy(yylval->s_val,yytext);return TYPE;}
"("                          {debug("LP        : %s\n",yytext);yylval=create_node("LP",LP,yylineno);return LP;}
")"                          {debug("RP        : %s\n",yytext);yylval=create_node("RP",RP,yylineno);return RP;}
"["                          {debug("LB        : %s\n",yytext);yylval=create_node("LB",LB,yylineno);return LB;}
"]"                          {debug("RB        : %s\n",yytext);yylval=create_node("RB",RB,yylineno);return RB;}
"{"                          {debug("LC        : %s\n",yytext);yylval=create_node("LC",LC,yylineno);return LC;}
"}"                          {debug("RC        : %s\n",yytext);yylval=create_node("RC",RC,yylineno);return RC;}
"struct"                     {debug("STRUCT    : %s\n",yytext);yylval=create_node("STRUCT",STRUCT,yylineno);return STRUCT;}
"return"                     {debug("RETURN    : %s\n",yytext);yylval=create_node("RETURN",RETURN,yylineno);return RETURN;}
"if"                         {debug("IF        : %s\n",yytext);yylval=create_node("IF",IF,yylineno);return IF;}
"else"                       {debug("ELSE      : %s\n",yytext);yylval=create_node("ELSE",ELSE,yylineno);return ELSE;}
"while"                      {debug("WHILE     : %s\n",yytext);yylval=create_node("WHILE",WHILE,yylineno);return WHILE;}
{letter}({digit}|{letter})*  {debug("ID        : %s\n",yytext);yylval=create_node("ID",ID,yylineno);yylval->s_val=malloc(sizeof(yytext));strcpy(yylval->s_val,yytext);return ID;}               //标识符：52个大写字母或小写字母、10个数字和一个下划线字符组成的字符串，不能数字开头,为了去除保留字，最后再匹配
.                            {errorflag=1;printf("Error type A at Line %d: Mysterious characters \'%s\'\n",yylineno, yytext);}
%%
