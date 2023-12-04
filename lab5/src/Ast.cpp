#include "Ast.h"
#include "SymbolTable.h"
#include "Unit.h"
#include "Instruction.h"
#include "IRBuilder.h"
#include <string>
#include "Type.h"
#include <assert.h>

extern FILE *yyout;
int Node::counter = 0;
IRBuilder* Node::builder = nullptr;
Type* returnType = nullptr;
bool funcReturned = false;
int inIteration = 0;//在迭代中
int inIf = 0;
BasicBlock* if_true_BB = nullptr;
BasicBlock* if_false_BB = nullptr;

std::stack<BasicBlock*> trueBrStack;
std::stack<BasicBlock*> falseBrStack;

std::stack<WhileStmt*> whileStack;  //判断嵌套while


Node::Node()
{
    seq = counter++;
}
void Node::backPatch(std::vector<BasicBlock**> &list, BasicBlock*target)
{
    if(list.empty()){
        list.push_back(&target);
    }
    else{
    //回填，将list全部填为target
    for(auto &bb:list){
        *bb = target;

    }
    }
}

std::vector<BasicBlock**> Node::merge(std::vector<BasicBlock**> &list1, std::vector<BasicBlock**> &list2)
{
    std::vector<BasicBlock**> res(list1);
    res.insert(res.end(), list2.begin(), list2.end());
    return res;
}

Operand* Node::typeCast(Type* targetType, Operand* operand) {
    //Todo
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

    if(params!=nullptr){
        params->genCode();
    }

    stmt->genCode();

    if(voidAddRet!=nullptr){
        voidAddRet->genCode();
    }

    /**
     * Construct control flow graph. You need do set successors and predecessors for each basic block.
     * Todo
    */
    //遍历blocks，设置控制流关系
     for (auto block = func->begin(); block != func->end(); block++) {
        // 清除ret之后的全部指令
        Instruction* index = (*block)->begin();
        while(index != (*block)->end()) {
            if(index->isRet()) {
                while(index != (*block)->rbegin()) {
                    (*block)->remove(index->getNext());
                }
                break;
            }
            index = index->getNext();
        }
        //std::cout<<(*block)->getNo()<<":"<<std::endl;
        // 获取该块的最后一条指令
        Instruction* last = (*block)->rbegin();
        // (*block)->output();
        // 对于有条件的跳转指令，需要对其true分支和false分支都设置控制流关系
        if (last->isCond()) {
            BasicBlock *trueBlock = dynamic_cast<CondBrInstruction*>(last)->getTrueBranch();
            BasicBlock *falseBlock = dynamic_cast<CondBrInstruction*>(last)->getFalseBranch();
             //std::cout<<(*block)->getNo()<<" true to" <<trueBlock->getNo()<<std::endl;
             //std::cout<<(*block)->getNo()<<" false to" <<falseBlock->getNo()<<std::endl;
            (*block)->addSucc(trueBlock);
            (*block)->addSucc(falseBlock);
            trueBlock->addPred(*block);
            falseBlock->addPred(*block);
        } 
        // 对于无条件的跳转指令，只需要对其目标基本块设置控制流关系即可
        if (last->isUncond()) {
            BasicBlock* dstBlock = dynamic_cast<UncondBrInstruction*>(last)->getBranch();
             //std::cout<<(*block)->getNo()<<"  to" <<dstBlock->getNo()<<std::endl;
            (*block)->addSucc(dstBlock);
            dstBlock->addPred(*block);
        }
    }



   
}

