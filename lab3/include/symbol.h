#pragma once
#include <string>
class SymbolTableEntry{
    public:
    std::string name;
    SymbolTableEntry* prev;
    SymbolTableEntry* next;
    int level;

};

typedef SymbolTableEntry STE;

class SymbolTable{
public:
    STE* ste_head ;
    STE* ste_tail ;
    SymbolTable* prev;
    SymbolTable* next;
    int level;
    int symNum = 0; 
    SymbolTable(int nowLevel);
    ~SymbolTable();

};

SymbolTable::SymbolTable(int nowLevel){
    ste_head = new STE;
    ste_tail = new STE;
    prev = next = NULL;
    level = nowLevel;
    symNum = 0;
    ste_head->next = ste_tail;
    ste_head->prev = NULL;
    ste_tail->next = NULL;
    ste_tail->prev = ste_head;
}

SymbolTable::~SymbolTable(){
    delete ste_head;
    delete ste_tail;
}
