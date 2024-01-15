%code top{
    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    Type* currentType;
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    double ftype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token <ftype> FLOATING
%token CONST
%token TYPE_INT TYPE_FLOAT TYPE_VOID
%token IF ELSE WHILE BREAK CONTINUE RETURN
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE COMMA SEMICOLON
%token ADD SUB MUL DIV MOD AND OR NOT LESS LESSEQ GREAT GREATEQ EQ NEQ ASSIGN

<<<<<<< HEAD
%type <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt WhileStmt ReturnStmt DeclStmt FuncDef BreakStmt ContinueStmt ExpStmt Exps
%type <stmttype> VarDefList VarDef ConstDefList ConstDef
%type <stmttype> ArrIndices ArrayInitVal ArrayInitValList ConstArrayInitVal ConstArrayInitValList
%type <exprtype> Exp ConstExp AddExp Cond LOrExp PrimaryExp LVal RelExp LAndExp UnaryExp MulExp EqExp 
%type <stmttype> FuncParams FuncParam FuncRealParams
=======
%type <stmttype> Stmts Stmt AssignStmt ExpStmt BlockStmt IfStmt WhileStmt BreakStmt ContinueStmt ReturnStmt
%type <stmttype> DeclStmt ConstDefList ConstDef ConstInitVal VarDefList VarDef VarInitVal FuncDef FuncParams FuncParam FuncRParams
%type <stmttype> ArrConstIndices ArrValIndices ConstInitValList VarInitValList
%type <exprtype> Exp ConstExp AddExp MulExp UnaryExp PrimaryExp LVal Cond LOrExp LAndExp EqExp RelExp
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
%type <type> Type

%precedence THEN
%precedence ELSE
%%

// 程序
Program
    :   Stmts{
            ast.setRoot($1);
        }
    ;

// 语句序列
Stmts
    :   Stmts Stmt{
            SeqNode* node = dynamic_cast<SeqNode*>($1);
            node->addNext(dynamic_cast<StmtNode*>($2));
            $$ = dynamic_cast<StmtNode*>(node);
        }
    |   Stmt{
            SeqNode* node = new SeqNode();
            node->addNext(dynamic_cast<StmtNode*>($1));
            $$ = dynamic_cast<StmtNode*>(node);
        }
    ;

// 语句
Stmt
<<<<<<< HEAD
    : AssignStmt {$$=$1;}
    | BlockStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | WhileStmt{$$ = $1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | FuncDef {$$=$1;}
    | BreakStmt{$$=$1;}
    | ContinueStmt{$$=$1;}
    | SEMICOLON{$$ = new EmptyStmt() ;}
    | ExpStmt{$$ = $1;}
=======
    :   AssignStmt {$$=$1;}
    |   ExpStmt SEMICOLON{$$=$1;}
    |   BlockStmt {$$=$1;}
    |   IfStmt {$$=$1;}
    |   WhileStmt {$$=$1;}
    |   BreakStmt {$$=$1;}
    |   ContinueStmt {$$=$1;}
    |   ReturnStmt {$$=$1;}
    |   DeclStmt {$$=$1;}
    |   FuncDef {$$=$1;}
    |   SEMICOLON {$$ = new EmptyStmt();}
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
    ;

// 左值
LVal
    :   ID {
            SymbolEntry *se;
            se = identifiers->lookup($1);
            if(se == nullptr)
            {
                fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
                delete [](char*)$1;
                assert(se != nullptr);
            }
            $$ = new Id(se);
            delete []$1;
        }
    // 数组左值
    |   ID ArrValIndices {
            SymbolEntry *se;
            se = identifiers->lookup($1);
            if(se == nullptr)
            {
                fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
                delete [](char*)$1;
                assert(se != nullptr);
            }
            Id* newId = new Id(se);
            newId->addIndices(dynamic_cast<ExprStmtNode*>($2));
            $$ =  newId;
            delete []$1;
        }
<<<<<<< HEAD
        Id* newId = new Id(se);
        newId->addIndices((ExprStmtNode*)$2);
        $$ =  newId;
        delete []$1;
    }
=======
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
    ;

// 赋值语句
AssignStmt
    :   LVal ASSIGN Exp SEMICOLON {
            $$ = new AssignStmt($1, $3);
        }
    ;

// 表达式语句
ExpStmt
    :   ExpStmt COMMA Exp {
            ExprStmtNode* node = dynamic_cast<ExprStmtNode*>($1);
            node->addNext($3);
            $$ = node;
        }
    |   Exp {
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext($1);
            $$ = node;
        }
    ;

// 语句快
BlockStmt
    :   LBRACE {
            identifiers = new SymbolTable(identifiers);
        } 
        Stmts RBRACE {
            $$ = new CompoundStmt($3);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
    |   LBRACE RBRACE {
            $$ = new CompoundStmt(nullptr);
        }
    ;

// if语句
IfStmt
    :   IF LPAREN Cond RPAREN Stmt %prec THEN {
            $$ = new IfStmt($3, $5);
        }
    |   IF LPAREN Cond RPAREN Stmt ELSE Stmt {
            $$ = new IfElseStmt($3, $5, $7);
        }
    ;

//while 语句
WhileStmt
    :   WHILE LPAREN Cond RPAREN Stmt {
            $$ = new WhileStmt($3,$5);
        }
    ;

//break 语句
BreakStmt
    :   BREAK SEMICOLON {
            $$ = new BreakStmt();
        }
    ;

//continue 语句
ContinueStmt
    :   CONTINUE SEMICOLON{
            $$ = new ContinueStmt();
        }
    ;


// return 语句
ReturnStmt
    :   RETURN Exp SEMICOLON {
            $$ = new ReturnStmt($2);
        }
    |   RETURN SEMICOLON {
            $$ = new ReturnStmt(nullptr);
        }
    ;

// 变量表达式
Exp
    :   AddExp {
            $$ = $1;
        }
    ;

<<<<<<< HEAD
Exps
    :  ExpStmt PARSE Exp {
            ExprStmtNode* node = (ExprStmtNode*)$1;
=======
// 常量表达式
ConstExp
    :   AddExp {
            $$ = $1;
        }
    ;

// 加法级表达式
AddExp
    :   MulExp {
            $$ = $1;
        }
    |   AddExp ADD MulExp {
            SymbolEntry *se;
            if($1->getType()->isAnyInt() && $3->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
        }
    |   AddExp SUB MulExp {
            SymbolEntry *se;
            if($1->getType()->isAnyInt() && $3->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
        }
    ;

// 乘法级表达式
MulExp
    :   UnaryExp {
            $$ = $1;
        }
    |   MulExp MUL UnaryExp {
            SymbolEntry *se;
            if($1->getType()->isAnyInt() && $3->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
        }
    |   MulExp DIV UnaryExp {
            SymbolEntry *se;
            if($1->getType()->isAnyInt() && $3->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
        }
    |   MulExp MOD UnaryExp {
            SymbolEntry *se;
            if($1->getType()->isAnyInt() && $3->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
        }
    ;

// 非数组表达式
UnaryExp
    :   PrimaryExp {
            $$ = $1;
        }
    |   ID LPAREN FuncRParams RPAREN {
            SymbolEntry *se;
            se = identifiers->lookup($1);
            if(se == nullptr)
            {
                fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
                delete [](char*)$1;
                assert(se != nullptr);
            }
            SymbolEntry *tmp = new TemporarySymbolEntry(dynamic_cast<FunctionType*>(se->getType())->getRetType(), SymbolTable::getLabel());
            $$ = new FuncCallNode(tmp, new Id(se), dynamic_cast<FuncCallParamsNode*>($3));
        }
    |   ADD UnaryExp {
            $$ = $2;
        }
    |   SUB UnaryExp {
            SymbolEntry *tmp = new TemporarySymbolEntry($2->getType(), SymbolTable::getLabel());
            $$ = new OneOpExpr(tmp, OneOpExpr::SUB, $2);
        }
    |   NOT UnaryExp {
            SymbolEntry *tmp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new OneOpExpr(tmp, OneOpExpr::NOT, $2);
        }
    ;

// 基础表达式
PrimaryExp
    :   LVal {
            $$ = $1;
        }
    |   LPAREN Exp RPAREN {
            $$ = $2;
        }
    |   INTEGER {
            SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constIntType, $1);
            $$ = new Constant(se);
        }
    |   FLOATING {
            SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constFloatType, $1);
            $$ = new Constant(se);
        }
    ;

// 函数参数列表
FuncRParams
    :   FuncRParams COMMA Exp {
            FuncCallParamsNode* node = dynamic_cast<FuncCallParamsNode*>($1);
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            node->addNext($3);
            $$ = node;
        }
    |   Exp {
            FuncCallParamsNode* node = new FuncCallParamsNode();
            node->addNext($1);
            $$ = node;
        }
    |   %empty {
            $$ = nullptr;
        }
    ;

// 条件表达式
Cond
    :   LOrExp {$$ = $1;}
    ;

// 或运算表达式
LOrExp
    :   LAndExp {
            $$ = $1;
        }
    |   LOrExp OR LAndExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
        }
    ;

// 与运算表达式
LAndExp
    :   EqExp {
            $$ = $1;
        }
    |   LAndExp AND EqExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
        }
    ;

// 相等判断表达式
EqExp
    :   RelExp {
            $$ = $1;
        }
    |   EqExp EQ RelExp {
            SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::EQ, $1, $3);
        }
    |   EqExp NEQ RelExp {
            SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::NEQ, $1, $3);
        }
    ;

// 关系表达式
RelExp
    :   AddExp {
            $$ = $1;
        }
    |   RelExp LESS AddExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
        }
    |   RelExp LESSEQ AddExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::LESSEQ, $1, $3);
        }
    |   RelExp GREAT AddExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::GREAT, $1, $3);
        }
    |   RelExp GREATEQ AddExp {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::GREATEQ, $1, $3);
        }
    ;

