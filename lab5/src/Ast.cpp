#include <iostream>
#include <string>
#include <assert.h>
#include "Ast.h"
#include "SymbolTable.h"
#include "Type.h"
#include "Unit.h"
#include "Instruction.h"
#include "IRBuilder.h"

extern FILE *yyout;
int Node::counter = 0;
IRBuilder* Node::builder = nullptr;

//we add
Type* returnType = nullptr;
bool funcReturned = false;
int inIteration = 0;//在迭代中
int genBr = 0;

Node::Node()
{
    seq = counter++;
}

Operand* Node::typeCast(Type* targetType, Operand* operand) {
    // 首先判断是否真的需要类型转化
    if(!TypeSystem::needCast(operand->getType(), targetType)) {
        return operand;
    }
    BasicBlock *bb = builder->getInsertBB();
    Operand* retOperand = new Operand(new TemporarySymbolEntry(targetType, SymbolTable::getLabel()));
    // 先实现bool扩展为int
    if(operand->getType()->isBool() && targetType->isInt()) {
        // 插入一条符号扩展指令
        new ZextInstruction(operand, retOperand, bb);
    }
    // 实现 int 到 float 的转换
    else if(operand->getType()->isInt() && targetType->isFloat()) {
        // 插入一条类型转化指令
        new IntFloatCastInstructionn(IntFloatCastInstructionn::I2F, operand, retOperand, bb);
    }
    // 实现 float 到 int 的转换
    else if(operand->getType()->isFloat() && targetType->isInt()) {
        // 插入一条类型转化指令
        new IntFloatCastInstructionn(IntFloatCastInstructionn::F2I, operand, retOperand, bb);
    }
    return retOperand;
}


void Node::backPatch(std::vector<Instruction*> &list, BasicBlock*bb)
{
    for(auto &inst:list)
    {
        if(inst->isCond())
            dynamic_cast<CondBrInstruction*>(inst)->setTrueBranch(bb);
        else if(inst->isUncond()){
            dynamic_cast<UncondBrInstruction*>(inst)->setBranch(bb);
        }
    }
}

std::vector<Instruction*> Node::merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2)
{
    std::vector<Instruction*> res(list1);
    res.insert(res.end(), list2.begin(), list2.end());
    return res;
}

void Ast::genCode(Unit *unit)
{
    IRBuilder *builder = new IRBuilder(unit);
    Node::setIRBuilder(builder);
    root->genCode();
}

void FunctionDef::genCode()
{
    Unit *unit = builder->getUnit();
    Function *func = new Function(unit, se);
    BasicBlock *entry = func->getEntry();
    // set the insert point to the entry basicblock of this function.
    builder->setInsertBB(entry);

    stmt->genCode();

    /**
     * Construct control flow graph. You need do set successors and predecessors for each basic block.
     * Todo
    */
   
}

void BinaryExpr::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Function *func = bb->getParent();
    if (op == AND)
    {
        BasicBlock *trueBB = new BasicBlock(func);  // if the result of lhs is true, jump to the trueBB.
        expr1->genCode();
        backPatch(expr1->trueList(), trueBB);
        builder->setInsertBB(trueBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        expr2->genCode();
        true_list = expr2->trueList();
        false_list = merge(expr1->falseList(), expr2->falseList());
    }
    else if(op == OR)
    {
        // Todo
    }
    else if(op >= LESS && op <= GREATER)
    {
        // Todo
    }
    else if(op >= ADD && op <= SUB)
    {
        expr1->genCode();
        expr2->genCode();
        Operand *src1 = expr1->getOperand();
        Operand *src2 = expr2->getOperand();
        int opcode;
        switch (op)
        {
        case ADD:
            opcode = BinaryInstruction::ADD;
            break;
        case SUB:
            opcode = BinaryInstruction::SUB;
            break;
        default:
            opcode = -1;
            break;
        }
        new BinaryInstruction(opcode, dst, src1, src2, bb);
    }
}

