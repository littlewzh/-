
%{
    #include "lex.yy.c"
    void yyerror(char *msg){
       fprintf(stderr,"Error type B at line %d: %s %s\n",yylineno,msg,yytext);
    }
%}
%union{
   int type_int;
   float type_float;
   double type_double;
   char* type_string;
}
%token <type_int> INT 
%token <type_float> FLOAT 
%token <type_string> ID
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
Program : ExtDefList
    ;
ExtDefList : 
    | ExtDef ExtDefList 
    ;
ExtDef : Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    ;
ExtDecList : VarDec
    | VarDec COMMA ExtDecList
    ;

Specifier : TYPE
    | StructSpecifier
    ;
StructSpecifier : STRUCT OptTag LC DefList RC
    | STRUCT Tag
    ;
OptTag : 
    | ID
    ;
Tag : ID
    ;


VarDec : ID
    | VarDec LB INT RB
    ;
FunDec : ID LP VarList RP
    | ID LP RP
    ;
VarList : ParamDec COMMA VarList
    | ParamDec error COMMA VarList   //error
    | ParamDec
    ;
ParamDec : Specifier VarDec
    ;


CompSt : LC DefList StmtList RC
    | LC DefList StmtList error RC   //error
    ;
StmtList : 
    | Stmt StmtList
    ;
Stmt : Exp SEMI
    | Exp error SEMI                    //error 
    | CompSt
    | RETURN Exp SEMI
    | RETURN Exp error SEMI               //error
    | IF LP Exp RP Stmt        %prec LOWER_THAT_ELSE
    | IF LP Exp RP Stmt ELSE Stmt
    | WHILE LP Exp RP Stmt
    ;


DefList :
    | Def DefList
    ;
Def : Specifier DecList SEMI
    | Specifier DecList error SEMI;  //error
    ;
DecList : Dec
    | Dec COMMA DecList                // ?????error
    ;
Dec : VarDec
    | VarDec ASSIGNOP Exp
    ;


Exp : Exp ASSIGNOP Exp
    | Exp AND Exp
    | Exp OR Exp
    | Exp RELOP Exp
    | Exp PLUS Exp
    | Exp MINUS Exp
    | Exp STAR Exp
    | Exp DIV Exp
    | LP Exp RP
    | LP Exp error RP        //error
    | MINUS Exp
    | NOT Exp
    | ID LP Args RP  
    | ID LP Args error RP   //error
    | ID LP RP
    | Exp LB Exp RB
    | Exp LB Exp error RB   //error
    | Exp DOT ID
    | ID
    | INT
    | FLOAT
    ;
Args : Exp COMMA Args
    | Exp
    ;
%%
