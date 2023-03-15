%locations
%{
    #define YYSTYPE Tnode*
    #include "N_tree.h"
    #include "lex.yy.c"//为了能够使用Flex中的各种函数，需要在Bison源代码中引用lex.yy.c
    struct treenode *root=NULL;
    extern int errorflag;
    void yyerror(char *msg){
       errorflag=1;
       fprintf(stderr,"Error type B at line %d: %s %s\n",yylineno,msg,yytext);
    }
    
%}
%token  INT 
%token  FLOAT 
%token  ID
%token SEMI COMMA ASSIGNOP 
%token RELOP PLUS MINUS STAR DIV AND OR DOT NOT     
%token TYPE    
%token LP RP LB RB LC RC      
%token STRUCT RETURN IF ELSE WHILE   

%right ASSIGNOP
%left AND OR
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LP RP LB RB DOT

%nonassoc LOWER_THAT_ELSE
%nonassoc ELSE

%%
Program : ExtDefList                        {$$=create_node("Program",0,@$.first_line);Ninsert($$,1,$1);root=$$;}
    ;
ExtDefList :                                {$$=NULL;}
    | ExtDef ExtDefList                     {$$=create_node("ExtDefList",0,@$.first_line);Ninsert($$,2,$1,$2);}
    ;
ExtDef : Specifier ExtDecList SEMI          {$$=create_node("ExtDef",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Specifier SEMI                        {$$=create_node("ExtDef",0,@$.first_line);Ninsert($$,2,$1,$2);}
    | Specifier FunDec CompSt               {$$=create_node("ExtDef",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Specifier error SEMI
    | error SEMI
    ;
ExtDecList : VarDec                         {$$=create_node("ExtDecList",0,@$.first_line);Ninsert($$,1,$1);}
    | VarDec COMMA ExtDecList               {$$=create_node("ExtDecList",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    ;

Specifier : TYPE                            {$$=create_node("Specifier",0,@$.first_line);Ninsert($$,1,$1);}
    | StructSpecifier                       {$$=create_node("Specifier",0,@$.first_line);Ninsert($$,1,$1);}
    ;
StructSpecifier : STRUCT OptTag LC DefList RC       {$$=create_node("StructSpecifier",0,@$.first_line);Ninsert($$,5,$1,$2,$3,$4,$5);}
    | STRUCT Tag                                    {$$=create_node("StructSpecifier",0,@$.first_line);Ninsert($$,2,$1,$2);}
    ;
OptTag :                                    {$$=NULL;}  
    | ID                                    {$$=create_node("OptTag",0,@$.first_line);Ninsert($$,1,$1);}
    ;
Tag : ID                                    {$$=create_node("Tag",0,@$.first_line);Ninsert($$,1,$1);}
    ;


VarDec : ID                                 {$$=create_node("VarDec",0,@$.first_line);Ninsert($$,1,$1);}
    | VarDec LB INT RB                      {$$=create_node("VarDec",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}
    | error RB                              //error
    ;
FunDec : ID LP VarList RP                   {$$=create_node("FunDec",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}
    | ID LP RP                              {$$=create_node("FunDec",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | error RP                             //error
    ;
VarList : ParamDec COMMA VarList            {$$=create_node("VarList",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | ParamDec                              {$$=create_node("VarList",0,@$.first_line);Ninsert($$,1,$1);}
    ;
ParamDec : Specifier VarDec                 {$$=create_node("ParamDec",0,@$.first_line);Ninsert($$,2,$1,$2);}
    ;


CompSt : LC DefList StmtList RC             {$$=create_node("CompSt",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}
    | error RC                              //error
    ;
StmtList :                                  {$$=NULL;}
    | Stmt StmtList                         {$$=create_node("StmtList",0,@$.first_line);Ninsert($$,2,$1,$2);}
    ;
Stmt : Exp SEMI                             {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,2,$1,$2);}
    | CompSt                                {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,1,$1);}
    | RETURN Exp SEMI                       {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | IF LP Exp RP Stmt        %prec LOWER_THAT_ELSE    {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,5,$1,$2,$3,$4,$5);}
    | IF LP Exp RP Stmt ELSE Stmt                       {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,7,$1,$2,$3,$4,$5,$6,$7);}
    | WHILE LP Exp RP Stmt                              {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,5,$1,$2,$3,$4,$5);}
    | error SEMI                            {printf("error SEMI\n");}//error
    ;


DefList :                                   {$$=NULL;}     
    | Def DefList                           {$$=create_node("DefList",0,@$.first_line);Ninsert($$,2,$1,$2);}
    ;
Def : Specifier DecList SEMI                {$$=create_node("Def",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Specifier error SEMI                  {printf("Specifier error SEMI\n");}//error
    ;
DecList : Dec                               {$$=create_node("DecList",0,@$.first_line);Ninsert($$,1,$1);}     
    | Dec COMMA DecList                     {$$=create_node("DecList",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    ;
Dec : VarDec                                {$$=create_node("Dec",0,@$.first_line);Ninsert($$,1,$1);}     
    | VarDec ASSIGNOP Exp                   {$$=create_node("Dec",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    ;


Exp : Exp ASSIGNOP Exp                      {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp AND Exp                           {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp OR Exp                            {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp RELOP Exp                         {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp PLUS Exp                          {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp MINUS Exp                         {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp STAR Exp                          {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp DIV Exp                           {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | LP Exp RP                             {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | MINUS Exp                             {$$=create_node("Exp",0,@$.first_line);Ninsert($$,2,$1,$2);}
    | NOT Exp                               {$$=create_node("Exp",0,@$.first_line);Ninsert($$,2,$1,$2);}
    | ID LP Args RP                         {$$=create_node("Exp",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}
    | ID LP RP                              {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp LB Exp RB                         {$$=create_node("Exp",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}
    | Exp DOT ID                            {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | ID                                    {$$=create_node("Exp",0,@$.first_line);Ninsert($$,1,$1);}
    | INT                                   {$$=create_node("Exp",0,@$.first_line);Ninsert($$,1,$1);}
    | FLOAT                                 {$$=create_node("Exp",0,@$.first_line);Ninsert($$,1,$1);}
    ;
Args : Exp COMMA Args                       {$$=create_node("Args",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp                                   {$$=create_node("Args",0,@$.first_line);Ninsert($$,1,$1);}
    ;
%%