void Constant::genCode()
{
    // we don't need to generate code.
}

void Id::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getAddr();
    new LoadInstruction(dst, addr, bb);
}

void IfStmt::genCode()
{
    Function *func;
    BasicBlock *then_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), end_bb);

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    builder->setInsertBB(end_bb);
}

void IfElseStmt::genCode()
{
    // Todo
}

void CompoundStmt::genCode()
{
    // Todo
}

void SeqNode::genCode()
{
    // Todo
}
void DeclStmt::genCode()
{
    for(auto stmt : defList){
        stmt->genCode();
    }
}


// void DeclStmt::genCode()
// {
//     IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>(id->getSymPtr());
//     if(se->isGlobal())
//     {
//         Operand *addr;
//         SymbolEntry *addr_se;
//         addr_se = new IdentifierSymbolEntry(*se);
//         addr_se->setType(new PointerType(se->getType()));
//         addr = new Operand(addr_se);
//         se->setAddr(addr);
//     }
//     else if(se->isLocal())
//     {
//         Function *func = builder->getInsertBB()->getParent();
//         BasicBlock *entry = func->getEntry();
//         Instruction *alloca;
//         Operand *addr;
//         SymbolEntry *addr_se;
//         Type *type;
//         type = new PointerType(se->getType());
//         addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
//         addr = new Operand(addr_se);
//         alloca = new AllocaInstruction(addr, se);                   // allocate space for local id in function stack.
//         entry->insertFront(alloca);                                 // allocate instructions should be inserted into the begin of the entry block.
//         se->setAddr(addr);                                          // set the addr operand in symbol entry so that we can use it in subsequent code generation.
//     }
// }

void ReturnStmt::genCode()
{
    // Todo
}

void AssignStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    expr->genCode();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(lval->getSymPtr())->getAddr();
    Operand *src = expr->getOperand();
    /***
     * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
     * If you want to implement array, you have to caculate the address first and then store the result into it.
     */
    new StoreInstruction(addr, src, bb);
}
void EmptyStmtNode::genCode()
{
    // Todo
}
void ArrayindiceNode::genCode()
{
    for(auto expr : arrindexList){
        expr->genCode();
    }
}
void ArrayinitNode::genCode(){

}
void DefNode::genCode()
{
    Operand *addr;
    IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>(id->getSymPtr());
    if(se->isGlobal())
    {
        SymbolEntry *addr_se;
        addr_se = new IdentifierSymbolEntry(*se);
        addr_se->setType(new PointerType(se->getType()));
        addr = new Operand(addr_se);
        se->setAddr(addr);
        this->builder->getUnit()->insertDecl(se);
    }
    else if(se->isLocal())
    {
        Function *func = builder->getInsertBB()->getParent();
        BasicBlock *entry = func->getEntry();
        Instruction *alloca;
        SymbolEntry *addr_se;
        Type *type;
        type = new PointerType(se->getType());
        addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        addr = new Operand(addr_se);
        alloca = new AllocaInstruction(addr, se);                   // allocate space for local id in function stack.
        entry->insertFront(alloca);                                 // allocate instructions should be inserted into the begin of the entry block.
        se->setAddr(addr);                                          // set the addr operand in symbol entry so that we can use it in subsequent code generation.
    }
    //add array instructions here
    if(initVal!=nullptr){
        BasicBlock *bb = builder->getInsertBB();
        initVal->genCode();
        Operand *src = typeCast(se->getType(), dynamic_cast<ExprNode *>(initVal)->getOperand());
        /***
         * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
         * If you want to implement array, you have to caculate the address first and then store the result into it.
         */
        new StoreInstruction(addr, src, bb);
    }
}
//函数参数可以看作局部变量声明，而且还带赋值
void FuncDefParamsNode::genCode()
{
    Function *func = builder->getInsertBB()->getParent();
    BasicBlock *entry = func->getEntry();
    for(auto id : paramsList){
        func->insertParam(id->getOperand());
        IdentifierSymbolEntry* se = dynamic_cast<IdentifierSymbolEntry*>(id->getSymbolEntry());
        Type *type = new PointerType(id->getType());
        SymbolEntry *addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        Operand* addr = new Operand(addr_se);
        Instruction *alloca = new AllocaInstruction(addr, se);// allocate space for local id in function stack.
        entry->insertFront(alloca);                           // allocate instructions should be inserted into the begin of the entry block.
        se->setAddr(addr);
        Operand *src = id->getOperand();
        /***
         * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
         * If you want to implement array, you have to caculate the address first and then store the result into it.
         */
        new StoreInstruction(addr, src, entry);
    }
}

