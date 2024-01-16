#include "IRBlockMerge.h"
#include <unordered_set>
#include <vector>


using namespace std;

void BlockMerge::execute() {
    for (auto func = unit->begin(); func != unit->end(); func++){
        findBLocks(*func);
    }
}

// 查找可以合并的块
void BlockMerge::findBLocks(Function *func) {
    for (auto bb : func->getBlockList()) {
        

        BasicBlock *block = bb;
        int succ_num = block->getNumOfSucc();
        if(succ_num>1){
            continue;
        }

        mergeList.clear();
        

        while (true) {
            bool can_merge = 0;
            // 获取block的后继块succ;
            BasicBlock* succ;

            if (can_merge) {
                mergeList.push_back(succ);
                block = succ;
            } else {
                break;
            }
        }
        // TODO: 3. 合并基本块
        if (mergeList.size() > 0)
            merge(func, bb);
    }
}

// 如果debug时需要查看块内指令信息，可借助该函数
void BlockMerge::printInsts(BasicBlock *start) {
    auto head = start->end();
    for (auto instr = head->getNext(); instr != head;
         instr = instr->getNext()) {
        // 此处可以打印自己想要查看的指令信息
    }
}

void BlockMerge::merge(Function *func, BasicBlock *start) {
    
    // TODO: 1. 处理所有待合并块之间的联系，包括删除冗余的可合并块之间的跳转等；

    for (auto bb : mergeList) {
        std::vector<Instruction *> mergeInst = {};
        auto head = bb->end();
        for (auto instr = head->getNext(); instr != head;
             instr = instr->getNext()) {

            // 此处需要补充对指令的判断与处理
            mergeInst.push_back(instr);

        }
        func->remove(bb);
    }
}


// 如果实现了phi指令，需要对其进行维护
void BlockMerge::replacePhiBB(BasicBlock *succ, BasicBlock *start) {
    auto head = succ->end();
    for (auto instr = head->getNext(); instr != head;
         instr = instr->getNext()) {

    }
}