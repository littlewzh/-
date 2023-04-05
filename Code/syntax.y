%locations
%{
    #include "N_tree.h"
    #include "lex.yy.c"//为了能够使用Flex中的各种函数，需要在Bison源代码中引用lex.yy.c
    struct treenode *root=NULL;
    extern int errorflag;
    int yyerror(const char *msg);

    //#define LOCAL_MACHINE 1  //用于调试，使得输出自定义的bison调试信息
    #ifdef LOCAL_MACHINE
     #define bdebug(...) printf(__VA_ARGS__)
    #else
     #define bdebug(...) assert(1)
    #endif
%}
%union{
    Tnode* node;
}
//终结符
%token <node> INT 
%token <node> FLOAT 
%token <node> ID
%token <node> SEMI COMMA ASSIGNOP 
%token <node> RELOP PLUS MINUS STAR DIV AND OR DOT NOT     
%token <node> TYPE    
%token <node> LP RP LB RB LC RC      
%token <node> STRUCT RETURN IF ELSE WHILE   
//非终结符
%type <node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args
%type <node> error
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
//语法单元Program是初始语法单元，表示整个程序
Program : ExtDefList                        {$$=create_node("Program",0,@$.first_line);Ninsert($$,1,$1);root=$$;}
    ;

//每个Program可以产生一个ExtDefList，这里的ExtDefList表示零个或多个ExtDef
ExtDefList :                                {$$=NULL;}
    | ExtDef ExtDefList                     {$$=create_node("ExtDefList",0,@$.first_line);Ninsert($$,2,$1,$2);}
    ;

