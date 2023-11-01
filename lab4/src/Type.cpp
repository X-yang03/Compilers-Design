#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(4);
VoidType TypeSystem::commonVoid = VoidType();

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;

std::string IntType::toStr()
{
    return "int";
}

std::string VoidType::toStr()
{
    return "void";
}

void FunctionType::setparamsType(std::vector<Type*> in)
{
    paramsType = in;
}

std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "(";
    for(int i = 0;i < (int)paramsType.size();i++){
        if(i!=0) buffer << ", ";
        buffer << paramsType[i]->toStr();
    }
    buffer << ")";
    return buffer.str();
}