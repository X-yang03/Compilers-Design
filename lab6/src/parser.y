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
    int iType;
    double fType;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
}

%start Program
%token <strtype> ID 
%token <iType>  INTEGER
%token <fType>  FLOATNUM
%token IF ELSE WHILE
%token INT VOID FLOAT
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON LBRACKET RBRACKET PARSE
%token ADD SUB MUL DIV MOD OR AND LESS LE GREATER GE ASSIGN EQ NEQ NOT
%token CONST RETURN CONTINUE BREAK

%type <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt WhileStmt ReturnStmt DeclStmt FuncDef BreakStmt ContinueStmt ExpStmt Exps
%type <stmttype> VarDefList VarDef ConstDefList ConstDef
%type <stmttype> ArrIndices ArrayInitVal ArrayInitValList ConstArrayInitVal ConstArrayInitValList
%type <exprtype> Exp ConstExp AddExp Cond LOrExp PrimaryExp LVal RelExp LAndExp UnaryExp MulExp EqExp 
%type <stmttype> FuncParams FuncParam FuncRealParams
%type <type> Type
//%nterm <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt ReturnStmt DeclStmt FuncDef
//%nterm <exprtype> Exp AddExp Cond LOrExp PrimaryExp LVal RelExp LAndExp
//%nterm <type> Type

%precedence THEN
%precedence ELSE
%%
Program
    : Stmts {
        ast.setRoot($1);
    }
    ;

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
Stmt
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
    ;
LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se);
        
         // std::cout<<$$->getType()->toStr();
         // std::cout<<"test"<<std::endl;
        delete []$1;
    }
    |
    ID ArrIndices {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        Id* newId = new Id(se);
        newId->addIndices((ExprStmtNode*)$2);
        $$ =  newId;
        delete []$1;
    }
    ;
AssignStmt
    :
    LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    ;
BlockStmt
    :   LBRACE 
        {
            identifiers = new SymbolTable(identifiers);
        } 
        Stmts RBRACE 
        {
            $$ = new CompoundStmt($3);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
        |   LBRACE RBRACE {
            $$ = new CompoundStmt(nullptr);
        }
    ;
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;
WhileStmt 
    : WHILE LPAREN Cond RPAREN Stmt{
        $$ = new WhileStmt($3, $5);
    }

ContinueStmt
    : CONTINUE SEMICOLON{
        $$ = new ContinueStmt();
    }

BreakStmt
    : BREAK SEMICOLON{
        $$ = new BreakStmt();
    }

ReturnStmt
    :
    RETURN Exp SEMICOLON{
        $$ = new ReturnStmt($2);
    }
    |   RETURN SEMICOLON {
         $$ = new ReturnStmt(nullptr);
    }
    ;

ExpStmt
    :   Exps SEMICOLON{$$ = $1;}
    ;

Exps
    :  ExpStmt PARSE Exp {
            ExprStmtNode* node = (ExprStmtNode*)$1;
            node->addNext($3);
            $$ = node;
        }
    |   Exp {
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext($1);
            $$ = node;
        }
    ;

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
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext($2);
            $$ = node;

        }
    ;

ConstDefList 
    : ConstDefList PARSE ConstDef{
            DeclStmt* node = (DeclStmt*) $1;
            node->addNext((DefNode*)$3);
            $$ = node;
    }
    | ConstDef {
            DeclStmt* node = new DeclStmt(true);
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
            Id* id = new Id(se);
            id->addIndices(dynamic_cast<ExprStmtNode*>($2));
            // 类型向上转换
            $$ = new DefNode(id, dynamic_cast<Node*>($4), true, true);
        

        }

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
    }
    ; 

ArrayInitValList
    :   ArrayInitValList PARSE ArrayInitVal{
            InitValNode* node = (InitValNode*)$1;
            node->addNext((InitValNode*)$3);
            $$ = node;
        }
    |   ArrayInitVal{
            InitValNode* newNode = new InitValNode(false);
            newNode->addNext((InitValNode*)$1);
            $$ = newNode;
        }
    ;

