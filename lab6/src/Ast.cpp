#include <iostream>
#include <string>
#include <assert.h>
#include "Ast.h"
#include "SymbolTable.h"
#include "Type.h"
#include "Unit.h"
#include "Instruction.h"
#include "IRBuilder.h"
#include "ArrayUtil.h"

extern FILE *yyout;
int Node::counter = 0;
IRBuilder* Node::builder = nullptr;
Type* returnType = nullptr;
bool funcReturned = false;
int inIteration = 0;//在迭代中
<<<<<<< HEAD
int inIf = 0;
BasicBlock* if_true_BB = nullptr;
BasicBlock* if_false_BB = nullptr;

std::stack<BasicBlock*> trueBrStack;   //用栈替代回填
std::stack<BasicBlock*> falseBrStack;

std::stack<WhileStmt*> whileStack;  //判断嵌套while

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
=======
int genBr = 0;
>>>>>>> 952f69e01c68e82866d21d701853de8691377611

Operand* Node::typeCast(Type* targetType, Operand* operand) {
    // 首先判断是否真的需要类型转化
    if(!TypeSystem::needCast(operand->getType(), targetType)) {
        return operand;
    }
    BasicBlock *bb = builder->getInsertBB();
    //Function *func = bb->getParent();
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

//lab6 added
<<<<<<< HEAD

=======
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
>>>>>>> 952f69e01c68e82866d21d701853de8691377611

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
    if(this->voidAddRet != nullptr) {
        voidAddRet->genCode();
    }

    // 遍历Function中所有的BasicBlock，在各个BasicBlock之间建立控制流关系
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
        // 获取该块的最后一条指令
        Instruction* last = (*block)->rbegin();
        // (*block)->output();
        // 对于有条件的跳转指令，需要对其true分支和false分支都设置控制流关系
        if (last->isCond()) {
            BasicBlock *trueBlock = dynamic_cast<CondBrInstruction*>(last)->getTrueBranch();
            BasicBlock *falseBlock = dynamic_cast<CondBrInstruction*>(last)->getFalseBranch();
            (*block)->addSucc(trueBlock);
            (*block)->addSucc(falseBlock);
            trueBlock->addPred(*block);
            falseBlock->addPred(*block);
        } 
        // 对于无条件的跳转指令，只需要对其目标基本块设置控制流关系即可
        if (last->isUncond()) {
            BasicBlock* dstBlock = dynamic_cast<UncondBrInstruction*>(last)->getBranch();
            (*block)->addSucc(dstBlock);
            dstBlock->addPred(*block);
        }
    }
}

void BinaryExpr::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    Function *func = bb->getParent();
    Type* maxType = TypeSystem::getMaxType(expr1->getSymPtr()->getType(), expr2->getSymPtr()->getType());
    if (op == AND)
    {
        BasicBlock *trueBB = new BasicBlock(func);  // if the result of lhs is true, jump to the trueBB.
        genBr = 1;
        expr1->genCode();
        backPatch(expr1->trueList(), trueBB);
        builder->setInsertBB(trueBB);               // set the insert point to the trueBB so that intructions generated by expr2 will be inserted into it.
        expr2->genCode();
        true_list = expr2->trueList();
        false_list = merge(expr1->falseList(), expr2->falseList());

    }
    else if(op == OR)
    {
        BasicBlock *falseBB = new BasicBlock(func);
        genBr = 1;
        expr1->genCode();
        backPatch(expr1->falseList(), falseBB);
        builder->setInsertBB(falseBB);
        expr2->genCode();
        true_list = merge(expr1->trueList(), expr2->trueList());
        false_list = expr2->falseList();
    }
    else if(op >= LESS && op <= NEQ)
    {
<<<<<<< HEAD

        expr1->genCode();
        expr2->genCode();
=======
        genBr--;
        expr1->genCode();
        expr2->genCode();
        genBr++;
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
        Operand *src1 = typeCast(maxType, expr1->getOperand());
        Operand *src2 = typeCast(maxType, expr2->getOperand());
        int opcode;
        switch (op)
        {
        case LESS:
            opcode = CmpInstruction::L;
            break;
        case LESSEQ:
            opcode = CmpInstruction::LE;
            break;
        case GREAT:
            opcode = CmpInstruction::G;
            break;
        case GREATEQ:
            opcode = CmpInstruction::GE;
            break;
        case EQ:
            opcode = CmpInstruction::E;
            break;
        case NEQ:
            opcode = CmpInstruction::NE;
            break;
        }
        if(maxType->isFloat()) {
            new FCmpInstruction(opcode, dst, src1, src2, bb);
        }
        else {
            new CmpInstruction(opcode, dst, src1, src2, bb);
        }
        if(genBr > 0){
            // 跳转目标block
            BasicBlock* trueBlock, *falseBlock, *mergeBlock;
            trueBlock = new BasicBlock(func);
            falseBlock = new BasicBlock(func);
            mergeBlock = new BasicBlock(func);
            true_list.push_back(new CondBrInstruction(trueBlock, falseBlock, dst, bb));
            false_list.push_back(new UncondBrInstruction(mergeBlock, falseBlock));
        }
    }
    else if(op >= ADD && op <= MOD)
    {
        expr1->genCode();
        expr2->genCode();
        Operand *src1 = typeCast(maxType, expr1->getOperand());
        Operand *src2 = typeCast(maxType, expr2->getOperand());
        int opcode;
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
        if(maxType->isFloat()) {
            new FBinaryInstruction(opcode, dst, src1, src2, bb);
        }
        else {
            new BinaryInstruction(opcode, dst, src1, src2, bb);
        }
    }
}

void OneOpExpr::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
<<<<<<< HEAD
=======
    Function *func = bb->getParent();
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
    /*
    * 取相反数的操作可能会涉及到int float和bool
    * 对于int和float指令，运算所需要的type即为本身的type
    * 对于bool，运算所需要的type转换为int类型
    */
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
<<<<<<< HEAD