void BinaryExpr::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Function *func = bb->getParent();

    Type* UpperType = TypeSystem::getMaxType(expr1->getSymPtr()->getType(), expr2->getSymPtr()->getType());  //Todo
    if (op == AND)
    {
        BasicBlock *trueBB = new BasicBlock(func);  // if the result of lhs is true, jump to the trueBB.
        expr1->genCode();
        trueBrStack.push(trueBB);
        if(inIf){
            //std::cout<<"if and"<<std::endl;
            if_false_BB = falseBrStack.top();
            new CondBrInstruction(trueBB, if_false_BB, expr1->getOperand(), builder->getInsertBB());
        }
        backPatch(expr1->trueList(), trueBB);
        builder->setInsertBB(trueBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        trueBrStack.pop();     
        expr2->genCode();
        this->dst = expr2->getOperand();
        true_list = expr2->trueList();
        false_list = merge(expr1->falseList(), expr2->falseList());
    }
    else if(op == OR)
    {
        // Todo
        BasicBlock *falseBB = new BasicBlock(func);
        falseBrStack.push(falseBB);
        expr1->genCode();
        bb = builder->getInsertBB();
        if(inIf){
            //std::cout<<"if or "<<bb->getNo()<<std::endl;
            if_true_BB = trueBrStack.top();
            new CondBrInstruction(if_true_BB,falseBB, expr1->getOperand(), builder->getInsertBB());
            //std::cout<<expr1->getOperand()->toStr()<<" "<<expr1->getOperand()<<" true to"<<if_true_BB->getNo()<<" false to"<<falseBB->getNo()<<std::endl;
        }
        falseBrStack.pop();
        
        backPatch(expr1->falseList(),falseBB);
        builder->setInsertBB(falseBB);
        //std::cout<<"now bb "<<builder->getInsertBB()->getNo()<<std::endl;
        expr2->genCode();
        this->dst = expr2->getOperand();
        true_list = merge(expr1->trueList(), expr2->trueList());
        false_list = expr2->falseList();

    }
    // else if(op >= LESS && op <= GREATER)
    else if(op >= LESS && op <=NEQ)  //LESS,LE,GREATER,GE,EQ,NEQ
    {
        // Todo
        expr1->genCode();
        expr2->genCode();   // Both need to genCode
        Operand *src1 = typeCast(UpperType, expr1->getOperand());
        Operand *src2 = typeCast(UpperType, expr2->getOperand());
        int opcode = -1;
         switch (op)
        {
        case LESS:
            opcode = CmpInstruction::L;
            break;
        case LE:
            opcode = CmpInstruction::LE;
            break;
        case GREATER:
            opcode = CmpInstruction::G;
            break;
        case GE:
            opcode = CmpInstruction::GE;
            break;
        case EQ:
            opcode = CmpInstruction::E;
            break;
        case NEQ:
            opcode = CmpInstruction::NE;
            break;
        }
         if(UpperType->isFloat()) {
            new FCmpInstruction(opcode, dst, src1, src2, bb);
        }
        else {
            new CmpInstruction(opcode, dst, src1, src2, bb);
            //std::cout<<dst->toStr()<<" "<<dst<<std::endl;
        }
        
    }
    else if(op >= ADD && op <= MOD)
    {
        expr1->genCode();
        expr2->genCode();
        Operand *src1 = typeCast(UpperType, expr1->getOperand());
        Operand *src2 = typeCast(UpperType, expr2->getOperand());
        int opcode = -1;
        switch (op)
        {
        case ADD:
            opcode = BinaryInstruction::ADD;
            break;
        case SUB:
            opcode = BinaryInstruction::SUB;
            break;
        case MUL:
            opcode = BinaryInstruction::MUL;
            break;
        case DIV:
            opcode = BinaryInstruction::DIV;
            break;
        case MOD:
            opcode = BinaryInstruction::MOD;
            break;
        }
        if(UpperType->isFloat()) {
            new FBinaryInstruction(opcode, dst, src1, src2, bb);
        }
        else {
            new BinaryInstruction(opcode, dst, src1, src2, bb);
        }
    }
}

void UnaryOpExpr::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    if (op == SUB)
    {
        expr->genCode();
        Operand *src1;
        Operand *src2;
        if(expr->getSymPtr()->getType()->isBool()) {
            src1 = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
            src2 = typeCast(TypeSystem::intType, expr->getOperand());
            int opcode = BinaryInstruction::SUB;
            new BinaryInstruction(opcode, dst, src1, src2, bb);
        }
        else if(expr->getSymPtr()->getType()->isInt()){
            src1 = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
            src2 = typeCast(TypeSystem::intType, expr->getOperand());
            int opcode = BinaryInstruction::SUB;
            new BinaryInstruction(opcode, dst, src1, src2, bb);
            
        }
        else if(expr->getSymPtr()->getType()->isFloat()) {
            src1 = new Operand(new ConstantSymbolEntry(TypeSystem::constFloatType, 0));
            src2 = typeCast(TypeSystem::floatType, expr->getOperand());
            int opcode = FBinaryInstruction::SUB;
            new FBinaryInstruction(opcode, dst, src1, src2, bb);
        }
    }
    else if(op == NOT)
    {
        expr->genCode();
        Operand *src1 = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
        Operand *src2 = typeCast(TypeSystem::intType, expr->getOperand());
        new CmpInstruction(CmpInstruction::E, dst, src1, src2, bb);
    }

}