//每个ExtDef表示一个全局变量、结构体或函数的定义
ExtDef : Specifier ExtDecList SEMI          {$$=create_node("ExtDef",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
//Specifier SEMI专门为结构体的定义而准备，也会允许出现“int;”
    | Specifier SEMI                        {$$=create_node("ExtDef",0,@$.first_line);Ninsert($$,2,$1,$2);}
//函数的定义：FunDec是函数头，一定要有函数体CompSt
    | Specifier FunDec CompSt               {$$=create_node("ExtDef",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
//一些可能的错误：全局
    | Specifier error SEMI                  {yyerrok;}//下一条有了这个可以去掉吗 
    | error SEMI                            {yyerrok;}
    | Specifier error                       {yyerrok;}//连着两个全局变量没分号的错误                       ???????
    | error FunDec CompSt                   {bdebug("error FunDec CompSt \n");yyerrok;}//函数类型不对的错误
    ;

//ExtDecList表示零个或多个VarDec变量定义
ExtDecList : VarDec                         {$$=create_node("ExtDecList",0,@$.first_line);Ninsert($$,1,$1);}
    | VarDec COMMA ExtDecList               {$$=create_node("ExtDecList",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    ;

//Specifier是类型描述符，可以直接变成TYPE或者StructSpecifier结构体类型
Specifier : TYPE                            {$$=create_node("Specifier",0,@$.first_line);Ninsert($$,1,$1);}
    | StructSpecifier                       {$$=create_node("Specifier",0,@$.first_line);Ninsert($$,1,$1);}
    ;
//结构体类型，OptTag是结构体名可有可无（？），STRUCT Tag用来直接用之前定义的结构体
//最基本的结构体形式是例如struct Complex { int real, image; }，DefList可以空如果定义过后就可以直接用struct Complex a, b;也就是第二种形式


StructSpecifier : STRUCT OptTag LC DefList RC           {$$=create_node("StructSpecifier",0,@$.first_line);Ninsert($$,5,$1,$2,$3,$4,$5);}
    | STRUCT Tag                                        {$$=create_node("StructSpecifier",0,@$.first_line);Ninsert($$,2,$1,$2);}    
    | STRUCT OptTag LC error RC                         {yyerrok;}//结构体定义的内部错误
  //  | STRUCT error                                      {yyerrok;} //struct后面跟着的所有可能错误              ??????
    ;
OptTag :                                                {$$=NULL;}  
    | ID                                                {$$=create_node("OptTag",0,@$.first_line);Ninsert($$,1,$1);}
    ;
Tag : ID                                                {$$=create_node("Tag",0,@$.first_line);Ninsert($$,1,$1);}
    ;

//VarDec表示对一个变量的定义，变量或数组
VarDec : ID                                             {$$=create_node("VarDec",0,@$.first_line);Ninsert($$,1,$1);}
    | VarDec LB INT RB                                  {$$=create_node("VarDec",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}
    | VarDec LB error RB                                {yyerrok;}
    ;

//FunDec表示对一个函数头的定义：标识符+括号函数列表
FunDec : ID LP VarList RP                               {$$=create_node("FunDec",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}
    | ID LP RP                                          {$$=create_node("FunDec",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | ID LP error RP                                    {yyerrok;}    
    ;
//VarList 形参列表
VarList : ParamDec COMMA VarList                        {$$=create_node("VarList",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | ParamDec                                          {$$=create_node("VarList",0,@$.first_line);Ninsert($$,1,$1);}
    ;
//每个ParamDec都是对一个形参的定义
ParamDec : Specifier VarDec                             {$$=create_node("ParamDec",0,@$.first_line);Ninsert($$,2,$1,$2);}
    ;

// CompSt表示一个由一对花括号括起来的语句块：只能先定义再语句
CompSt : LC DefList StmtList RC                         {$$=create_node("CompSt",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}
    | error RC                                          {yyerrok;}//右括号前的错误
    ;

//StmtList就是零个或多个Stmt的组合
StmtList :                                              {$$=NULL;}
    | Stmt StmtList                                     {$$=create_node("StmtList",0,@$.first_line);Ninsert($$,2,$1,$2);}
    ;
//每个Stmt都表示一条语句:分号表达式、一个语句块CompSt、RETURN语句、If、While、
Stmt : Exp SEMI                                         {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,2,$1,$2);}
    | CompSt                                            {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,1,$1);}
    | RETURN Exp SEMI                                   {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | IF LP Exp RP Stmt        %prec LOWER_THAT_ELSE    {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,5,$1,$2,$3,$4,$5);}
    | IF LP Exp RP Stmt ELSE Stmt                       {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,7,$1,$2,$3,$4,$5,$6,$7);}
    | WHILE LP Exp RP Stmt                              {$$=create_node("Stmt",0,@$.first_line);Ninsert($$,5,$1,$2,$3,$4,$5);}
//error 
    | IF LP error RP Stmt        %prec LOWER_THAT_ELSE  {yyerrok;}
    | IF LP error RP ELSE Stmt                          {yyerrok;}
    | IF LP Exp RP error ELSE Stmt                      {yyerrok;}    
    | WHILE LP error RP Stmt                            {yyerrok;}
  //  | Exp error                                         {yyerrok;}
  //  | RETURN error                                      {yyerrok;}
    | error SEMI                                        {yyerrok;}
    | error LP Exp RP Stmt                              {yyerrok;}         // ??????
    ;

//Local Definitions：与局部变量的定义有关：形式例如int a=1,b,c;
DefList :                                   {$$=NULL;}     
    | Def DefList                           {$$=create_node("DefList",0,@$.first_line);Ninsert($$,2,$1,$2);}
    ;
//每个Def就是一条分号首尾的变量定义
Def : Specifier DecList SEMI                {$$=create_node("Def",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Specifier error SEMI                  {yyerrok;}
    //| Specifier error                       {yyerrok;}     // ?????????
    ;
//允许逗号分割
DecList : Dec                               {$$=create_node("DecList",0,@$.first_line);Ninsert($$,1,$1);}     
    | Dec COMMA DecList                     {$$=create_node("DecList",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Dec error DecList                     {yyerrok;}
    ;
//允许局部变量初始化
Dec : VarDec                                {$$=create_node("Dec",0,@$.first_line);Ninsert($$,1,$1);}     
    | VarDec ASSIGNOP Exp                   {$$=create_node("Dec",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    ;

//Expressions这一部分的产生式主要与表达式有关：
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
    | ID LP Args RP                         {$$=create_node("Exp",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}//函数调用
    | ID LP RP                              {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp LB Exp RB                         {$$=create_node("Exp",0,@$.first_line);Ninsert($$,4,$1,$2,$3,$4);}
    | Exp DOT ID                            {$$=create_node("Exp",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | ID                                    {$$=create_node("Exp",0,@$.first_line);Ninsert($$,1,$1);}
    | INT                                   {$$=create_node("Exp",0,@$.first_line);Ninsert($$,1,$1);}
    | FLOAT                                 {$$=create_node("Exp",0,@$.first_line);Ninsert($$,1,$1);}
    ;
//错误：???????????????
    | Exp ASSIGNOP error                    {yyerrok;}
    | Exp AND error                         {yyerrok;}
    | Exp OR error                          {yyerrok;}
    | Exp RELOP error                       {yyerrok;}
    | Exp MINUS error                       {yyerrok;}
    | Exp STAR error                        {yyerrok;}
    | Exp DIV error                         {yyerrok;}
    | LP error RP                           {yyerrok;}
    | ID LP error RP                        {yyerrok;}
    | Exp LB error RB                       {yyerrok;} 

//Args是参数列表        
Args : Exp COMMA Args                       {$$=create_node("Args",0,@$.first_line);Ninsert($$,3,$1,$2,$3);}
    | Exp                                   {$$=create_node("Args",0,@$.first_line);Ninsert($$,1,$1);}
    ;
%%
//
int lastlineno=-1;//用于记录上一次报错的行数，使得一行只报错一次即可
int onelineflag = 1;//1表示开启一行只打印一个错误，0为关闭
int yyerror(const char *msg){
       errorflag=1;
       if(!onelineflag||yylineno!=lastlineno){//如果相等说明之前报错过了，就不打印
         lastlineno=yylineno;
         fprintf(stderr,"Error type B at line %d: %s :unexpected token %s\n",yylineno,msg,yytext);
       }
}