=======
        genBr--;
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
        expr->genCode();
        genBr++;
        Operand *src1 = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
        Operand *src2 = typeCast(TypeSystem::intType, expr->getOperand());
        new CmpInstruction(CmpInstruction::E, dst, src1, src2, bb);
<<<<<<< HEAD
       
=======
        if(genBr > 0) {
            // 跳转目标block
            BasicBlock* trueBlock, *falseBlock, *mergeBlock;
            trueBlock = new BasicBlock(func);
            falseBlock = new BasicBlock(func);
            mergeBlock = new BasicBlock(func);
            true_list.push_back(new CondBrInstruction(trueBlock, falseBlock, dst, bb));
            false_list.push_back(new UncondBrInstruction(mergeBlock, falseBlock));
        }
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
    }
}

void Constant::genCode()
{
    // we don't need to generate code.
}

void Id::genCode()
{
    if(getType()->isConst() && !getType()->isArray()){
        return;
    }
    BasicBlock *bb = builder->getInsertBB();
    Operand *addr = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getAddr();
    dst = new Operand(new TemporarySymbolEntry(dst->getType(), SymbolTable::getLabel()));
    if(getType()->isArray()){
        Operand* offset = nullptr;
        if(indices!=nullptr){
            indices->genCode();
            offset = indices->exprList[0]->getOperand();
        }
        std::vector<int> dimensions;
        if(getType()->isIntArray()){
            dimensions = dynamic_cast<IntArrayType*>(getType())->getDimensions();
        }
        else if(getType()->isConstIntArray()) {
            dimensions = dynamic_cast<ConstIntArrayType*>(getType())->getDimensions();
        }
        else if(getType()->isFloatArray()){
            dimensions = dynamic_cast<FloatArrayType*>(getType())->getDimensions();
        }
        else {
            dimensions = dynamic_cast<ConstFloatArrayType*>(getType())->getDimensions();
        }
        //如果是函数参数传入的数组指针，其最后一个维度为-1
        //此时需要生成新的load指令获取其地址
        if(dimensions[0]==-1){
            // printf("%d\n", dimensions[1]);
            TemporarySymbolEntry* se = new TemporarySymbolEntry(getType(), SymbolTable::getLabel());
            Operand* new_addr = new Operand(se);
            new LoadInstruction(new_addr, addr, bb);
            addr = new_addr;
        }
        for(unsigned int i = 1; indices!=nullptr && i < indices->exprList.size(); i++) {
            Operand* dim_i = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, dimensions[i]));
            TemporarySymbolEntry* se1 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            Operand* offset1 = new Operand(se1);
            new BinaryInstruction(BinaryInstruction::MUL, offset1, offset, dim_i, bb);  //offset1 = offset * dimensions[i]
            TemporarySymbolEntry* se2 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            offset = new Operand(se2);
            new BinaryInstruction(BinaryInstruction::ADD, offset, offset1, indices->exprList[i]->getOperand(), bb); //offset = offset1 + indices[i]
        }
        //索引维度<总维度，需要再乘一次最后的维度
        if(indices!=nullptr && indices->exprList.size()<dimensions.size()){
            Operand* dim_i = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, dimensions[indices->exprList.size()]));
            TemporarySymbolEntry* se1 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            Operand* offset1 = new Operand(se1);
            new BinaryInstruction(BinaryInstruction::MUL, offset1, offset, dim_i, bb);  //offset1 = offset * dimensions[i]
            offset = offset1;
        }
        Operand* offset1 = nullptr;
        if(indices!=nullptr){
            TemporarySymbolEntry* se1 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            offset1 = new Operand(se1);
            Operand* align = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, 4));
            new BinaryInstruction(BinaryInstruction::MUL, offset1, offset, align, bb);  //offset1 = offset * 4
        }
        else{
            offset1 = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
        }
        TemporarySymbolEntry* se2 = new TemporarySymbolEntry(getType(), SymbolTable::getLabel());
        Operand* offset_final = new Operand(se2);
        // 全局变量地址标签不能直接参与运算，需要先load
        if(dynamic_cast<IdentifierSymbolEntry*>(getSymbolEntry())->isGlobal()){
            TemporarySymbolEntry* se3 = new TemporarySymbolEntry(getType(), SymbolTable::getLabel());
            Operand* new_addr = new Operand(se3);
            new LoadInstruction(new_addr, addr, bb);
            addr = new_addr;
            se2->setGlobalArray();
            dynamic_cast<TemporarySymbolEntry*>(dst->getEntry())->setGlobalArray();
        }
        if(indices!=nullptr && indices->exprList.size()==dimensions.size()){
            new BinaryInstruction(BinaryInstruction::ADD, offset_final, offset1, addr, bb);  //offset_final = offset1 + addr
            // printf("%s\n", getSymbolEntry()->toStr().c_str());
            //进入此分支表明已经寻址完成，可以由array type转为普通type
            if(dst->getType()->isFloatArray() || dst->getType()->isConstFloatArray()){
                dst->getEntry()->setType(new FloatType(4));
                // 如果不是全局变量 那么就设置 need_fp 标志位
                if(!dynamic_cast<IdentifierSymbolEntry*>(getSymbolEntry())->isGlobal() && dimensions[0] != -1){
                    dynamic_cast<FloatType*>(dst->getEntry()->getType())->setNeedFP(true);
                }
            }
            new LoadInstruction(dst, offset_final, bb);
        }
        else{
            //为区分数组指针和数组值，需要置位dst的type中的pointer
            if(dst->getType()->isIntArray()){
                dst->getEntry()->setType(new IntArrayType(*(dynamic_cast<IntArrayType*>(dst->getType()))));
                dynamic_cast<IntArrayType*>(dst->getType())->setPointer(true);
            }
            else if(dst->getType()->isConstIntArray()){
                dst->getEntry()->setType(new ConstIntArrayType(*(dynamic_cast<ConstIntArrayType*>(dst->getType()))));
                dynamic_cast<ConstIntArrayType*>(dst->getType())->setPointer(true);
            }
            else if(dst->getType()->isFloatArray()){
                dst->getEntry()->setType(new FloatArrayType(*(dynamic_cast<FloatArrayType*>(dst->getType()))));
                dynamic_cast<FloatArrayType*>(dst->getType())->setPointer(true);
            }
            else if(dst->getType()->isConstFloatArray()){
                dst->getEntry()->setType(new ConstFloatArrayType(*(dynamic_cast<ConstFloatArrayType*>(dst->getType()))));
                dynamic_cast<ConstFloatArrayType*>(dst->getType())->setPointer(true);
            }
            new BinaryInstruction(BinaryInstruction::ADD, dst, offset1, addr, bb); 
        }
    }
    else{
        new LoadInstruction(dst, addr, bb);
    }
}