void Constant::genCode()
{
    // we don't need to generate code.
}

void Id::genCode()
{
    if(getType()->isConst()){
        return;
    }
    BasicBlock *bb = builder->getInsertBB();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getAddr();
    dst = new Operand(new TemporarySymbolEntry(dst->getType(), SymbolTable::getLabel()));
    new LoadInstruction(dst, addr, bb);
}

void ArrayIndiceNode::genCode(){

}

void ArrayinitNode::genCode(){

}

void DefNode::genCode(){
    Operand *addr = nullptr;
    IdentifierSymbolEntry *se = dynamic_cast<IdentifierSymbolEntry *>(id->getSymPtr());
    if(se->isGlobal())
    {
        SymbolEntry *addr_se;
        addr_se = new IdentifierSymbolEntry(*se);
        addr_se->setType(new PointerType(se->getType()));
        addr = new Operand(addr_se);
        se->setAddr(addr);
        this->builder->getUnit()->insertDecl(se);
        if(initVal!=nullptr ){
            if(!dynamic_cast<ExprNode*>(initVal)->getType()->isConst()){
                se->value = initVal->getVal();
            }
        }
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



void IfStmt::genCode()
{
    Function *func;
    BasicBlock *then_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);
    //std::cout<<"true no "<<then_bb->getNo()<<" false no"<<end_bb->getNo()<<std::endl;
    trueBrStack.push(then_bb);
    falseBrStack.push(end_bb);
    inIf = true;
    cond->genCode();
    BasicBlock *bb = builder->getInsertBB();
    new CondBrInstruction(then_bb, end_bb, cond->getOperand(), bb);
    //std::cout<<bb->getNo()<<" true to"<<then_bb->getNo()<<" false to "<<end_bb->getNo()<<std::endl;

    if_true_BB = nullptr;
    if_false_BB = nullptr;
    inIf = false;
    trueBrStack.pop();
    falseBrStack.pop();

    backPatch(cond->trueList(), then_bb); //ture ---> then_block
    backPatch(cond->falseList(), end_bb); //false --> end_block

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    builder->setInsertBB(end_bb);    // then_block is done, point to end_block
}

void IfElseStmt::genCode()
{
    // Todo
     Function *func;
    BasicBlock *then_bb, *else_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    else_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    trueBrStack.push(then_bb);
    falseBrStack.push(else_bb);
    inIf = true;

    cond->genCode();
    new CondBrInstruction(then_bb, else_bb, cond->getOperand(), builder->getInsertBB());
    if_true_BB = nullptr;
    if_false_BB = nullptr;
    inIf = false;
    trueBrStack.pop();
    falseBrStack.pop();
    backPatch(cond->trueList(), then_bb); // true --> then ; false -->else
    backPatch(cond->falseList(), else_bb);

    // 先then
    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);  //跳至end

    // 再else
    builder->setInsertBB(else_bb);
    elseStmt->genCode();
    else_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, else_bb);

    builder->setInsertBB(end_bb);
}


void WhileStmt::genCode(){

    whileStack.push(this);
    BasicBlock* stmt_bb, *cond_bb, *end_bb, *bb = builder->getInsertBB();
    Function* func = bb->getParent();
    stmt_bb = new BasicBlock(func);
    cond_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    this->condBlock = cond_bb;
    this->endBlock = end_bb;

    new UncondBrInstruction(cond_bb, bb); //第一次while,bb to cond_bb

    builder->setInsertBB(cond_bb);
    trueBrStack.push(stmt_bb);
    falseBrStack.push(end_bb);
    inIf = true;
    cond->genCode();
    if_true_BB = nullptr;
    if_false_BB = nullptr;
    trueBrStack.pop();
    falseBrStack.pop();
    inIf = false;
    new CondBrInstruction(stmt_bb,end_bb,cond->getOperand(),builder->getInsertBB());
    backPatch(cond->trueList(), stmt_bb);  //true --> stmt ; false -->end
    backPatch(cond->falseList(), end_bb);

    builder->setInsertBB(stmt_bb);
    Stmt->genCode();
    stmt_bb = builder->getInsertBB();  // update block
    new UncondBrInstruction(cond_bb, stmt_bb); // stmt to cond_bb

    // 重新调整插入点到end_bb
    builder->setInsertBB(end_bb);
    whileStack.pop();


}


