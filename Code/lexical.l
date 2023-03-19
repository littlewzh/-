
%{

    #include <stdio.h>
    #include <string.h>
    #include "syntax.tab.h"//使得flex可以返回bison定义的词法类型
    #include <assert.h>
    int yycolumn = 1;
    #define YY_USER_ACTION \
      yylloc.first_line=yylloc.last_line=yylineno; \
      yylloc.first_column=yycolumn; \
      yylloc.last_column=yycolumn+yyleng-1; \
      yycolumn+=yyleng;
    int errorflag=0;

	//#define LOCAL_MACHINE 1  //用于调试，使得输出flex调试信息
    #ifdef LOCAL_MACHINE
     #define fdebug(...) printf(__VA_ARGS__)
    #else
     #define fdebug(...) assert(1)
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

(0|[1-9]{digit}*)            {fdebug("INT       : %s\n",yytext);yylval.node=create_node("INT",INT,yylineno);yylval.node->i_val = atoi(yytext);return INT;}                                      //INT是无符号，不以0开头就行

0[0-7]+                      {fdebug("8INT      : %s\n",yytext);yylval.node=create_node("INT",INT,yylineno);char * p=yytext;
  p++;int tmp=0;
  while(*p!='\0'){tmp=tmp*8+*p-48;p++;}
  yylval.node->i_val = tmp;return INT;
}                                                 //8

0(x|X)([0-9A-Fa-f])+         {fdebug("16INT     : %s\n",yytext);yylval.node=create_node("INT",INT,yylineno);char * p=yytext;
  p+=2; int tmp = 0;
	while (*p != '\0') {
		if (*p >= '0' && *p <= '9')tmp = tmp * 16 + *p - '0';
		if (*p >= 'A' && *p <= 'F')tmp = tmp * 16 + *p - 'A' + 10;
		if (*p >= 'a' && *p <= 'f')tmp = tmp * 16 + *p - 'a' + 10;
		p++;
	}yylval.node->i_val = tmp;return INT;
}               //16



({digit}+\.{digit}+|\.{digit}+|{digit}+\.)(e|E)?[-+]?{digit}+        {fdebug("FLOATE    : %s\n",yytext);yylval.node=create_node("FLOAT",FLOAT,yylineno);char * p=yytext;
    float flans = 0;
	int flstatus = 0,fltmp[3] = {0,0,0}, flwid1 = 0, flflag2 = 1;//三阶段分别解析数字：tmp0表示小数点前，1表示小数点后，2表示指数,wid1表示小数位数，flag2表示指数的正负
	while (*p != '\0') {
		switch (*p) {
		case  '.':flstatus = 1; break;
		case  'e':
		case  'E': flstatus = 2; break;
		case '+':if (flstatus == 2)flflag2 = 1; break;
		case '-':if (flstatus == 2)flflag2 = -1; break;
		default: 
			fltmp[flstatus] = fltmp[flstatus] * 10 + *p - '0';
			if (flstatus == 1)flwid1++;
		}
		p++;
	}
	flans = 1.0 * fltmp[0];//整数部分
	float ftmp = 1.0 * fltmp[1];
	while (flwid1--) ftmp/=10;
	flans += ftmp;//基数部分
	if (flflag2>0){
		while (fltmp[2]--)flans *= 10;
	}else {
		while (fltmp[2]--)flans /= 10;
	}
    yylval.node->f_val = flans;
	return FLOAT;
}



";"                          {fdebug("SEMI      : %s\n",yytext);yylval.node=create_node("SEMI",SEMI,yylineno);return SEMI;} 
","                          {fdebug("COMMA     : %s\n",yytext);yylval.node=create_node("COMMA",COMMA,yylineno);return COMMA;}
>=|<=|>|<|==|!=              {fdebug("RELOP     : %s\n",yytext);yylval.node=create_node("RELOP",RELOP,yylineno);return RELOP;}
"="                          {fdebug("ASSIGNOP  : %s\n",yytext);yylval.node=create_node("ASSIGNOP",ASSIGNOP,yylineno);return ASSIGNOP;} 
"+"                          {fdebug("PLUS      : %s\n",yytext);yylval.node=create_node("PLUS",PLUS,yylineno);return PLUS;}
"-"                          {fdebug("MINUS     : %s\n",yytext);yylval.node=create_node("MINUS",MINUS,yylineno);return MINUS;}
"*"                          {fdebug("STAR      : %s\n",yytext);yylval.node=create_node("STAR",STAR,yylineno);return STAR;}
"/"                          {fdebug("DIV       : %s\n",yytext);yylval.node=create_node("DIV",DIV,yylineno);return DIV;}
"&&"                         {fdebug("AND       : %s\n",yytext);yylval.node=create_node("AND",AND,yylineno);return AND;}
"||"                         {fdebug("OR        : %s\n",yytext);yylval.node=create_node("OR",OR,yylineno);return OR;}
"."                          {fdebug("DOT       : %s\n",yytext);yylval.node=create_node("DOT",DOT,yylineno);return DOT;}
"!"                          {fdebug("NOT       : %s\n",yytext);yylval.node=create_node("NOT",NOT,yylineno);return NOT;}
("int"|"float")              {fdebug("TYPE      : %s\n",yytext);yylval.node=create_node("TYPE",TYPE,yylineno);yylval.node->s_val=malloc(sizeof(yytext));strcpy(yylval.node->s_val,yytext);return TYPE;}
"("                          {fdebug("LP        : %s\n",yytext);yylval.node=create_node("LP",LP,yylineno);return LP;}
")"                          {fdebug("RP        : %s\n",yytext);yylval.node=create_node("RP",RP,yylineno);return RP;}
"["                          {fdebug("LB        : %s\n",yytext);yylval.node=create_node("LB",LB,yylineno);return LB;}
"]"                          {fdebug("RB        : %s\n",yytext);yylval.node=create_node("RB",RB,yylineno);return RB;}
"{"                          {fdebug("LC        : %s\n",yytext);yylval.node=create_node("LC",LC,yylineno);return LC;}
"}"                          {fdebug("RC        : %s\n",yytext);yylval.node=create_node("RC",RC,yylineno);return RC;}
"struct"                     {fdebug("STRUCT    : %s\n",yytext);yylval.node=create_node("STRUCT",STRUCT,yylineno);return STRUCT;}
"return"                     {fdebug("RETURN    : %s\n",yytext);yylval.node=create_node("RETURN",RETURN,yylineno);return RETURN;}
"if"                         {fdebug("IF        : %s\n",yytext);yylval.node=create_node("IF",IF,yylineno);return IF;}
"else"                       {fdebug("ELSE      : %s\n",yytext);yylval.node=create_node("ELSE",ELSE,yylineno);return ELSE;}
"while"                      {fdebug("WHILE     : %s\n",yytext);yylval.node=create_node("WHILE",WHILE,yylineno);return WHILE;}
{letter}({digit}|{letter})*  {fdebug("ID        : %s\n",yytext);yylval.node=create_node("ID",ID,yylineno);yylval.node->s_val=malloc(sizeof(yytext));strcpy(yylval.node->s_val,yytext);return ID;}               //标识符：52个大写字母或小写字母、10个数字和一个下划线字符组成的字符串，不能数字开头,为了去除保留字，最后再匹配
.                            {errorflag=1;printf("Error type A at Line %d: Mysterious characters \'%s\'\n",yylineno, yytext);}//如果不能符合上述正则说明有词法错误
%%