void IfStmt::genCode()
{
    Function *func;
    BasicBlock *then_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    genBr = 1;
    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), end_bb);

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

<<<<<<< HEAD
    builder->setInsertBB(end_bb);    // then_block is done, point to end_block

=======
    builder->setInsertBB(end_bb);
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
}

void IfElseStmt::genCode()
{
    Function *func;
    BasicBlock *then_bb, *else_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    else_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    genBr = 1;
    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), else_bb);

    // 先处理then分支
    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    // 再处理else分支
    builder->setInsertBB(else_bb);
    elseStmt->genCode();
    else_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, else_bb);

    builder->setInsertBB(end_bb);

}

void CompoundStmt::genCode()
<<<<<<< HEAD
{
    stmt->genCode();
}

void SeqNode::genCode()
{
    for(auto stmt : stmtList){
        stmt->genCode();
    }
}

void DeclStmt::genCode()
{
    for(auto stmt : defList){
        stmt->genCode();
    }
}

void ReturnStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    if(retValue != nullptr) {
        retValue->genCode();
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
    //如果左值是array type，需要将其先转为普通type，以产生vstr指令
    Type* targetType = dynamic_cast<PointerType*>(addr->getType())->getValueType();
    if(targetType->isFloatArray()){
        targetType = TypeSystem::floatType;
    }
    Operand *src = typeCast(targetType, expr->getOperand());
    /***
     * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
     * If you want to implement array, you have to caculate the address first and then store the result into it.
     */
    if(lval->getType()->isArray()) {
        ExprStmtNode* indices = dynamic_cast<Id*>(lval)->getIndices();
        indices->genCode();
        Operand* offset = indices->exprList[0]->getOperand();
        std::vector<int> dimensions;
        if(lval->getType()->isIntArray()){
            dimensions = dynamic_cast<IntArrayType*>(lval->getType())->getDimensions();
        }
        else{
            dimensions = dynamic_cast<FloatArrayType*>(lval->getType())->getDimensions();
        }
        //如果是函数参数传入的数组指针，其最后一个维度为-1
        //此时需要生成新的load指令获取其地址
        if(dimensions[dimensions.size()-1]==-1){
            TemporarySymbolEntry* se = new TemporarySymbolEntry(lval->getType(), SymbolTable::getLabel());
            Operand* new_addr = new Operand(se);
            new LoadInstruction(new_addr, addr, bb);
            addr = new_addr;
        }
        for(unsigned int i = 1; i < indices->exprList.size(); i++) {
            Operand* dim_i = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, dimensions[i]));
            TemporarySymbolEntry* se1 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            Operand* offset1 = new Operand(se1);
            new BinaryInstruction(BinaryInstruction::MUL, offset1, offset, dim_i, bb);  //offset1 = offset * dimensions[i]
            TemporarySymbolEntry* se2 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            offset = new Operand(se2);
            new BinaryInstruction(BinaryInstruction::ADD, offset, offset1, indices->exprList[i]->getOperand(), bb); //offset = offset1 + indices[i]
        }
        TemporarySymbolEntry* se1 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        Operand* offset1 = new Operand(se1);
        Operand* align = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, 4));
        new BinaryInstruction(BinaryInstruction::MUL, offset1, offset, align, bb);  //offset1 = offset * 4
        TemporarySymbolEntry* se2 = new TemporarySymbolEntry(lval->getType(), SymbolTable::getLabel());
        Operand* offset_final = new Operand(se2);
        // 全局变量地址标签不能直接参与运算，需要先load
        if(dynamic_cast<IdentifierSymbolEntry*>(dynamic_cast<Id*>(lval)->getSymbolEntry())->isGlobal()){
            TemporarySymbolEntry* se3 = new TemporarySymbolEntry(lval->getType(), SymbolTable::getLabel());
            Operand* new_addr = new Operand(se3);
            new LoadInstruction(new_addr, addr, bb);
            addr = new_addr;
            se2->setGlobalArray();
        }
        new BinaryInstruction(BinaryInstruction::ADD, offset_final, offset1, addr, bb);  //offset_final = offset1 + addr
        new StoreInstruction(offset_final, src, bb);
    }
    else{
        new StoreInstruction(addr, src, bb);
    }
}

