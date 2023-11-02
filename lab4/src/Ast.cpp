#include "Ast.h"
#include "SymbolTable.h"
#include <string>
#include "Type.h"

extern FILE *yyout;
int Node::counter = 0;

Node::Node()
{
    seq = counter++;
}

void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

Type* ExprNode::getType()
{
    return symbolEntry->getType();
}

void BinaryExpr::output(int level)
{
    std::string op_str;
    switch(op)
    {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case AND:
            op_str = "and";
            break;
        case OR:
            op_str = "or";
            break;
        case LESS:
            op_str = "less";
            break;
        case MUL:
            op_str = "mul";
            break;
        case DIV:
            op_str = "div";
            break;
        case MOD:
            op_str = "mod";
            break;
        case LE:
            op_str = "LESS OR EQUAL";
            break;
        case GREATER:
            op_str = "greater";
            break;
        case GE:
            op_str="greater or equal";
            break;
        case EQ:
            op_str = "equal";
            break;
        case NEQ:
            op_str = "not equal";
            break;
    }
    fprintf(yyout, "%*cBinaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

void UnaryOpExpr::output(int level){
     std::string op_str;
    switch(op)
    {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case NOT:
            op_str = "not";
            break;
    }
    fprintf(yyout, "%*cUnaryOpExpr\top: %s\n", level, ' ', op_str.c_str());
    expr->output(level + 4);
}

void Constant::output(int level)
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    fprintf(yyout, "%*cIntegerLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

bool Id::isArray()
{
    return getType()->isArray();
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
    if(isArray() && indices!=nullptr){
        indices->output(level+4);
    }
}

void ArrayindiceNode::append(ExprNode* next)
{
    arrindexList.push_back(next);
}

void ArrayindiceNode::output(int level)
{
    fprintf(yyout, "%*cArrayindiceNode\n", level, ' ');
    for(auto expr : arrindexList)
    {
        expr->output(level+4);
    }
}


void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    stmt->output(level + 4);
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level + 4);
    stmt2->output(level + 4);
}

//we add
void DefNode::output(int level)
{
    std::string constStr = isConst ? "true" : "false";
    std::string arrayStr = isArray ? "true" : "false";
    fprintf(yyout, "%*cDefNode\tisConst:%s\tisArray:%s\n", level, ' ', constStr.c_str(), arrayStr.c_str());
    id->output(level+4);
    if(initVal == nullptr){
        fprintf(yyout, "%*cnull\n", level+4, ' ');
    }
    else{
        initVal->output(level+4);
    }
}

void DeclStmt::addNext(DefNode* next)
{
    defList.push_back(next);
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    for(auto def : defList){
        def->output(level+4);
    }
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}

void IfElseStmt::output(int level)
{
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

void WhileStmt::output(int level){
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    Stmt->output(level + 4);    
}


void ContinueStmt::output(int level){
    fprintf(yyout,"%*cContinueStmt\n",level,' ');
}

void BreakStmt::output(int level){
    fprintf(yyout,"%*cBreakStmt\n",level,' ');
}

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    retValue->output(level + 4);
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}


//WE ADD BEGIN
void FuncDefParamsNode::addNext(Id* next)
{
    paramsList.push_back(next);
}

std::vector<Type*> FuncDefParamsNode::getParamsType()
{
    std::vector<Type*> typeArray;
    for(auto param : paramsList){
        typeArray.push_back(param->getType());
    }
    return typeArray;
}

void FuncDefParamsNode::output(int level)
{
    fprintf(yyout, "%*cFuncDefParamsNode\n", level, ' ');
    for(auto param : paramsList){
        param->output(level+4);
    }
}
//WE ADD END

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    stmt->output(level + 4);
}

void FuncCallNode::output(int level)
{
    // std::string name, type;
    // int scope;
    // SymbolEntry* funcEntry = funcId->getSymbolEntry();
    // name = funcEntry->toStr();
    // type = funcEntry->getType()->toStr();
    // scope = dynamic_cast<IdentifierSymbolEntry*>(funcEntry)->getScope();
    // fprintf(yyout, "%*cFuncCallNode\tfuncName: %s\t funcType: %s\tscope: %d\n", 
    //         level, ' ', name.c_str(), type.c_str(), scope);
    // if(params!=nullptr){
    //     params->output(level+4);
    // }
    // else{
    //     fprintf(yyout, "%*cFuncCallParamsNode NULL\n", level+4, ' ');
    // }
}

void FuncCallParamsNode::append(ExprNode* next)
{
    paramsList.push_back(next);
}

void FuncCallParamsNode::output(int level)
{
    fprintf(yyout, "%*cFuncCallParamsNode\n", level, ' ');
    for(auto param : paramsList){
        param->output(level+4);
    }
}

// void CompoundStmt::output(int level)
// {
//     fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
//     if(stmt == nullptr){
//         fprintf(yyout, "%*cNull Stmt\n", level+4, ' ');
//     }
//     else{
//         stmt->output(level + 4);
//     }
// }