// 类型
Type
    :   TYPE_INT {
            $$ = TypeSystem::intType;
            currentType = TypeSystem::intType;
        }
    |   TYPE_FLOAT {
            $$ = TypeSystem::floatType;
            currentType = TypeSystem::floatType;
        }
    |   TYPE_VOID {
            $$ = TypeSystem::voidType;
        }
    ;

// 数组的常量下标表示
ArrConstIndices 
    :   ArrConstIndices LBRACKET ConstExp RBRACKET {
            ExprStmtNode* node = dynamic_cast<ExprStmtNode*>($1);
            node->addNext($3);
            $$ = node;          
        }
    |   LBRACKET ConstExp RBRACKET {
            ExprStmtNode* node = new ExprStmtNode();
<<<<<<< HEAD
            node->addNext($1);
=======
            node->addNext($2);
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            $$ = node;
        }
    ;

<<<<<<< HEAD
Exp
    :
    AddExp {$$ = $1;}
    ;

 ConstExp
    :   
    AddExp {$$ = $1;}
    ; 

Cond
    :
    LOrExp {$$ = $1;}
    ;

FuncRealParams
    :
    FuncRealParams PARSE Exp{
        FuncCallParamsNode* node = (FuncCallParamsNode*) $1;
        node->addNext($3);
        $$ = node;
    }
    |
    Exp{
        FuncCallParamsNode* node = new FuncCallParamsNode();
        node->addNext($1);
        $$ = node;
    }
    |
    %empty{
        $$ = nullptr;
    }