void WhileStmt::genCode()
{
    // 将当前的whileStmt压栈
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
    bodyStmt->genCode();
    stmt_bb = builder->getInsertBB();  // update block
    new UncondBrInstruction(cond_bb, stmt_bb); // stmt to cond_bb

    // 重新调整插入点到end_bb
    builder->setInsertBB(end_bb);
    whileStack.pop();

}
//函数参数可以看作局部变量声明，而且还带赋值
void FuncDefParamsNode::genCode()
{
=======
{
    stmt->genCode();
}

void SeqNode::genCode()
{
    for(auto stmt : stmtList){
        stmt->genCode();
    }
}

void DeclStmt::genCode()
{
    for(auto stmt : defList){
        stmt->genCode();
    }
}

void ReturnStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    if(retValue != nullptr) {
        retValue->genCode();
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
    //如果左值是array type，需要将其先转为普通type，以产生vstr指令
    Type* targetType = dynamic_cast<PointerType*>(addr->getType())->getValueType();
    if(targetType->isFloatArray()){
        targetType = TypeSystem::floatType;
    }
    Operand *src = typeCast(targetType, expr->getOperand());
    /***
     * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
     * If you want to implement array, you have to caculate the address first and then store the result into it.
     */
    if(lval->getType()->isArray()) {
        ExprStmtNode* indices = dynamic_cast<Id*>(lval)->getIndices();
        indices->genCode();
        Operand* offset = indices->exprList[0]->getOperand();
        std::vector<int> dimensions;
        if(lval->getType()->isIntArray()){
            dimensions = dynamic_cast<IntArrayType*>(lval->getType())->getDimensions();
        }
        else{
            dimensions = dynamic_cast<FloatArrayType*>(lval->getType())->getDimensions();
        }
        //如果是函数参数传入的数组指针，其最后一个维度为-1
        //此时需要生成新的load指令获取其地址
        if(dimensions[dimensions.size()-1]==-1){
            TemporarySymbolEntry* se = new TemporarySymbolEntry(lval->getType(), SymbolTable::getLabel());
            Operand* new_addr = new Operand(se);
            new LoadInstruction(new_addr, addr, bb);
            addr = new_addr;
        }
        for(unsigned int i = 1; i < indices->exprList.size(); i++) {
            Operand* dim_i = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, dimensions[i]));
            TemporarySymbolEntry* se1 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            Operand* offset1 = new Operand(se1);
            new BinaryInstruction(BinaryInstruction::MUL, offset1, offset, dim_i, bb);  //offset1 = offset * dimensions[i]
            TemporarySymbolEntry* se2 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            offset = new Operand(se2);
            new BinaryInstruction(BinaryInstruction::ADD, offset, offset1, indices->exprList[i]->getOperand(), bb); //offset = offset1 + indices[i]
        }
        TemporarySymbolEntry* se1 = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        Operand* offset1 = new Operand(se1);
        Operand* align = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, 4));
        new BinaryInstruction(BinaryInstruction::MUL, offset1, offset, align, bb);  //offset1 = offset * 4
        TemporarySymbolEntry* se2 = new TemporarySymbolEntry(lval->getType(), SymbolTable::getLabel());
        Operand* offset_final = new Operand(se2);
        // 全局变量地址标签不能直接参与运算，需要先load
        if(dynamic_cast<IdentifierSymbolEntry*>(dynamic_cast<Id*>(lval)->getSymbolEntry())->isGlobal()){
            TemporarySymbolEntry* se3 = new TemporarySymbolEntry(lval->getType(), SymbolTable::getLabel());
            Operand* new_addr = new Operand(se3);
            new LoadInstruction(new_addr, addr, bb);
            addr = new_addr;
            se2->setGlobalArray();
        }
        new BinaryInstruction(BinaryInstruction::ADD, offset_final, offset1, addr, bb);  //offset_final = offset1 + addr
        new StoreInstruction(offset_final, src, bb);
    }
    else{
        new StoreInstruction(addr, src, bb);
    }
}

