#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(4);
FloatType TypeSystem::commonFloat = FloatType();
ConstIntType TypeSystem::commonConstInt = ConstIntType();
ConstFloatType TypeSystem::commonConstFloat = ConstFloatType();
BoolType TypeSystem::commonBool = BoolType();
VoidType TypeSystem::commonVoid = VoidType();

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::floatType = &commonFloat;
Type* TypeSystem::constIntType = &commonConstInt;
Type* TypeSystem::constFloatType = &commonConstFloat;
Type* TypeSystem::boolType = &commonBool;
Type* TypeSystem::voidType = &commonVoid;


Type* TypeSystem::UpperType(Type* type1,Type* type2){   // float > int > bool
    if(type1->isFloat() || type2->isFloat()) return floatType;
    else if(type1->isInt() || type2->isInt()) return intType;
    else return boolType;
}

bool TypeSystem::needCast(Type* src, Type* target) {
    if(src->isInt() && target->isInt()) {
        return false;
    }
    if(src->isFloat() && target->isFloat()) {
        return false;
    }
    if(src->isBool() && target->isBool()) {
        return false;
    }
    return true;
}

std::string IntType::toStr()
{
    return "int";
}

std::string FloatType::toStr()
{
    return "float";
}

std::string ConstIntType::toStr()
{
    return "const int";
}

std::string ConstFloatType::toStr()
{
    return "const float";
}

std::string BoolType::toStr()
{
    return "bool";
}

std::string VoidType::toStr()
{
    return "void";
}

std::string PointerType::toStr(){
    return "Pointer";
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

void IntArrayType::pushBackDimension(int dim)
{
    dimensions.push_back(dim);
}

std::vector<int> IntArrayType::getDimensions()
{
    return dimensions;
}

std::string IntArrayType::toStr()
{
    return "int array";
}

void FloatArrayType::pushBackDimension(int dim)
{
    dimensions.push_back(dim);
}

std::vector<int> FloatArrayType::getDimensions()
{
    return dimensions;
}

std::string FloatArrayType::toStr()
{
    return "float array";
}
void ConstIntArrayType::pushBackDimension(int dim)
{
    dimensions.push_back(dim);
}

std::vector<int> ConstIntArrayType::getDimensions()
{
    return dimensions;
}

std::string ConstIntArrayType::toStr()
{
    return "const int array";
}

void ConstFloatArrayType::pushBackDimension(int dim)
{
    dimensions.push_back(dim);
}

std::vector<int> ConstFloatArrayType::getDimensions()
{
    return dimensions;
}

std::string ConstFloatArrayType::toStr()
{
    return "const float array";
}