//基本表达式
PrimaryExp
    :
    LVal {
        $$ = $1;
    }
    | INTEGER {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constIntType, $1);
        $$ = new Constant(se);
    }
    | FLOATNUM {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constFloatType,$1);
        $$ = new Constant(se);
    }
    | LPAREN Exp RPAREN{
        $$ = $2;
    }
    ;

UnaryExp
    :
    PrimaryExp{$$=$1;}
    |
    ADD UnaryExp{
        $$ = $2;
    }
    |
    SUB UnaryExp{
        SymbolEntry *se = new TemporarySymbolEntry($2->getType(), SymbolTable::getLabel());
        $$ = new OneOpExpr(se, OneOpExpr::SUB, $2);
    }
    |
    NOT UnaryExp{
         SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
         $$ = new OneOpExpr(se, OneOpExpr::NOT, $2);
    }
    |
    ID LPAREN FuncRealParams RPAREN{ // 函数调用
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        SymbolEntry *tmp = new TemporarySymbolEntry(dynamic_cast<FunctionType*>(se->getType())->getRetType(), SymbolTable::getLabel());
        $$ = new FuncCallNode(tmp, new Id(se), dynamic_cast<FuncCallParamsNode*>($3));
    }

    ;


// mult div
MulExp
    :
    UnaryExp{$$=$1;}
    |
    MulExp MUL UnaryExp {
        SymbolEntry *se;
        if($1->getType()->isInt() && $3->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
    }
    |
    MulExp DIV UnaryExp {
        SymbolEntry *se;
        if($1->getType()->isInt() && $3->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
    }
    |
    MulExp MOD UnaryExp {
        SymbolEntry *se;
        if($1->getType()->isInt() && $3->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
    }
    ;
    

AddExp
    :
    MulExp{$$=$1;}
    |
    AddExp ADD MulExp
    {
        SymbolEntry *se;
        if($1->getType()->isInt() && $3->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
    }
    |
    AddExp SUB MulExp
    {
        SymbolEntry *se;
        if($1->getType()->isInt() && $3->getType()->isInt()){
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        }
        else{
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        }
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
    }
    ;

RelExp
    :
    AddExp {$$ = $1;}
    |
    RelExp LESS AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    |
    RelExp GREATER AddExp
    {
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREAT, $1, $3);
    }
    |
    RelExp LE AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESSEQ, $1, $3);
    }
    |
    RelExp GE AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATEQ, $1, $3);
    }
    ;