void WhileStmt::genCode()
{
    // 将当前的whileStmt压栈
    whileStack.push(this);
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* stmt_bb, *cond_bb, *end_bb, *bb = builder->getInsertBB();
    stmt_bb = new BasicBlock(func);
    cond_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    this->condBlock = cond_bb;
    this->endBlock = end_bb;

    // 先从当前的bb跳转到cond_bb进行条件判断
    new UncondBrInstruction(cond_bb, bb);

    // 调整插入点到cond_bb，对条件判断部分生成中间代码
    builder->setInsertBB(cond_bb);
    genBr = 1;
    cond->genCode();
    backPatch(cond->trueList(), stmt_bb);
    backPatch(cond->falseList(), end_bb);

    // 调整插入点到stmt_bb，对循环体部分生成中间代码
    builder->setInsertBB(stmt_bb);
    bodyStmt->genCode();
    // 循环体完成之后，增加一句无条件跳转到cond_bb
    stmt_bb = builder->getInsertBB();
    new UncondBrInstruction(cond_bb, stmt_bb);

    // 重新调整插入点到end_bb
    builder->setInsertBB(end_bb);


    // 将当前的whileStmt出栈
    whileStack.pop();
}
//函数参数可以看作局部变量声明，而且还带赋值
void FuncDefParamsNode::genCode()
{
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
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

void ContinueStmt::genCode()
{
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

void BreakStmt::genCode()
{
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

void InitValNode::genCode()
{
    // 如果是个叶节点
    if(this->leafNode != nullptr) {
        this->leafNode->genCode();
        Operand* src = leafNode->getOperand();
        int offset = ArrayUtil::getCurrentOffset() * 4;
        Operand* offset_operand = new Operand(new ConstantSymbolEntry(TypeSystem::constIntType, offset));
        Operand* final_offset = new Operand(new TemporarySymbolEntry(ArrayUtil::getArrayType(), SymbolTable::getLabel()));
        Operand* addr = ArrayUtil::getArrayAddr();
        // 计算最终地址偏移
        new BinaryInstruction(BinaryInstruction::ADD, final_offset, offset_operand, addr, builder->getInsertBB());
        // 插入 store 指令
        new StoreInstruction(final_offset, src, builder->getInsertBB());
    }
    // 经过 typecheck 之后 数组初始化值已经被全部展平
    for(auto child : innerList) {
        child->genCode();
        ArrayUtil::incCurrentOffset();
    }
}

void DefNode::genCode()
{
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
        if(!se->getType()->isArray()){
            initVal->genCode();
            Operand *src = typeCast(se->getType(), dynamic_cast<ExprNode *>(initVal)->getOperand());
            new StoreInstruction(addr, src, bb);
        }
        else{
            ArrayUtil::init();
            ArrayUtil::setArrayType(se->getType());
            ArrayUtil::setArrayAddr(addr);
            initVal->genCode();
        }
        /***
         * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
         * If you want to implement array, you have to caculate the address first and then store the result into it.
         */
    }
}

void FuncCallParamsNode::genCode()
{
<<<<<<< HEAD

    for(auto expr : paramsList){
        expr->genCode();
    }

=======
    genBr--;
    for(auto expr : paramsList){
        expr->genCode();
    }
    genBr++;
>>>>>>> 952f69e01c68e82866d21d701853de8691377611
}

std::vector<Operand*> FuncCallParamsNode::getOperandList()
{
    std::vector<Operand*> result;
    for(auto param : paramsList){
        result.push_back(param->getOperand());
    }
    return result;
}

void FuncCallNode::genCode()
{
    //找到对应function的符号表项
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
        for(unsigned int i = 0; i < passParams.size(); i++) {
            realParams.push_back(typeCast(paramsType[i], passParams[i]));
        }
        new CallInstruction(dst, realParams, dynamic_cast<IdentifierSymbolEntry*>(funcId->getSymPtr()), bb);
    }
}

void ExprStmtNode::genCode()
{
    for(auto expr : exprList){
        expr->genCode();
    }
}

void EmptyStmt::genCode()
{
    // Todo 这个还需要做嘛
}

void Ast::typeCheck()
{
    if(root != nullptr)
        root->typeCheck(nullptr);
}

/**
 * 主要工作是检查函数是否有返回值以及返回值类型是否匹配
 */
void FunctionDef::typeCheck(Node** parentToChild)
{
    // 首先调用参数的typeCheck
    if(params != nullptr) {
        params->typeCheck((Node**)&(params));
    }
    // 获取函数的返回值类型
    returnType = ((FunctionType*)se->getType())->getRetType();
    // 判断函数是否返回
    funcReturned = false;
    stmt->typeCheck(nullptr);
    // 非void类型的函数需要有返回值
    if(!funcReturned && !returnType->isVoid()){
        fprintf(stderr, "expected a %s type to return, but no returned value found\n", returnType->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    // 如果void类型没写return需要补上
    if(returnType->isVoid()) {
        this->voidAddRet = new ReturnStmt(nullptr);
    }
    returnType = nullptr;
}

/**
 * 二元表达式类型检查工作主要为
 * 对两个孩子运算数类型的检查，并根据类型对父节点的类型进行调整
 */
void BinaryExpr::typeCheck(Node** parentToChild)
{
    expr1->typeCheck((Node**)&(this->expr1));
    expr2->typeCheck((Node**)&(this->expr2));
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
    // 在语法解析阶段就对父节点和孩子节点的类型进行了相应的转换设置
    // 在类型检查阶段就没有必要再对这部分进行检查了
    // 可以对mod取模运算检查一下是否有浮点参与
    if(op == MOD) {
        if(!(realTypeLeft->isAnyInt() && realTypeRight->isAnyInt())) {
            fprintf(stderr, "mod is not supported with float or bool operands!\n");
            exit(EXIT_FAILURE);
        }
    }
    // 推断父节点类型
    if(this->op >= AND && this->op <= NEQ) {
        this->setType(TypeSystem::boolType);
    }
    else {
        this->setType(TypeSystem::getMaxType(realTypeLeft, realTypeRight));
    }
    // if(realTypeLeft->isBool() && realTypeRight->isBool()){
    //     //别忘了两边一边是bool一边是int/float的情况
    // }
    // if(realTypeLeft->isAnyInt() && realTypeRight->isAnyInt()) {
    //     this->setType(TypeSystem::intType);
    // }
    // else{
    //     if(op==MOD){//浮点值参与取模运算
    //         fprintf(stderr, "mod is not supported with float or bool operands!\n");
    //         exit(EXIT_FAILURE);
    //     }
    //     this->setType(TypeSystem::floatType);
    // }
    // 如果父节点不需要这个值，直接返回
    if(parentToChild==nullptr){
        return;
    }
    //左右子树均为常数，计算常量值，替换节点
    if(realTypeLeft->isConst() && realTypeRight->isConst()){
        SymbolEntry *se;
        // 如果该节点结果的目标类型为bool
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
            case LESSEQ:
                val = leftValue <= rightValue;
            break;
            case GREAT:
                val = leftValue > rightValue;
            break;
            case GREATEQ:
                val = leftValue >= rightValue;
            break;
            case EQ:
                val = leftValue == rightValue;
            break;
            case NEQ:
                val = leftValue != rightValue;
            break;
            }
            se = new ConstantSymbolEntry(TypeSystem::constBoolType, val);
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
            // case AND:
            //     val = leftValue && rightValue;
            // break;
            // case OR:
            //     val = leftValue || rightValue;
            // break;
            // case LESS:
            //     val = leftValue < rightValue;
            // break;
            // case LESSEQ:
            //     val = leftValue <= rightValue;
            // break;
            // case GREAT:
            //     val = leftValue > rightValue;
            // break;
            // case GREATEQ:
            //     val = leftValue >= rightValue;
            // break;
            // case EQ:
            //     val = leftValue == rightValue;
            // break;
            // case NEQ:
            //     val = leftValue != rightValue;
            // break;
            }
            se = new ConstantSymbolEntry(TypeSystem::constIntType, val);
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
            // case MOD:
            //     fprintf(stderr, "mod is not supported with float or bool operands!");
            //     exit(EXIT_FAILURE);
            // break;
            // case LESS:
            //     val = leftValue < rightValue;
            // break;
            // case LESSEQ:
            //     val = leftValue <= rightValue;
            // break;
            // case GREAT:
            //     val = leftValue > rightValue;
            // break;
            // case GREATEQ:
            //     val = leftValue >= rightValue;
            // break;
            // case EQ:
            //     val = leftValue == rightValue;
            // break;
            // case NEQ:
            //     val = leftValue != rightValue;
            // break;
            }
            se = new ConstantSymbolEntry(TypeSystem::constFloatType, val);
        }
        Constant* newNode = new Constant(se);
        *parentToChild = newNode;
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

void Constant::typeCheck(Node** parentToChild){}

void Id::typeCheck(Node** parentToChild)
{
    // 如果是一个普通变量就什么也不做
    // 如果是一个普通常量
    if(!isArray() && symbolEntry->getType()->isConst() && parentToChild != nullptr) {
        ConstantSymbolEntry* newConst = new ConstantSymbolEntry(symbolEntry->getType(), dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->value);
        Constant* newNode = new Constant(newConst);
        (*parentToChild) = newNode;
    }
    // 如果是数组 要看看维度信息有没有初始化
    // 由于在语法解析阶段已经判断了标识符先定义再使用
    // 所以如果维度信息还未初始化则说明当前是数组定义阶段
    if(isArray() && indices!=nullptr){
        indices->typeCheck(nullptr);
        // 检查indices下的exprList(私有域)中的每个exprNode的类型，若不为自然数则报错
        // if(((IdentifierSymbolEntry*)getSymPtr())->arrayDimension.empty()){
        if((getType()->isIntArray() && dynamic_cast<IntArrayType*>(getType())->getDimensions().empty()) ||
            (getType()->isConstIntArray() && dynamic_cast<ConstIntArrayType*>(getType())->getDimensions().empty()) ||
            (getType()->isFloatArray() && dynamic_cast<FloatArrayType*>(getType())->getDimensions().empty()) ||
            (getType()->isConstFloatArray() && dynamic_cast<ConstFloatArrayType*>(getType())->getDimensions().empty())){
            // (getType()->isIntArray() && dynamic_cast<IntArrayType*>(getType())->getDimensions().back()==-1)){
            indices->initDimInSymTable((IdentifierSymbolEntry*)getSymPtr());
        }
        // 读取常量数组 这个不打算做了
        else if(getType()->isConst()){
            //TODO: 将常量数组+全常量下标的数组元素访问替换为字面值常量节点Constant
            //STEP：1.遍历indices下的exprList(私有域)，查看是否有非常量节点。若有，直接返回
            //STEP: 2.若全部为常量下标，替换
        }
    }
}

void IfStmt::typeCheck(Node** parentToChild)
{
    cond->typeCheck((Node**)&(this->cond));
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
        thenStmt->typeCheck((Node**)&(this->thenStmt));
    }
    else {
        thenStmt = new EmptyStmt();
    }
}

