#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include "Operand.h"
#include <vector>
#include <stack>

class SymbolEntry;
class Unit;
class Function;
class BasicBlock;
class Instruction;
class IRBuilder;
class Type;

class Node
{
private:
    static int counter;
    int seq;
protected:
    //std::vector<BasicBlock**> true_list;
    //std::vector<BasicBlock**> false_list;
    std::vector<Instruction*> true_list;
    std::vector<Instruction*> false_list;
    static IRBuilder *builder;
    //void backPatch(std::vector<BasicBlock**> &list, BasicBlock*target);
    void backPatch(std::vector<Instruction*> &list, BasicBlock*bb);
    //std::vector<BasicBlock**> merge(std::vector<BasicBlock**> &list1, std::vector<BasicBlock**> &list2);
    std::vector<Instruction*> merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2);
    Operand* typeCast(Type* targetType, Operand* operand);
public:
    Node();
    int getSeq() const {return seq;};
    static void setIRBuilder(IRBuilder*ib) {builder = ib;};
    virtual void output(int level) = 0;
    virtual void typeCheck(Node** parentToChild) = 0;
    virtual void genCode() = 0;
    // std::vector<BasicBlock**>& trueList() {return true_list;}
    // std::vector<BasicBlock**>& falseList() {return false_list;}
    std::vector<Instruction*>& trueList() {return true_list;}
    std::vector<Instruction*>& falseList() {return false_list;}
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
    Operand *dst;   // The result of the subtree is stored into dst.
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){dst = new Operand(symbolEntry); };
    Operand* getOperand() {return dst;};
    SymbolEntry* getSymPtr() {return symbolEntry;};
    Type* getType();
    void setType(Type* type);
};

class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
     enum {ADD, SUB, AND, OR, LESS,MUL,DIV,MOD,LE,GREATER,GE,EQ,NEQ};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};
class UnaryOpExpr : public ExprNode{
private:
    int op;
    ExprNode *expr;
public:
    enum {ADD,SUB,NOT};
    UnaryOpExpr(SymbolEntry *se,int op,ExprNode *expr) : ExprNode(se),op(op),expr(expr){};
    void output(int level);
};
class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){dst = new Operand(se);};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};

class StmtNode : public Node
{};

class ArrayindiceNode : public StmtNode
{
private:
    std::vector<ExprNode*> arrindexList;
public:
    ArrayindiceNode(){};
    void append(ExprNode* next);
    void output(int level);

    void typeCheck(Node** parentToChild);
    void genCode();
    void initDimInSymTable(IdentifierSymbolEntry* se);
};

class Id : public ExprNode
{
private:
    ArrayindiceNode* indices;
public:
    Id(SymbolEntry *se) : ExprNode(se){SymbolEntry *temp = new TemporarySymbolEntry(se->getType(), SymbolTable::getLabel()); dst = new Operand(temp);};
     SymbolEntry* getSymbolEntry() {return symbolEntry;}
    bool isArray();     //必须配合indices!=nullptr使用（a[]的情况）
    void addIndices(ArrayindiceNode* idx) {indices = idx;}
    void output(int level);
    std::string getName();
    Type* getType();
    void typeCheck(Node** parentToChild);
    void genCode();
};



class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt) : stmt(stmt) {};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};
class ArrayinitNode : public StmtNode
{
private:
    bool isConst;
    ExprNode* leafNode;//用于output
    std::vector<ArrayinitNode*> innerList;//容器为空则是叶节点
public:
    ArrayinitNode(bool isConst) : 
        isConst(isConst), leafNode(nullptr){};
    void setLeafNode(ExprNode* leaf){leafNode = leaf;};
    void append(ArrayinitNode* next){innerList.push_back(next);};
    bool isLeaf(){return innerList.empty();};
    void output(int level);

    void typeCheck(Node** parentToChild);
    void genCode();
};
class DefNode : public StmtNode
{
private:
    bool isConst;
    bool isArray;
    Id* id;
    Node* initVal;//对于非数组，是ExprNode；对于数组，是InitValueNode
public:
    DefNode(Id* id, Node* initVal, bool isConst, bool isArray) : 
        isConst(isConst), isArray(isArray), id(id), initVal(initVal){};
    Id* getId() {return id;}
    void output(int level);
    
    void typeCheck(Node** parentToChild);
    void genCode();
};

class DeclStmt : public StmtNode
{
private:
    bool isConst;
    std::vector<DefNode*> defList;
public:
    DeclStmt(bool isConst) : isConst(isConst){};
    void addNext(DefNode* next);
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};

class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};
class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *Stmt;
public:
    WhileStmt(ExprNode *cond, StmtNode *Stmt) : cond(cond), Stmt(Stmt){};
    void output(int level);
};
class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue) : retValue(retValue) {};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};
class ContinueStmt : public StmtNode //continue
{
private:
public:
    void output(int level);
    
};
class BreakStmt: public StmtNode
{
public:
    void output(int level);
};
class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};
class FuncDefParamsNode : public StmtNode
{
private:
    std::vector<Id*> paramsList;
public:
    FuncDefParamsNode() {};
    void addNext(Id* next);
    std::vector<Type*> getParamsType();
    void output(int level);

    void typeCheck(Node** parentToChild);
    void genCode();
};


class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    FuncDefParamsNode *params;
    StmtNode *stmt;
    StmtNode* voidAddRet = nullptr;
public:
    FunctionDef(SymbolEntry *se, FuncDefParamsNode *params, StmtNode *stmt) : se(se), params(params), stmt(stmt){};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();
};
class EmptyStmtNode : public StmtNode
{
public:
    EmptyStmtNode(){};
    void output(int level);
    void typeCheck(Node** parentToChild);
    void genCode();

};


// 函数调用
class FuncCallParamsNode : public StmtNode
{
private:
    std::vector<ExprNode*> paramsList; //参数列表
public:
    FuncCallParamsNode(){};
    void append(ExprNode* next);
    void output(int level);
};

class FuncCallNode : public ExprNode  
{
private:
    Id* funcId;  //函数名
    FuncCallParamsNode* params; //参数
public:
    FuncCallNode(SymbolEntry *se, Id* id, FuncCallParamsNode* params) : ExprNode(se), funcId(id), params(params){};
    void output(int level);
};
class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
    void typeCheck(Node** parentToChild);
    void genCode(Unit *unit);
};
class ExprStmtNode : public StmtNode
{
private:
    std::vector<ExprNode*> exprList;
public:
    ExprStmtNode(){};
    void append(ExprNode* next);
    void output(int level);
};
#endif