void ContinueStmt::genCode(){
    assert(whileStack.size()!=0);
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* bb = builder->getInsertBB();
    // 首先获取当前所在的while
    WhileStmt* whileStmt = whileStack.top();
    // 获取条件判断block
    BasicBlock* cond_bb = whileStmt->getCondBlock();
    // 在当前基本块中生成一条跳转到条件判断的语句
    new UncondBrInstruction(cond_bb, bb);
    // 声明一个新的基本块用来插入后续的指令
    BasicBlock* nextBlock = new BasicBlock(func);
    builder->setInsertBB(nextBlock);
}

void BreakStmt::genCode(){
    assert(whileStack.size()!=0);
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* bb = builder->getInsertBB();
    // 首先获取当前所在的while
    WhileStmt* whileStmt = whileStack.top();
    // 获取条件判断block
    BasicBlock* end_bb = whileStmt->getEndBlock();
    // 在当前基本块中生成一条跳转到条件判断的语句
    new UncondBrInstruction(end_bb, bb);
    // 声明一个新的基本块用来插入后续的指令
    BasicBlock* nextBlock = new BasicBlock(func);
    builder->setInsertBB(nextBlock);
}

void CompoundStmt::genCode()
{
    // Todo
    stmt->genCode();
}

void SeqNode::genCode()
{
    for(auto stmt : stmtList){
        stmt->genCode();
    }
}

void EmptyStmtNode::genCode(){

}

void FuncDefParamsNode::genCode(){

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


void FuncCallParamsNode::genCode(){
    for(auto param: paramsList){
        param->genCode();
    }
}

std::vector<Operand*> FuncCallParamsNode::getOperandList()
{
    std::vector<Operand*> result;
    for(auto param : paramsList){
        result.push_back(param->getOperand());
    }
    return result;
}

void FuncCallNode::genCode(){
    IdentifierSymbolEntry* actualSE = dynamic_cast<IdentifierSymbolEntry*>(funcId->getSymPtr());
    if(actualSE->isLibFunc()){//若为库函数，则输出declare语句
        builder->getUnit()->insertDecl(actualSE);
    }
    //输出call语句
    //TODO: 内联函数
    BasicBlock *bb = builder->getInsertBB();
    //void 型函数不能返回
    if(params==nullptr){
        std::vector<Operand*> emptyList;
        new CallInstruction(dst, emptyList, dynamic_cast<IdentifierSymbolEntry*>(funcId->getSymPtr()), bb);
    }
    else{
        // 生成计算各个实参的中间代码
        params->genCode();
        // 完成实参形参之间的类型转换
        IdentifierSymbolEntry* funcSe = dynamic_cast<IdentifierSymbolEntry*>(funcId->getSymPtr());
        std::vector<Type*> paramsType = dynamic_cast<FunctionType*>(funcSe->getType())->getParamsType();
        std::vector<Operand*> passParams = params->getOperandList();
        std::vector<Operand*> realParams;
        for(int i = 0; i < (int)passParams.size(); i++) {
            realParams.push_back(typeCast(paramsType[i], passParams[i]));
        }
        new CallInstruction(dst, realParams, dynamic_cast<IdentifierSymbolEntry*>(funcId->getSymPtr()), bb);
    }

}

void ExprStmtNode::genCode(){
    for(auto expr:exprList){
        expr->genCode();
    }

}

void DeclStmt::genCode()
{

    for(auto &stmt:defList){
        stmt->genCode();
    }
}

void ReturnStmt::genCode()
{
    // Todo
    BasicBlock *bb = builder->getInsertBB();  //Current basic block
    if(retValue != nullptr) {
        retValue->genCode();
        //std::cout<<this->retType->toStr()<<std::endl;
        Operand* operand = typeCast(this->retType, retValue->getOperand());
        new RetInstruction(operand, bb);
    }
    else {
        new RetInstruction(nullptr, bb);
    }
}

void AssignStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    expr->genCode();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(lval->getSymPtr())->getAddr();
    Operand *src = typeCast(dynamic_cast<PointerType*>(addr->getType())->getValueType(), expr->getOperand());
    /***
     * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
     * If you want to implement array, you have to caculate the address first and then store the result into it.
     */
    new StoreInstruction(addr, src, bb);
}