void Ast::typeCheck(Node** parentToChild)
{
    if(root != nullptr)
        root->typeCheck(parentToChild);
}

void FunctionDef::typeCheck(Node** parentToChild)
{
    // Todo
}

void BinaryExpr::typeCheck(Node** parentToChild)
{
    // Todo
}

void Constant::typeCheck(Node** parentToChild)
{
    // Todo
}

void Id::typeCheck(Node** parentToChild)
{
    // Todo
}

void IfStmt::typeCheck(Node** parentToChild)
{
    // Todo
}

void IfElseStmt::typeCheck(Node** parentToChild)
{
    // Todo
}

void CompoundStmt::typeCheck(Node** parentToChild)
{
    // Todo
}

void SeqNode::typeCheck(Node** parentToChild)
{
    // Todo
}

void DeclStmt::typeCheck(Node** parentToChild)
{
    // Todo
    for(int i = 0;i<(int)defList.size();++i){
        defList[i]->typeCheck(nullptr);
    }
}

void ReturnStmt::typeCheck(Node** parentToChild)
{
    // Todo
}

void AssignStmt::typeCheck(Node** parentToChild)
{
    // Todo
}
void EmptyStmtNode::typeCheck(Node** parentToChild){

}
void ArrayindiceNode::typeCheck(Node** parentToChild)
{
    for(int i = 0;i<(int)arrindexList.size();++i){
        arrindexList[i]->typeCheck((Node**)&(arrindexList[i]));
    }
}
void ArrayinitNode::typeCheck(Node** parentTochild){

}
// TODO: 这段代码逻辑太乱了，需要重构
void DefNode::typeCheck(Node** parentToChild)
{
    id->typeCheck(nullptr);
    // 不赋初值，直接返回
    if(initVal==nullptr){
        return;
    }
    initVal->typeCheck((Node**)&(initVal));

    if(!id->getType()->isArray()){//不是数组时，右边可能出现函数：int a = f();
        if(((ExprNode*)initVal)->getType()->isFunc() && 
            (!((FunctionType*)(((ExprNode*)initVal)->getType()))->getRetType()->calculatable())){//右边是个为返回值空的函数
            fprintf(stderr, "expected a return value, but functionType %s return nothing\n", ((ExprNode*)initVal)->getType()->toStr().c_str());
            exit(EXIT_FAILURE);
        }
    }
    if(id->getType()->isConst()){
        // 判断是否用变量给常量赋值
        if(!isArray) {
            if(!((ExprNode*)initVal)->getType()->isConst()) {
                fprintf(stderr, "attempt to initialize variable value to const\n");
                exit(EXIT_FAILURE);
            }
        }
        else{
            if(!this->isConst) {
                fprintf(stderr, "attempt to initialize variable value to const\n");
                exit(EXIT_FAILURE);
            }
        }
        // 接下来就是常量计算的工作了
        // 数组初始化值 暂时不打算做了
        if(id->getType()->isArray()){
            //TODO: initialize elements in symbol table
        }
        // 常量初始化值
        else{
            IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)id->getSymPtr();
            se->value = ((ConstantSymbolEntry*)((ExprNode*)initVal)->getSymPtr())->getValue();
        }   
    }
    // 如果是全局变量，也要根据需要赋值
    if(dynamic_cast<IdentifierSymbolEntry*>(id->getSymPtr())->isGlobal()) {
        // 对于初始化值不为空的，要进行初始化赋值
        if(initVal != nullptr) {
            // 只允许使用常量对全局变量进行赋值
            if(!((ExprNode*)initVal)->getType()->isConst()) {
                fprintf(stderr, "not allow to initialize global variable with not const value\n");
                exit(EXIT_FAILURE);
            }
            IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)id->getSymPtr();
            se->value = ((ConstantSymbolEntry*)((ExprNode*)initVal)->getSymPtr())->getValue();
        }
    }
}
void FuncDefParamsNode::typeCheck(Node** parentToChild){}

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