VarDefList
    :   VarDefList PARSE VarDef {
            DeclStmt* node = (DeclStmt*) $1;
            node->addNext((DefNode*)$3);
            $$ = node;
        }
    |   VarDef {
            DeclStmt* node = new DeclStmt(false);
            node->addNext((DefNode*)$1);
            $$ = node;
        }
    ;
VarDef
    :   ID {
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            //identifiers->install($1, se);
            if(identifiers->lookupOneLevel($1) == nullptr){
                identifiers->install($1, se);
            }else{
                fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)$1);
                assert(identifiers->lookupOneLevel($1) == nullptr);
            }
            $$ = new DefNode(new Id(se), nullptr, false, false);
        }
    |   ID ASSIGN Exp {
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            //identifiers->install($1, se);
            if(identifiers->lookupOneLevel($1) == nullptr){
                identifiers->install($1, se);
            }else{
                fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)$1);
                assert(identifiers->lookupOneLevel($1) == nullptr);
            }
            $$ = new DefNode(new Id(se), (Node*)$3, false, false);
        }
    |   ID ArrIndices {
            Type* type;
            if(currentType->isInt()){
                type = new IntArrayType();
            }
            else{
                type = new FloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            //identifiers->install($1, se);
            if(identifiers->lookupOneLevel($1) == nullptr){
                identifiers->install($1, se);
            }else{
                fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)$1);
                assert(identifiers->lookupOneLevel($1) == nullptr);
            }
            Id* id = new Id(se);
            id->addIndices((ExprStmtNode*)$2);
            $$ = new DefNode(id, nullptr, false, true);
        }
    |   ID ArrIndices ASSIGN ArrayInitVal{
            Type* type;
            if(currentType->isInt()){
                type = new IntArrayType();
            }
            else{
                type = new FloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, $1, identifiers->getLevel());
            //identifiers->install($1, se);
            if(identifiers->lookupOneLevel($1) == nullptr){
                identifiers->install($1, se);
            }else{
                fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)$1);
                assert(identifiers->lookupOneLevel($1) == nullptr);
            }
            Id* id = new Id(se);
            id->addIndices((ExprStmtNode*)$2);
            $$ = new DefNode(id, (Node*)$4, false, true);
        }
FuncDef
    :
    Type ID {
        // 返回值类型是ID的type，函数定义中需要创建新的符号表
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
                 (dynamic_cast<FunctionType*>(se->getType()))->setparamsType(
                    (dynamic_cast<FuncDefParamsNode*>($5))->getParamsType()
                );
            }   
        }  
    RPAREN
    BlockStmt
    {
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
    :   FuncParams PARSE FuncParam {
            FuncDefParamsNode* node = (FuncDefParamsNode*)$1;
            node->addNext(((DefNode*)$3)->getId());
            $$ = node;
        }
    |   FuncParam {
            FuncDefParamsNode* node = new FuncDefParamsNode();
            node->addNext(((DefNode*)$1)->getId());
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
    | Type ID LBRACKET RBRACKET ArrIndices{
            Type* arrayType = nullptr; 
            if($1==TypeSystem::intType){
                arrayType = new IntArrayType();
            }
            else if($1==TypeSystem::floatType){
                arrayType = new FloatArrayType();
               
            }
            //最高维未指定，记为默认值-1
            SymbolEntry *addDim = new ConstantSymbolEntry(TypeSystem::constIntType, -1);
            dynamic_cast<ExprStmtNode*>($5)->addFirst(new Constant(addDim));
            SymbolEntry *se = new IdentifierSymbolEntry(arrayType, $2, identifiers->getLevel());
            identifiers->install($2, se);
            Id* id = new Id(se);
            id->addIndices((ExprStmtNode*)$5);
            $$ = new DefNode(id, nullptr, false, true);
        }
    |   Type ID LBRACKET RBRACKET{
            Type* arrayType = nullptr; 
            if($1==TypeSystem::intType){
                arrayType = new IntArrayType();
            }
            else if($1==TypeSystem::floatType){
                arrayType = new FloatArrayType();
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