void IfElseStmt::typeCheck(Node** parentToChild)
{
    cond->typeCheck((Node**)&(this->cond));
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
        thenStmt->typeCheck((Node**)&(this->thenStmt));
    }
    else {
        thenStmt = new EmptyStmt();
    }
    if(elseStmt!=nullptr){
        elseStmt->typeCheck((Node**)&(this->elseStmt));
    }
    else {
        elseStmt = new EmptyStmt();
    }
}

void CompoundStmt::typeCheck(Node** parentToChild)
{
    if(stmt!=nullptr){
        stmt->typeCheck(nullptr);
    }
    else {
        stmt = new EmptyStmt();
    }
}

void SeqNode::typeCheck(Node** parentToChild)
{
    for(int i = 0;i<(int)stmtList.size();++i){
        stmtList[i]->typeCheck((Node**)&(stmtList[i]));
    }
}

void DeclStmt::typeCheck(Node** parentToChild)
{
    for(int i = 0;i<(int)defList.size();++i){
        defList[i]->typeCheck(nullptr);
    }
}

void ReturnStmt::typeCheck(Node** parentToChild)
{
    //fprintf(stderr, "%s %s\n", returnType->toStr().c_str(), retValue->getType()->toStr().c_str());
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
        retValue->typeCheck((Node**)&(retValue));
    }
    this->retType = returnType;
    funcReturned = true;
}