EqExp
    :
    RelExp{$$=$1;}
    |
    EqExp EQ RelExp{
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQ, $1, $3);
    }
    |
    EqExp NEQ RelExp{
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NEQ, $1, $3);
    }
    ;

LAndExp
    :
    EqExp {$$ = $1;}
    |
    LAndExp AND EqExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
    }
    ;
LOrExp 
    :
    LAndExp {$$ = $1;}
    |
    LOrExp OR LAndExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
    }
    ;
Type
    : INT {
        $$ = TypeSystem::intType;
        currentType = TypeSystem::intType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
        currentType = TypeSystem::voidType;
    }
    | FLOAT {
        $$ = TypeSystem::floatType;
        currentType = TypeSystem::floatType;
    }
    ;
DeclStmt
    : CONST Type ConstDefList SEMICOLON{ // const声明
        $$ = $3;
    }

    | Type VarDefList SEMICOLON { 
        $$ = $2;
    }

    ;
// 数组下标
ArrIndices 
    :   ArrIndices LBRACKET ConstExp RBRACKET {
            ExprStmtNode* node = dynamic_cast<ExprStmtNode*>($1);
            node->addNext($3);
            $$ = node;     
      
        }
    |   LBRACKET ConstExp RBRACKET {
=======
// 数组的变量下标表示
ArrValIndices 
    :   ArrValIndices LBRACKET Exp RBRACKET {
            ExprStmtNode* node = dynamic_cast<ExprStmtNode*>($1);
            node->addNext($3);
            $$ = node;          
        }
    |   LBRACKET Exp RBRACKET {
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext($2);
            $$ = node;

        }
    ;

// 声明语句
DeclStmt
    :   CONST Type ConstDefList SEMICOLON {
            $$ = $3;
        }
    |   Type VarDefList SEMICOLON {
            $$ = $2;
        }
    ;

// 常量定义列表
ConstDefList
    :   ConstDefList COMMA ConstDef {
            DeclStmt* node = dynamic_cast<DeclStmt*>($1);
            node->addNext(dynamic_cast<DefNode*>($3));
            $$ = node;
        }
    |   ConstDef {
            DeclStmt* node = new DeclStmt(true);
<<<<<<< HEAD
            node->addNext((DefNode*)$1);
            $$ = node; 
    }

ConstDef 
    : ID ASSIGN ConstExp {
        // const 必须赋初值
            // 首先判断是否重定义
            if(identifiers->isRedefine($1)) {
                fprintf(stderr, "identifier %s redefine\n", $1);
                exit(EXIT_FAILURE);
            }
            // 此处文法有改动
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::constIntType;
            }
            else{
                type = TypeSystem::constFloatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
            // 类型向上转换
            $$ = new DefNode(new Id(se), dynamic_cast<Node*>($3), true, false);
        

        }
    // todo 数组变量的定义
        |   ID ArrIndices ASSIGN ConstArrayInitVal{
=======
            node->addNext(dynamic_cast<DefNode*>($1));
            $$ = node;
        }
    ;

// 常量定义
ConstDef
    :   ID ASSIGN ConstExp {
            // 首先判断是否重定义
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            if(identifiers->isRedefine($1)) {
                fprintf(stderr, "identifier %s redefine\n", $1);
                exit(EXIT_FAILURE);
            }
<<<<<<< HEAD
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = new ConstIntArrayType();
            }
            else{
                type = new ConstFloatArrayType();
=======
            // 此处文法有改动
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::constIntType;
            }
            else{
                type = TypeSystem::constFloatType;
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
<<<<<<< HEAD
=======
            // 类型向上转换
            $$ = new DefNode(new Id(se), dynamic_cast<Node*>($3), true, false);
        }
    // 数组常量的定义
    |   ID ArrConstIndices ASSIGN ConstInitVal{
            // 首先判断是否重定义
            if(identifiers->isRedefine($1)) {
                fprintf(stderr, "identifier %s redefine\n", $1);
                exit(EXIT_FAILURE);
            }
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = new ConstIntArrayType();
            }
            else{
                type = new ConstFloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            Id* id = new Id(se);
            id->addIndices(dynamic_cast<ExprStmtNode*>($2));
            // 类型向上转换
            $$ = new DefNode(id, dynamic_cast<Node*>($4), true, true);
<<<<<<< HEAD
        

=======
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
        }
    ;

<<<<<<< HEAD
ConstArrayInitVal 
    :   ConstExp {
            InitValNode* node = new InitValNode(true);
            node->setLeafNode(dynamic_cast<ExprNode*>($1));
            $$ = node;
        }
    |   LBRACE ConstArrayInitValList RBRACE{
            $$ = $2;
        }
    |   LBRACE RBRACE{
            $$ = new InitValNode(true);
    }
    ; 

 ConstArrayInitValList
    :   ConstArrayInitValList PARSE ConstArrayInitVal{
            InitValNode* node = (InitValNode*)$1;
            node->addNext(dynamic_cast<InitValNode*>($3));
            $$ = node;
        }
    |   ConstArrayInitVal{
            InitValNode* newNode = new InitValNode(true);
            newNode->addNext((InitValNode*)$1);
            $$ = newNode;
        }
    ;   

ArrayInitVal 
    :   Exp {
            InitValNode* node = new InitValNode(false);
            node->setLeafNode((ExprNode*)$1);
            $$ = node;
        }
    |   LBRACE ArrayInitValList RBRACE{
            $$ = $2;
        }
    |   LBRACE RBRACE{
            $$ = new InitValNode(false);
=======
// 常量初始化值
ConstInitVal
    :   ConstExp {
            // 不能直接赋值，否则根本无法判断是list还是expr
            InitValNode* newNode = new InitValNode(true);
            newNode->setLeafNode(dynamic_cast<ExprNode*>($1));
            $$ = newNode;
        }
    // 常量数组的初始化值 
    |   LBRACE ConstInitValList RBRACE{
            $$ = $2;
        }
    |   LBRACE RBRACE{
            $$ = new InitValNode(true);
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
    }
    ;

<<<<<<< HEAD
ArrayInitValList
    :   ArrayInitValList PARSE ArrayInitVal{
            InitValNode* node = (InitValNode*)$1;
            node->addNext((InitValNode*)$3);
            $$ = node;
        }
    |   ArrayInitVal{
            InitValNode* newNode = new InitValNode(false);
            newNode->addNext((InitValNode*)$1);
=======
// 数组常量初始化列表
ConstInitValList
    :   ConstInitValList COMMA ConstInitVal{
            InitValNode* node = dynamic_cast<InitValNode*>($1);
            node->addNext(dynamic_cast<InitValNode*>($3));
            $$ = node;
        }
    |   ConstInitVal{
            InitValNode* newNode = new InitValNode(true);
            newNode->addNext(dynamic_cast<InitValNode*>($1));
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            $$ = newNode;
        }
    ;

// 变量定义列表
VarDefList
    :   VarDefList COMMA VarDef {
            DeclStmt* node = dynamic_cast<DeclStmt*>($1);
            node->addNext(dynamic_cast<DefNode*>($3));
            $$ = node;
        }
    |   VarDef {
            DeclStmt* node = new DeclStmt(true);
            node->addNext(dynamic_cast<DefNode*>($1));
            $$ = node;
        }
    ;

// 变量定义
VarDef
    :   ID {
            // 首先判断是否重定义
            if(identifiers->isRedefine($1)) {
                fprintf(stderr, "identifier %s redefine\n", $1);
                exit(EXIT_FAILURE);
            }
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
            $$ = new DefNode(new Id(se), nullptr, false, false);
        }
    |   ID ASSIGN Exp {
            // 首先判断是否重定义
            if(identifiers->isRedefine($1)) {
                fprintf(stderr, "identifier %s redefine\n", $1);
                exit(EXIT_FAILURE);
            }
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
            $$ = new DefNode(new Id(se), dynamic_cast<Node*>($3), false, false);//类型向上转换
        }
    // 数组变量的定义
    |   ID ArrConstIndices {
            // 首先判断是否重定义
            if(identifiers->isRedefine($1)) {
                fprintf(stderr, "identifier %s redefine\n", $1);
                exit(EXIT_FAILURE);
            }
            Type* type;
            if(currentType->isInt()){
                type = new IntArrayType();
            }
            else{
                type = new FloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
            Id* id = new Id(se);
<<<<<<< HEAD
            id->addIndices((ExprStmtNode*)$2);
            $$ = new DefNode(id, nullptr, false, true);
=======
            id->addIndices(dynamic_cast<ExprStmtNode*>($2));
            $$ = new DefNode(id, nullptr, false, true);//类型向上转换
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
        }
    |   ID ArrConstIndices ASSIGN VarInitVal{
            // 首先判断是否重定义
            if(identifiers->isRedefine($1)) {
                fprintf(stderr, "identifier %s redefine\n", $1);
                exit(EXIT_FAILURE);
            }
            Type* type;
            if(currentType->isInt()){
                type = new IntArrayType();
            }
            else{
                type = new FloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            identifiers->install($1, se);
            Id* id = new Id(se);
<<<<<<< HEAD
            id->addIndices((ExprStmtNode*)$2);
            $$ = new DefNode(id, (Node*)$4, false, true);
=======
            id->addIndices(dynamic_cast<ExprStmtNode*>($2));
            $$ = new DefNode(id, dynamic_cast<Node*>($4), false, true);//类型向上转换
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
        }
    ;

// 变量初始化值
VarInitVal
    :   Exp {
            InitValNode* node = new InitValNode(false);
            node->setLeafNode(dynamic_cast<ExprNode*>($1));
            $$ = node;
        }
    // 数组变量的初始化值
    |   LBRACE VarInitValList RBRACE{
            $$ = $2;
        }
    |   LBRACE RBRACE{
            $$ = new InitValNode(false);
    }
    ; 

// 数组变量初始化列表
VarInitValList
    :   VarInitValList COMMA VarInitVal{
            InitValNode* node = dynamic_cast<InitValNode*>($1);
            node->addNext(dynamic_cast<InitValNode*>($3));
            $$ = node;
        }
    |   VarInitVal{
            InitValNode* newNode = new InitValNode(false);
            newNode->addNext(dynamic_cast<InitValNode*>($1));
            $$ = newNode;
        }
    ;

// 函数定义
FuncDef
    :   Type ID {
            Type *funcType;
            funcType = new FunctionType($1,{});
            SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
            identifiers->install($2, se);
            identifiers = new SymbolTable(identifiers);
        }
        LPAREN FuncParams{
            SymbolEntry *se;
            se = identifiers->lookup($2);
            assert(se != nullptr);
            if($5!=nullptr){
                //将函数参数类型写入符号表
                (dynamic_cast<FunctionType*>(se->getType()))->setparamsType(
                    (dynamic_cast<FuncDefParamsNode*>($5))->getParamsType()
                );
            }   
        } 
        RPAREN BlockStmt {
            SymbolEntry *se;
            se = identifiers->lookup($2);
            assert(se != nullptr);
            $$ = new FunctionDef(se, dynamic_cast<FuncDefParamsNode*>($5), $8);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
            delete []$2;
        }
    ;

// 函数参数列表
FuncParams
    :   FuncParams COMMA FuncParam {
            FuncDefParamsNode* node = dynamic_cast<FuncDefParamsNode*>($1);
            node->addNext((dynamic_cast<DefNode*>($3))->getId());
            $$ = node;
        }
    |   FuncParam {
            FuncDefParamsNode* node = new FuncDefParamsNode();
            node->addNext((dynamic_cast<DefNode*>($1))->getId());
            $$ = node;
        }
    |   %empty {
            $$ = nullptr;
        }
    ;

// 函数参数
FuncParam
    :   Type ID {
            SymbolEntry *se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
            identifiers->install($2, se);
            $$ = new DefNode(new Id(se), nullptr, false, false);
        }
    //数组函数参数
    |   Type ID LBRACKET RBRACKET ArrConstIndices{
            Type* arrayType; 
            if($1==TypeSystem::intType){
                arrayType = new IntArrayType();
<<<<<<< HEAD
            }
            else if($1==TypeSystem::floatType){
                arrayType = new FloatArrayType();
               
=======
                // (dynamic_cast<IntArrayType*>(arrayType))->pushBackDimension(-1);
            }
            else if($1==TypeSystem::floatType){
                arrayType = new FloatArrayType();
                // (dynamic_cast<FloatArrayType*>(arrayType))->pushBackDimension(-1);
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            }
            //最高维未指定，记为默认值-1
            SymbolEntry *addDim = new ConstantSymbolEntry(TypeSystem::constIntType, -1);
            dynamic_cast<ExprStmtNode*>($5)->addFirst(new Constant(addDim));
            SymbolEntry *se = new IdentifierSymbolEntry(arrayType, $2, identifiers->getLevel());
            identifiers->install($2, se);
            Id* id = new Id(se);
<<<<<<< HEAD
            id->addIndices((ExprStmtNode*)$5);
=======
            id->addIndices(dynamic_cast<ExprStmtNode*>($5));
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            $$ = new DefNode(id, nullptr, false, true);
        }
    |   Type ID LBRACKET RBRACKET{
            Type* arrayType; 
            if($1==TypeSystem::intType){
                arrayType = new IntArrayType();
<<<<<<< HEAD
            }
            else if($1==TypeSystem::floatType){
                arrayType = new FloatArrayType();
=======
                // (dynamic_cast<IntArrayType*>(arrayType))->pushBackDimension(-1);
            }
            else if($1==TypeSystem::floatType){
                arrayType = new FloatArrayType();
                // (dynamic_cast<FloatArrayType*>(arrayType))->pushBackDimension(-1);
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
            }
            //最高维未指定，记为默认值-1
            SymbolEntry *addDim = new ConstantSymbolEntry(TypeSystem::constIntType, -1);
            ExprStmtNode* indices = new ExprStmtNode();
            indices->addNext(new Constant(addDim));
            SymbolEntry *se = new IdentifierSymbolEntry(arrayType, $2, identifiers->getLevel());
            identifiers->install($2, se);
            Id* id = new Id(se);
            id->addIndices(indices);
            $$ = new DefNode(id, nullptr, false, true);
        }
    ;
    
%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}