void Ast::typeCheck()
{
    if(root != nullptr)
        root->typeCheck();
}

void FunctionDef::typeCheck()
{
    // Todo
    returnType = ((FunctionType*)se->getType())->getRetType();
    // 判断函数是否返回
    funcReturned = false;
    stmt->typeCheck();
    // 非void类型的函数需要有返回值
    if(!funcReturned && !returnType->isVoid()){
        fprintf(stderr, "expected a %s type to return, but no returned value found\n", returnType->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    // 如果void类型没写return需要补上
    if(!funcReturned && returnType->isVoid()) {
        this->voidAddRet = new ReturnStmt(nullptr);
    }
    returnType = nullptr;
}

void UnaryOpExpr::typeCheck(){
    expr->typeCheck();
    //检查是否void函数返回值参与运算
    Type* realType = expr->getType()->isFunc() ? 
        ((FunctionType*)expr->getType())->getRetType() : 
        expr->getType();
    if(!realType->calculatable()){
        fprintf(stderr, "type %s is not calculatable!\n", expr->getType()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    //推断父节点类型
    if(realType->isAnyFloat()) {
        this->setType(TypeSystem::floatType);
    }
    else{
        this->setType(TypeSystem::intType);
    }
    // 如果是not运算
    if(op == NOT) {
        this->setType(TypeSystem::boolType);
    }

    if(realType->isConst()){
        double val = 0;
        int initValue = expr->getSymPtr()->isConstant() ? 
            ((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue() : 
            ((IdentifierSymbolEntry*)(expr->getSymPtr()))->value;
        switch (op) 
        {
        case SUB:
            val = -initValue;
        break;
        case NOT:
            val = !initValue;
        break;
        }
        this->setVal(val);
    }
}

void BinaryExpr::typeCheck()
{
    // Todo
    expr1->typeCheck();
    expr2->typeCheck();
    //检查是否void函数返回值参与运算
    Type* realTypeLeft = expr1->getType()->isFunc() ? 
        ((FunctionType*)expr1->getType())->getRetType() : 
        expr1->getType();
    if(!realTypeLeft->calculatable()){
        fprintf(stderr, "type %s is not calculatable!\n", expr1->getType()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    Type* realTypeRight = expr2->getType()->isFunc() ? 
        ((FunctionType*)expr2->getType())->getRetType() : 
        expr2->getType();
    if(!realTypeRight->calculatable()){
        fprintf(stderr, "type %s is not calculatable!\n", expr2->getType()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    if(op == MOD) {
        if(!(realTypeLeft->isAnyInt() && realTypeRight->isAnyInt())) {
            fprintf(stderr, "mod is not supported with float or bool operands!\n");
            exit(EXIT_FAILURE);
        }
    }
    if(realTypeLeft->isConst() && realTypeRight->isConst()){
        if(this->getType()->isBool()) {
            bool val = 0;
            float leftValue = expr1->getSymPtr()->isConstant() ? 
                ((ConstantSymbolEntry*)(expr1->getSymPtr()))->getValue() : 
                ((IdentifierSymbolEntry*)(expr1->getSymPtr()))->value;
            float rightValue = expr2->getSymPtr()->isConstant() ? 
                ((ConstantSymbolEntry*)(expr2->getSymPtr()))->getValue() : 
                ((IdentifierSymbolEntry*)(expr2->getSymPtr()))->value;
            switch(op)
            {
            case AND:
                val = leftValue && rightValue;
            break;
            case OR:
                val = leftValue || rightValue;
            break;
            case LESS:
                val = leftValue < rightValue;
            break;
            case LE:
                val = leftValue <= rightValue;
            break;
            case GREATER:
                val = leftValue > rightValue;
            break;
            case GE:
                val = leftValue >= rightValue;
            break;
            case EQ:
                val = leftValue == rightValue;
            break;
            case NEQ:
                val = leftValue != rightValue;
            break;
            }
            this->setVal(val);
        }
        // 如果该节点结果的目标类型为int
        else if(this->getType()->isInt()){
            int val = 0;
            int leftValue = expr1->getSymPtr()->isConstant() ? 
                ((ConstantSymbolEntry*)(expr1->getSymPtr()))->getValue() : //字面值常量
                ((IdentifierSymbolEntry*)(expr1->getSymPtr()))->value;  //符号常量
            int rightValue = expr2->getSymPtr()->isConstant() ? 
                ((ConstantSymbolEntry*)(expr2->getSymPtr()))->getValue() : 
                ((IdentifierSymbolEntry*)(expr2->getSymPtr()))->value;
            switch (op) 
            {
            case ADD:
                val = leftValue + rightValue;
            break;
            case SUB:
                val = leftValue - rightValue;
            break;
            case MUL:
                val = leftValue * rightValue;
            break;
            case DIV:
                val = leftValue / rightValue;
            break;
            case MOD:
                val = leftValue % rightValue;
            break;
           
            }
            this->setVal(val);
        }
        // 如果该节点结果的目标类型为float
        else{
            float val = 0;
            float leftValue = expr1->getSymPtr()->isConstant() ? 
                ((ConstantSymbolEntry*)(expr1->getSymPtr()))->getValue() : 
                ((IdentifierSymbolEntry*)(expr1->getSymPtr()))->value;
            float rightValue = expr2->getSymPtr()->isConstant() ? 
                ((ConstantSymbolEntry*)(expr2->getSymPtr()))->getValue() : 
                ((IdentifierSymbolEntry*)(expr2->getSymPtr()))->value;
            switch (op) 
            {
            case ADD:
                val = leftValue + rightValue;
            break;
            case SUB:
                val = leftValue - rightValue;
            break;
            case MUL:
                val = leftValue * rightValue;
            break;
            case DIV:
                val = leftValue / rightValue;
            break;
            }
            this->setVal(val);
        }
        
    }
    // 调整 && 和 || 运算符的两个操作数
    // 操作数类型不为 bool，或者se是一个常量bool
    // 则说明此时的情况为 a || 1 或者 a && a + b
    // 增加一个和1的EQ判断
    if(op == AND || op == OR) {
        if(!expr1->getSymPtr()->getType()->isBool() || expr1->getSymPtr()->isConstant()) {
            Constant* zeroNode = new Constant(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
            TemporarySymbolEntry* tmpSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            BinaryExpr* newCond = new BinaryExpr(tmpSe, BinaryExpr::NEQ, zeroNode, expr1);
            expr1 = newCond;
        }
        if(!expr2->getSymPtr()->getType()->isBool() || expr2->getSymPtr()->isConstant()) {
            Constant* zeroNode = new Constant(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
            TemporarySymbolEntry* tmpSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            BinaryExpr* newCond = new BinaryExpr(tmpSe, BinaryExpr::NEQ, zeroNode, expr2);
            expr2 = newCond;
        }
    }
}

void Constant::typeCheck()
{
    // Todo
}

void ArrayIndiceNode::typeCheck(){

}

void ArrayinitNode::typeCheck(){

}

void DefNode::typeCheck(){
    //todo
     id->typeCheck();
    // 不赋初值，直接返回
    if(initVal==nullptr){
        return;
    }
    initVal->typeCheck();

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
            if(!((ArrayinitNode*)initVal)->isConst()) {
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
            // if(!((ExprNode*)initVal)->getType()->isConst()) {
            //     fprintf(stderr, "not allow to initialize global variable with not const value\n");
            //     exit(EXIT_FAILURE);
            // }
            IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)id->getSymPtr();
            se->value = ((ConstantSymbolEntry*)((ExprNode*)initVal)->getSymPtr())->getValue();
        }
    }

}

void Id::typeCheck()
{
    // Todo
   if(isArray() && indices!=nullptr){
        indices->typeCheck();
        // 检查indices下的exprList(私有域)中的每个exprNode的类型，若不为自然数则报错
        if(((IdentifierSymbolEntry*)getSymPtr())->arrayDimension.empty()){

        }
        // 读取常量数组 这个不打算做了
        else if(getType()->isConst()){
            //TODO: 将常量数组+全常量下标的数组元素访问替换为字面值常量节点Constant
            //STEP：1.遍历indices下的exprList(私有域)，查看是否有非常量节点。若有，直接返回
            //STEP: 2.若全部为常量下标，替换
        }
    }
}

void IfStmt::typeCheck()
{
    // Todo
    cond->typeCheck();
    // 如果cond中的se的类型不为 bool，或者se是一个常量bool
    // 则说明此时的情况为 if(a) 或者 if(1) 或者 if(a+1)
    // 增加一个和1的EQ判断
    if(!cond->getSymPtr()->getType()->isBool() || cond->getSymPtr()->isConstant()) {
        Constant* zeroNode = new Constant(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
        TemporarySymbolEntry* tmpSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        BinaryExpr* newCond = new BinaryExpr(tmpSe, BinaryExpr::NEQ, zeroNode, cond);
        cond = newCond;
    }
    if(thenStmt!=nullptr) {
        thenStmt->typeCheck();
    }
    else {
        thenStmt = new EmptyStmtNode();
    }
}

void IfElseStmt::typeCheck()
{
    // Todo
    cond->typeCheck();
    // 如果cond中的se的类型不为 bool，或者se是一个常量bool
    // 则说明此时的情况为 if(a) 或者 if(1) 或者 if(a+1)
    // 增加一个和1的EQ判断
    if(!cond->getSymPtr()->getType()->isBool() || cond->getSymPtr()->isConstant()) {
        Constant* zeroNode = new Constant(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
        TemporarySymbolEntry* tmpSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        BinaryExpr* newCond = new BinaryExpr(tmpSe, BinaryExpr::NEQ, zeroNode, cond);
        cond = newCond;
    }
    if(thenStmt!=nullptr) {
        thenStmt->typeCheck();
    }
    else {
        thenStmt = new EmptyStmtNode();
    }
    if(elseStmt!=nullptr){
        elseStmt->typeCheck();
    }
    else {
        elseStmt = new EmptyStmtNode();
    }
}

void WhileStmt::typeCheck(){
    cond->typeCheck();
    // 如果cond中的se的类型不为 bool，或者se是一个常量bool
    // 则说明此时的情况为 if(a) 或者 if(1) 或者 if(a+1)
    // 增加一个和1的EQ判断
    if(!cond->getSymPtr()->getType()->isBool() || cond->getSymPtr()->isConstant()) {
        Constant* zeroNode = new Constant(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
        TemporarySymbolEntry* tmpSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        BinaryExpr* newCond = new BinaryExpr(tmpSe, BinaryExpr::NEQ, zeroNode, cond);
        cond = newCond;
    }
    if(Stmt!=nullptr) {
        inIteration++;
        Stmt->typeCheck();
        inIteration--;
    }
    else {
        Stmt = new EmptyStmtNode();
    }

}

void ContinueStmt::typeCheck(){
    if(!inIteration){
        fprintf(stderr, "continue statement outside iterations\n");
        exit(EXIT_FAILURE);
    }

}

void BreakStmt::typeCheck(){
    if(!inIteration){
        fprintf(stderr, "break statement outside iterations\n");
        exit(EXIT_FAILURE);
    }

}

void CompoundStmt::typeCheck()
{
    // Todo
    if(stmt!=nullptr){
        stmt->typeCheck();
    }
    else {
        stmt = new EmptyStmtNode();
    }
}

void SeqNode::typeCheck()
{
    for(auto &stmt: stmtList){
        stmt->typeCheck();
    }
}

void DeclStmt::typeCheck()
{
    // Todo
    for(auto &expr: defList){
        expr->typeCheck();
    }
}

void ReturnStmt::typeCheck()
{
    // Todo
     if(returnType == nullptr){//not in a fuction
        fprintf(stderr, "return statement outside functions\n");
        exit(EXIT_FAILURE);
    }
    else if(returnType->isVoid() && retValue!=nullptr){//returned a value in void()
        fprintf(stderr, "value returned in a void() function\n");
        exit(EXIT_FAILURE);
    }
    else if(!returnType->isVoid() && retValue==nullptr){//expected returned value, but returned nothing
        fprintf(stderr, "expected a %s type to return, but returned nothing\n", returnType->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    if(!returnType->isVoid()){
        retValue->typeCheck();
    }
    this->retType = returnType;
    funcReturned = true;
}

void AssignStmt::typeCheck()
{
    // Todo
    lval->typeCheck();
    expr->typeCheck();
    if(lval->getType()->isConst()) {
        fprintf(stderr, "Unable to assign value to const variable %s\n", lval->getSymPtr()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    if(expr->getType()->isFunc() && ((FunctionType*)(expr->getType()))->getRetType()->isVoid()){//返回值为void的函数做运算数
        fprintf(stderr, "expected a return value, but functionType %s returns nothing\n", expr->getType()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
}

void EmptyStmtNode::typeCheck(){

}

void FuncDefParamsNode::typeCheck(){
    //  for(ExprNode* param : paramsList) {
    //     param->typeCheck();
    // }

}

void FuncCallParamsNode::typeCheck(){
    for(auto &param:paramsList){
        param->typeCheck();
    }
}

void FuncCallNode::typeCheck(){
    //todo
     std::vector<Type*> funcParamsType = (dynamic_cast<FunctionType*>(this->funcId->getSymPtr()->getType()))->getParamsType();
    // 首先对于无参的进行检查
    if(this->params==nullptr && funcParamsType.size() != 0){
        fprintf(stderr, "function %s call params number is not consistent\n",this->funcId->getSymPtr()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    else if(this->params==nullptr) {
        return;
    }
    // 先对FuncCallParamsNode进行类型检查，主要是完成常量计算
    this->params->typeCheck(); 
    std::vector<ExprNode*> funcCallParams = this->params->getParamsList();
    // 如果数量不一致直接报错
    if(funcCallParams.size() != funcParamsType.size()) {
        fprintf(stderr, "function %s call params number is not consistent\n",this->funcId->getSymPtr()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    // 然后进行类型匹配
    // 依次匹配类型
    for(int i = 0; i < (int)funcParamsType.size(); i++){
        Type* needType = funcParamsType[i];
        Type* giveType = funcCallParams[i]->getSymPtr()->getType();
        // 暂时不考虑类型转化的问题 所有的类型转化均到IR生成再做
        // 除了void类型都可以进行转化
        if((!needType->calculatable() && giveType->calculatable())
         ||(needType->calculatable() && !giveType->calculatable())){
            fprintf(stderr, "function %s call params type is not consistent\n",this->funcId->getSymPtr()->toStr().c_str());
            exit(EXIT_FAILURE);
        }
        // 检查数组是否匹配
        if((!needType->isArray() && giveType->isArray())
         ||(needType->isArray() && !giveType->isArray())){
            fprintf(stderr, "function %s call params type is not consistent\n",this->funcId->getSymPtr()->toStr().c_str());
            exit(EXIT_FAILURE);
        }
        //TODO: 检查数组维度是否匹配
        if(needType->isArray() && giveType->isArray()){

        }
    }
}

void ExprStmtNode::typeCheck(){
    for(auto &stmt : exprList){
        stmt->typeCheck();
    }
    
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
    fprintf(yyout, "%*cBinaryExpr\t%s\top: %s\n", level, ' ',dst->toStr().c_str(), op_str.c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

void UnaryOpExpr::output(int level){
     std::string op_str;
    switch(op)
    {
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

void ArrayIndiceNode::append(ExprNode* next)
{
    arrindexList.push_back(next);
}

void ArrayIndiceNode::output(int level)
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
    if(stmt!=nullptr){
    stmt->output(level + 4);
    }
}

void SeqNode::append(StmtNode* next)
{
    stmtList.push_back(next);
}

void SeqNode::output(int level)
{
    fprintf(yyout, "%*cSequence\n", level, ' ');
    for(auto stmt : stmtList)
    {
        stmt->output(level + 4);
    }
}

//we add

void ArrayinitNode::output(int level)
{
    std::string constStr = isconst ? "true" : "false";
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