void ExprNode::setType(Type* type)
{
    symbolEntry->setType(type);
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

void EmptyStmtNode::output(int level)
{
    fprintf(yyout, "%*cEmptyStmt\n", level, ' ');
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
    return symbolEntry->getType()->isArray();
}

void Id::output(int level)
{
    std::string name, type;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    int scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
    if(isArray() && indices!=nullptr){
        indices->output(level+4);
    }
}

std::string Id::getName()
{
    return symbolEntry->toStr();
}

Type* Id::getType()
{
    return symbolEntry->getType();
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
void ArrayindiceNode::initDimInSymTable(IdentifierSymbolEntry* se)
{
    for(auto expr :arrindexList){
        // 既不是字面值常量，也不是常量表达式
        if(!(expr->getSymPtr()->isConstant() || expr->getType()->isConst())){
            fprintf(stderr, "array dimensions must be constant! %d %d\n", expr->getSymPtr()->isConstant(), expr->getType()->isConst());
            fprintf(stderr, "%d %d\n", (int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue(), (int)((IdentifierSymbolEntry*)(expr->getSymPtr()))->value);
            exit(EXIT_FAILURE);
        }
        // 字面值常量，值存在ConstantSymbolEntry中
        if(expr->getSymPtr()->isConstant()){
            se->arrayDimension.push_back((int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue());
        }
        // 常量表达式，值存在IdentifierSymbolEntry中
        else if(expr->getType()->isConst()){
            se->arrayDimension.push_back((int)((IdentifierSymbolEntry*)(expr->getSymPtr()))->value);
        }
    }
}

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    if(stmt!=nullptr){
    stmt->output(level + 4);
    }
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    stmt1->output(level + 4);
    stmt2->output(level + 4);
}

//we add

void ArrayinitNode::output(int level)
{
    std::string constStr = isConst ? "true" : "false";
    fprintf(yyout, "%*cArrayinitNode\tisConst:%s\n", level, ' ', constStr.c_str());
    for(auto child : innerList)
    {
        child->output(level+4);
    }
    if(leafNode!=nullptr){
        leafNode->output(level+4);
    }
}


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
    if(retValue!=nullptr){
        retValue->output(level + 4);
    }
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
    std::string name, type;
    name = funcId->getName();
    type = funcId->getType()->toStr();
    SymbolEntry* funcEntry = funcId->getSymbolEntry();
    int scope = dynamic_cast<IdentifierSymbolEntry*>(funcEntry)->getScope();
    fprintf(yyout, "%*cFuncCallNode\tfuncName: %s\t funcType: %s\tscope: %d\n", 
            level, ' ', name.c_str(), type.c_str(), scope);
    
    if(params!=nullptr){
        params->output(level+4);
    }
    else{
        fprintf(yyout, "%*cFuncCallWithNoParams\n", level+4, ' ');
    }
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

void ExprStmtNode::append(ExprNode* next)
{
    exprList.push_back(next);
}

void ExprStmtNode::output(int level)
{
    fprintf(yyout, "%*cExprStmtNode\n", level, ' ');
    for(auto expr : exprList)
    {
        expr->output(level+4);
    }
}