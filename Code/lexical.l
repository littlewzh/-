%{

%}

digit   [0-9]
letter  [_a-zA-Z]
%%
"//"                         {printf("//: \n");char c =input();while(c!='\n')c=input();}//单行注释
"/*"([^*]|\*+[^*/])*\*+"/"   {printf("/*....*/:\n");}//多行注释
[\n\r\t" "]+                 {}//空格等
0|[1-9]{digit}*              {printf("INT   : %s\n",yytext);} //INT是无符号，不以0开头就行
0[1-7][0-7]*                 {printf("8INT   : %s\n",yytext);} //8
0(x|X)([0-9A-Fa-f])*         {printf("16INT   : %s\n",yytext);} //16
{digit}+\.{digit}+           {printf("FLOAT : %s\n",yytext);}
";"                          {printf("SEMI    : %s\n",yytext);} 
","                          {printf("COMMA    : %s\n",yytext);}
"="                          {printf("ASSIGNOP    : %s\n",yytext);} 
> | < | >= | <= | == | !=    {printf("1     : %s\n",yytext);}
"+"                          {printf("2     : %s\n",yytext);}
"-"                          {printf("3     : %s\n",yytext);}
"*"                          {printf("4     : %s\n",yytext);}
"/"                          {printf("5     : %s\n",yytext);}
"&&"                         {printf("6     : %s\n",yytext);}
"||"                         {printf("7     : %s\n",yytext);}
"."                          {printf("8     : %s\n",yytext);}
"!"                          {printf("9     : %s\n",yytext);}
("int"|"float")                  {printf("10 TYPE    : %s\n",yytext);}
"("                          {printf("11    : %s\n",yytext);}
")"                          {printf("12    : %s\n",yytext);}
"["                          {printf("13    : %s\n",yytext);}
"]"                          {printf("14    : %s\n",yytext);}
"{"                          {printf("15    : %s\n",yytext);}
"}"                          {printf("16    : %s\n",yytext);}
"struct"                     {printf("17    : %s\n",yytext);}
"return"                     {printf("18    : %s\n",yytext);}
"if"                         {printf("19    : %s\n",yytext);}
"else"                       {printf("20    : %s\n",yytext);}
"while"                      {printf("21    : %s\n",yytext);}
{letter}({digit}|{letter})*  {printf("ID    : %s\n",yytext);} //标识符：52个大写字母或小写字母、10个数字和一个下划线字符组成的字符串，不能数字开头,为了去除保留字，最后再匹配
%%