void AssignStmt::typeCheck(Node** parentToChild)
{
    lval->typeCheck(nullptr);
    expr->typeCheck((Node**)&(this->expr));
    if(lval->getType()->isConst()) {
        fprintf(stderr, "Unable to assign value to const variable %s\n", lval->getSymPtr()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    if(expr->getType()->isFunc() && ((FunctionType*)(expr->getType()))->getRetType()->isVoid()){//返回值为void的函数做运算数
        fprintf(stderr, "expected a return value, but functionType %s returns nothing\n", expr->getType()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
}

void FuncDefParamsNode::typeCheck(Node** parentToChild){
    for(auto param : paramsList) {
        // 由于不需要进行节点替换 直接传nullptr
        param->typeCheck(nullptr);
    }
}

void ContinueStmt::typeCheck(Node** parentToChild)
{
    if(!inIteration){
        fprintf(stderr, "continue statement outside iterations\n");
        exit(EXIT_FAILURE);
    }
}

void BreakStmt::typeCheck(Node** parentToChild)
{
    if(!inIteration){
        fprintf(stderr, "break statement outside iterations\n");
        exit(EXIT_FAILURE);
    }
}

void WhileStmt::typeCheck(Node** parentToChild)
{
    cond->typeCheck((Node**)&(this->cond));
    // 如果cond中的se的类型不为 bool，或者se是一个常量bool
    // 则说明此时的情况为 if(a) 或者 if(1) 或者 if(a+1)
    // 增加一个和1的EQ判断
    if(!cond->getSymPtr()->getType()->isBool() || cond->getSymPtr()->isConstant()) {
        Constant* zeroNode = new Constant(new ConstantSymbolEntry(TypeSystem::constIntType, 0));
        TemporarySymbolEntry* tmpSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        BinaryExpr* newCond = new BinaryExpr(tmpSe, BinaryExpr::NEQ, zeroNode, cond);
        cond = newCond;
    }
    if(bodyStmt!=nullptr) {
        inIteration++;
        bodyStmt->typeCheck((Node**)&(this->bodyStmt));
        inIteration--;
    }
    else {
        bodyStmt = new EmptyStmt();
    }
}

void InitValNode::typeCheck(Node** parentToChild)
{
    ArrayUtil::incCurrentDim();
    bool padding = true;
    if(this->leafNode != nullptr) {
        this->leafNode->typeCheck((Node**)&(this->leafNode));
        ArrayUtil::insertInitVal(this->leafNode);
        padding = false;

    }
    // 首先对 innerList 进行递归
    int size = 0;
    for(auto & child : innerList){
        child->typeCheck((Node**)&child);
        size++;
    }
//    int padding = currentDimSize - (int)innerList.size();
    // 然后对当前维度进行填充
    if(padding) {
        ArrayUtil::paddingInitVal(size);
    }
    ArrayUtil::decCurrentDim();
}

// TODO: 这段代码逻辑太乱了，需要重构
void DefNode::typeCheck(Node** parentToChild)
{
    id->typeCheck(nullptr);
    // 不赋初值，直接返回
    if(initVal==nullptr){
        return;
    }

    if(id->getType()->isArray()) {
        ArrayUtil::init();
        ArrayUtil::setArrayType(id->getType());
        initVal->typeCheck((Node**)&(initVal));
        this->initVal = new InitValNode(dynamic_cast<InitValNode*>(this->initVal)->isConst());
        std::vector<ExprNode*> initList = ArrayUtil::getInitVals();
        for(auto & child : initList){
            InitValNode* newNode = new InitValNode(dynamic_cast<InitValNode*>(this->initVal)->isConst());
            newNode->setLeafNode(child);
            dynamic_cast<InitValNode*>(this->initVal)->addNext(newNode);
        }
    }
    else {
        initVal->typeCheck((Node**)&(initVal));
    }


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
            if(!((InitValNode*)initVal)->isConst()) {
                fprintf(stderr, "attempt to initialize variable value to const\n");
                exit(EXIT_FAILURE);
            }
        }
        // 接下来就是常量计算的工作了
        // 数组初始化值 暂时不打算做了
        if(id->getType()->isArray()){
            IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)id->getSymPtr();
            for(auto val : dynamic_cast<InitValNode*>(initVal)->getInnerList()) {
                ExprNode* leafNode = val->getLeafNode();
                double value= ((ConstantSymbolEntry*)((ExprNode*)leafNode)->getSymPtr())->getValue();
                se->arrayValues.push_back(value);
            }
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
//            if(!((ExprNode*)initVal)->getType()->isConst()) {
//                fprintf(stderr, "not allow to initialize global variable with not const value\n");
//                exit(EXIT_FAILURE);
//            }
            IdentifierSymbolEntry* se = (IdentifierSymbolEntry*)id->getSymPtr();
            if(!se->getType()->isArray()) {
                se->value = ((ConstantSymbolEntry*)((ExprNode*)initVal)->getSymPtr())->getValue();
            }
            else {
                if(se->arrayValues.empty()) {
                    for(auto val : dynamic_cast<InitValNode*>(initVal)->getInnerList()) {
                        ExprNode* leafNode = val->getLeafNode();
                        double value= ((ConstantSymbolEntry*)((ExprNode*)leafNode)->getSymPtr())->getValue();
                        se->arrayValues.push_back(value);
                    }
                }
            }
        }
    }
}

void FuncCallParamsNode::typeCheck(Node** parentToChild)
{
    for(int i = 0; i < (int)paramsList.size(); i++) {
        paramsList[i]->typeCheck((Node**)&(paramsList[i]));
    }
}

void FuncCallNode::typeCheck(Node** parentToChild)
{
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
    this->params->typeCheck(nullptr); 
    std::vector<ExprNode*> funcCallParams = this->params->getParamsList();
    // 如果数量不一致直接报错
    if(funcCallParams.size() != funcParamsType.size()) {
        fprintf(stderr, "function %s call params number is not consistent\n",this->funcId->getSymPtr()->toStr().c_str());
        exit(EXIT_FAILURE);
    }
    // 然后进行类型匹配
    // 依次匹配类型
    for(unsigned int i = 0; i < funcParamsType.size(); i++){
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
        // if((!needType->isArray() && giveType->isArray())
        //  ||(needType->isArray() && !giveType->isArray())){
        //     fprintf(stderr, "function %s call params type is not consistent\n",this->funcId->getSymPtr()->toStr().c_str());
        //     exit(EXIT_FAILURE);
        // }
        //TODO: 检查数组维度是否匹配
        if(needType->isArray() && giveType->isArray()){

        }
    }
}

void ExprStmtNode::typeCheck(Node** parentToChild)
{
    for(int i = 0;i<(int)exprList.size();++i){
        exprList[i]->typeCheck((Node**)&(exprList[i]));
    }
}

void EmptyStmt::typeCheck(Node** parentToChild){}

void OneOpExpr::typeCheck(Node** parentToChild)
{
    expr->typeCheck((Node**)&(this->expr));
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
    //如果父节点不需要这个值，直接返回
    if(parentToChild==nullptr){
        return;
    }
    //孩子节点为常数，计算常量值，替换节点
    if(realType->isConst()){
        SymbolEntry *se;
        double val = 0;
        int initValue = expr->getSymPtr()->isConstant() ? 
            ((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue() :
            (((IdentifierSymbolEntry*)(expr->getSymPtr()))->value);
        switch (op) 
        {
        case SUB:
            val = -initValue;
        break;
        case NOT:
            val = !initValue;
        break;
        }
        if(this->getType()->isInt()){
            se = new ConstantSymbolEntry(TypeSystem::constIntType, val);
        }
        else{//float or bool
            se = new ConstantSymbolEntry(TypeSystem::constFloatType, val);
        }
        Constant* newNode = new Constant(se);
        *parentToChild = newNode;
        //delete this;
    }
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
        case MUL:
            op_str = "mul";
            break;
        case DIV:
            op_str = "div";
            break;
        case MOD:
            op_str = "mod";
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
        case LESSEQ:
            op_str = "lesseq";
            break;
        case GREAT:
            op_str = "great";
            break;
        case GREATEQ:
            op_str = "greateq";
            break;
        case EQ:
            op_str = "eq";
            break;
        case NEQ:
            op_str = "neq";
            break;
    }
    fprintf(yyout, "%*cBinaryExpr\top: %s\ttype: %s\n", level, ' ', op_str.c_str(), symbolEntry->getType()->toStr().c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

void OneOpExpr::output(int level) {
    std::string op_str;
    switch (op) {
        case NOT:
            op_str = "not";
            break;
        case SUB:
            op_str = "minus";
            break;
    }
    fprintf(yyout, "%*cOneOpExpr\top: %s\ttype: %s\n", level, ' ', op_str.c_str(), symbolEntry->getType()->toStr().c_str());
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
        fprintf(yyout, "%*cArrayIndices\n", level+4, ' ');
        indices->output(level+8);
    }
}

void EmptyStmt::output(int level)
{
    fprintf(yyout, "%*cEmptyStmt\n", level, ' ');
}

void ExprStmtNode::addNext(ExprNode* next)
{
    exprList.push_back(next);
}

void ExprStmtNode::addFirst(ExprNode* first)
{
    exprList.insert(exprList.begin(), first);
}

void ExprStmtNode::output(int level)
{
    fprintf(yyout, "%*cExprStmtNode\n", level, ' ');
    for(auto expr : exprList)
    {
        expr->output(level+4);
    }
}

void ExprStmtNode::initDimInSymTable(IdentifierSymbolEntry* se)
{
    for(auto expr :exprList){
        // 既不是字面值常量，也不是常量表达式
        if(!(expr->getSymPtr()->isConstant() || expr->getType()->isConst())){
            fprintf(stderr, "array dimensions must be constant! %d %d\n", expr->getSymPtr()->isConstant(), expr->getType()->isConst());
            fprintf(stderr, "%d %d\n", (int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue(), (int)((IdentifierSymbolEntry*)(expr->getSymPtr()))->value);
            exit(EXIT_FAILURE);
        }
        // 字面值常量，值存在ConstantSymbolEntry中
        if(expr->getSymPtr()->isConstant()){
            // se->arrayDimension.push_back((int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue());
            if(se->getType()->isIntArray()){
                dynamic_cast<IntArrayType*>(se->getType())->pushBackDimension((int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue());
            }
            else if(se->getType()->isConstIntArray()) {
                dynamic_cast<ConstIntArrayType*>(se->getType())->pushBackDimension((int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue());
            }
            else if(se->getType()->isFloatArray()){
                dynamic_cast<FloatArrayType*>(se->getType())->pushBackDimension((int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue());
            }
            else {
                dynamic_cast<ConstFloatArrayType*>(se->getType())->pushBackDimension((int)((ConstantSymbolEntry*)(expr->getSymPtr()))->getValue());
            }
        }
        // 常量表达式，值存在IdentifierSymbolEntry中
        else if(expr->getType()->isConst()){
            // se->arrayDimension.push_back((int)((IdentifierSymbolEntry*)(expr->getSymPtr()))->value);
            if(se->getType()->isIntArray()){
                dynamic_cast<IntArrayType*>(se->getType())->pushBackDimension((int)((IdentifierSymbolEntry*)(expr->getSymPtr()))->value);
            }
            else{
                dynamic_cast<FloatArrayType*>(se->getType())->pushBackDimension((int)((IdentifierSymbolEntry*)(expr->getSymPtr()))->value);
            }
        }
    }
}

void FuncCallNode::output(int level)
{
    std::string name, type;
    int scope;
    SymbolEntry* funcEntry = funcId->getSymbolEntry();
    name = funcEntry->toStr();
    type = funcEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(funcEntry)->getScope();
    fprintf(yyout, "%*cFuncCallNode\tfuncName: %s\t funcType: %s\tscope: %d\n", 
            level, ' ', name.c_str(), type.c_str(), scope);
    if(params!=nullptr){
        params->output(level+4);
    }
    else{
        fprintf(yyout, "%*cFuncCallParamsNode NULL\n", level+4, ' ');
    }
}

void FuncCallParamsNode::addNext(ExprNode* next)
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

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    if(stmt == nullptr){
        fprintf(yyout, "%*cNull Stmt\n", level+4, ' ');
    }
    else{
        stmt->output(level + 4);
    }
}

void SeqNode::addNext(StmtNode* next)
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

void InitValNode::addNext(InitValNode* next)
{
    innerList.push_back(next);
}

void InitValNode::output(int level)
{
    std::string constStr = isconst ? "true" : "false";
    fprintf(yyout, "%*cInitValNode\tisConst:%s\n", level, ' ', constStr.c_str());
    for(auto child : innerList)
    {
        child->output(level+4);
    }
    if(leafNode!=nullptr){
        leafNode->output(level+4);
    }
}

void InitValNode::setLeafNode(ExprNode* leaf)
{
    leafNode = leaf;
}

bool InitValNode::isLeaf()
{
    return innerList.empty();
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

void WhileStmt::output(int level)
{
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level+4);
    bodyStmt->output(level+4);
}

void BreakStmt::output(int level)
{
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}

void ContinueStmt::output(int level)
{
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    if(retValue!=nullptr) retValue->output(level + 4);
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

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

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    if(params!=nullptr){
        params->output(level+4);
    }
    else{
        fprintf(yyout, "%*cFuncDefParamsNode NULL\n", level+4, ' ');
    }
    stmt->output(level + 4);
    if(this->voidAddRet != nullptr) {
        voidAddRet->output(level + 4);
    }
}