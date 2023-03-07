digit   [0-9]
letter  [_a-zA-Z]
%%
(\/\*)             {}
"struct"                     {printf("17    : %s\n",yytext);}
"return"                     {printf("18    : %s\n",yytext);}
"if"                         {printf("19    : %s\n",yytext);}
"else"                       {printf("20    : %s\n",yytext);}
"while"                      {printf("21    : %s\n",yytext);}
(int|float)                  {printf("10    : %s\n",yytext);}
{letter}({digit}|{letter})*  {printf("ID    : %s\n",yytext);}
{digit}+                     {printf("INT   : %s\n",yytext);} 
{digit}+\.{digit}+           {printf("FLOAT : %s\n",yytext);}
";"                          {printf("ID    : %s\n",yytext);} 
","                          {printf("ID    : %s\n",yytext);}
"="                          {printf("ID    : %s\n",yytext);} 
> | < | >= | <= | == | !=    {printf("1     : %s\n",yytext);}
"+"                          {printf("2     : %s\n",yytext);}
"-"                          {printf("3     : %s\n",yytext);}
"*"                          {printf("4     : %s\n",yytext);}
"/"                          {printf("5     : %s\n",yytext);}
"&&"                         {printf("6     : %s\n",yytext);}
"||"                         {printf("7     : %s\n",yytext);}
"."                          {printf("8     : %s\n",yytext);}
"!"                          {printf("9     : %s\n",yytext);}
"("                          {printf("11    : %s\n",yytext);}
")"                          {printf("12    : %s\n",yytext);}
"["                          {printf("13    : %s\n",yytext);}
"]"                          {printf("14    : %s\n",yytext);}
"{"                          {printf("15    : %s\n",yytext);}
"}"                          {printf("16    : %s\n",yytext);}
"//"                         {char c=input();
                              while(c!='\n') c=input(); }
[\n\r\t" "]+                 {}
%%