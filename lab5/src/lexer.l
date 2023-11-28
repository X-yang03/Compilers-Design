%option noyywrap
%option nounput
%option noinput
%option yylineno
%top{
    #include <stdarg.h>
    #include "common.h"
    #include "parser.h"
}
%{

    
    int columnNo = 0;

    //bool preToken = 0; //0表示加减号 ，1表示为正负号

    extern dump_type_t dump_type;

    //  dump_tokens用于输出token的信息
    inline void dump_tokens(const char* format, ...){  //变长参数
        va_list args;                                   //va_list表示可变参数列表类型，实际上是一个char*
        va_start(args, format);                         //初始化args，指向第一个可变参数，即format后的第一个参数
        if (dump_type == TOKENS)
            vfprintf(yyout, format, args);              //yyout中输出format格式化的字符串
        va_end(args);
        columnNo += yyleng;      //columnNo 加上yytext的长度yyleng

    }

    /* Your code here, if desired (lab3). */
%}
/* definitions section */

COMMENTBEGIN    "/*"
COMMENTEND      "*/"
COMMENTELEMENT  .
SINGLECOMMENT   "//"[^\n]*   
DECIMIAL        ([1-9][0-9]*|0)
OCTAL           (0[0-7]+)
HEXDECIMAL      (0[xX][0-9a-fA-F]+)
FLOAT_NUMBER    ((([0-9]*[.][0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+))[fFlL]?)
HEX_FLOAT       (0[xX](([0-9A-Fa-f]*[.][0-9A-Fa-f]*[pP][+-]?[0-9]+)|([0-9A-Fa-f]+[pP][+-]?[0-9]+))[fFlL]?)
ID              [[:alpha:]_][[:alpha:][:digit:]_]*
EOL             (\r\n|\n|\r)
WHITE           [\t ]
%x COMMENT
/*  Your code here (lab3). */

%%
    /* rules section */
{SINGLECOMMENT} {
    columnNo = 0;
    dump_tokens("SINGLECOMMENT\t%d\n",yylineno);
}

{COMMENTBEGIN}  {
    BEGIN COMMENT;
    columnNo+=2;
}

<COMMENT>{COMMENTELEMENT}    { columnNo++;}

<COMMENT>{EOL}  {columnNo = 0;}

<COMMENT>{COMMENTEND}    {
    BEGIN INITIAL;
    columnNo+=2;
}


"int" {     //输出 TYPE_INT  int    行号    列号
    dump_tokens("TYPE_INT\t\t%s\t%d\t%d\n", yytext,yylineno,columnNo); //yytext是识别到的字符串
    return TYPE_INT;
}

"float" {
    dump_tokens("TYPE_FLOAT\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    return TYPE_FLOAT;
}

"void" {
    dump_tokens("TYPE_VOID\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    return TYPE_VOID;
}

"if" {
    dump_tokens("IF\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    return IF;
}

"else" {
    dump_tokens("ELSE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    return ELSE;
}

"return" {
    dump_tokens("RETURN\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    //here add
    return RETURN;
}
"!=" {
    dump_tokens("NEQ\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return NEQ;
}
"==" {
    dump_tokens("EQ\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return EQ;
}

"=" {
    dump_tokens("ASSIGN\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return ASSIGN;
}

"<="    {
    dump_tokens("LESSEQ\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return LESSEQ;
}

"<" {
    dump_tokens("LESS\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return LESS;
}

">="    {
    dump_tokens("GREATEQ\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return GREATEQ;
}

">" {
    dump_tokens("GREATE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return GREAT;
}

"+" {
  
        dump_tokens("ADD\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
        return ADD;
    
}

"-" {
        dump_tokens("SUB\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
        return SUB;
}

"*" {
    dump_tokens("MUL\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    //here add

    return MUL;
}
"/" {
    dump_tokens("DIV\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    //here add

    return DIV;
}
"%" {
    dump_tokens("MOD\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    return MOD;
}
";" {
    dump_tokens("SEMICOLON\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return SEMICOLON;
}

"(" {
    dump_tokens("LPAREN\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return LPAREN;
}

")" {
    dump_tokens("RPAREN\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return RPAREN;
}

"{" {
    dump_tokens("LBRACE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return LBRACE;
}

"}" {
    dump_tokens("RBRACE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return RBRACE;
}
"," {
    dump_tokens("COMMA\t%s\t%d\t%d\n", yytext,yylineno,columnNo);

    return COMMA;
}
"while" {
    dump_tokens("WHILE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    return WHILE;
}

"continue"  {
    dump_tokens("CONTINUE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    return CONTINUE;
}

"break" {
    dump_tokens("BREAK\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    return BREAK;
}

"const" {
    dump_tokens("CONST\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
    return CONST;
}

"&&"    {
    dump_tokens("AND\t%s\t%d\t%d\n",yytext,yylineno,columnNo);

    return AND;
}

"||"    {
    dump_tokens("OR\t%s\t%d\t%d\n",yytext,yylineno,columnNo);

    return OR;
}

"!" {
    dump_tokens("NOT\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
    return NOT;
}

"[" {
    dump_tokens("LBRACKET\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
    return LBRACKET;
}

"]" {
    dump_tokens("RBRACKET\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
    return RBRACKET;
}

"getint" {

        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::intType, {});//返回类型int，无参数
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域GLOBAL(0)
        globalTable->install(yytext, entry);
        return ID;

}
"getch" {

        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::intType, {});//返回类型int，无参数
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域GLOBAL(0)
        globalTable->install(yytext, entry);
        return ID;

}
"getfloat" {
        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::floatType, {});//返回类型int，无参数
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域GLOBAL(0)
        globalTable->install(yytext, entry);
        return ID;

}
"getarray" {

        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; //形参类型表
        Type* arrayType = new IntArrayType();
        vec.push_back(arrayType);
        Type* funcType = new FunctionType(TypeSystem::intType, vec);
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;

}
"getfarray" {
        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; //形参类型表
        Type* arrayType = new FloatArrayType();
       vec.push_back(arrayType);
        Type* funcType = new FunctionType(TypeSystem::intType, vec);
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;
}
"putint" {
        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; //形参类型表
        vec.push_back(TypeSystem::intType);
        Type* funcType = new FunctionType(TypeSystem::voidType, vec);//返回类型void，参数表[int]
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;
}
"putch" {
        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; //形参类型表
        vec.push_back(TypeSystem::intType);
        Type* funcType = new FunctionType(TypeSystem::voidType, vec);//返回类型void，参数表[int]
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;
}
"putfloat" {
        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; //形参类型表
        vec.push_back(TypeSystem::floatType);
        Type* funcType = new FunctionType(TypeSystem::voidType, vec);//返回类型void，参数表[int]
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;
}
"putarray" {
        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; //形参类型表
        vec.push_back(TypeSystem::intType);
        Type* arrayType = new IntArrayType();
        ((IntArrayType*)arrayType)->pushBackDimension(-1);
        vec.push_back(arrayType);
        Type* funcType = new FunctionType(TypeSystem::voidType, vec);
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;
}
"putfarray" {
        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; //形参类型表
        vec.push_back(TypeSystem::intType);
        Type* arrayType = new FloatArrayType();
        ((FloatArrayType*)arrayType)->pushBackDimension(-1);
        vec.push_back(arrayType);
        Type* funcType = new FunctionType(TypeSystem::voidType, vec);
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;

}
"putf" {
        columnNo+=yyleng;
        char *lexeme = new char[yyleng + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        std::vector<Type*> vec; //形参类型表
        vec.push_back(TypeSystem::floatType);
        Type* funcType = new FunctionType(TypeSystem::voidType, vec);
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;
}

"_sysy_starttime" {
        columnNo += yyleng;
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::voidType, {});//返回类型void，无参数
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); 
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;
}
"_sysy_stoptime" {
        columnNo += yyleng;
        char *lexeme = new char[strlen(yytext) + 1];
        strcpy(lexeme, yytext);
        yylval.strtype = lexeme;
        Type* funcType = new FunctionType(TypeSystem::voidType, {});//返回类型void，无参数
        SymbolTable* globalTable;    //全域符号表
        for(globalTable = identifiers;globalTable->getPrev();globalTable = globalTable->getPrev()); //全域符号表
        SymbolEntry* entry = new IdentifierSymbolEntry(funcType, yytext, 0);//作用域(0)
        globalTable->install(yytext, entry);
        return ID;
}

{DECIMIAL} {
    int decimal;
    decimal = atoi(yytext);
    yylval.itype = decimal;
    dump_tokens("DECIMAL\t%s\t%d\t%d\t%d\n", yytext,yylineno,columnNo, decimal);
    return INTEGER;
}
{OCTAL} {
    int oct = 0;
    sscanf(yytext, "%o", &oct);
    yylval.itype = oct;
    dump_tokens("OCTAL\t%s\t%d\t%d\t%d\n", yytext,yylineno,columnNo, oct);

    return INTEGER;
}
{HEXDECIMAL} {
    int hex = 0;
    sscanf(yytext,"%016x",&hex);
    yylval.itype = hex;
    dump_tokens("HEX\t%s\t%d\t%d\t%d\n", yytext,yylineno,columnNo, hex);
    return INTEGER;
}
{FLOAT_NUMBER} {
    float f ;
    sscanf(yytext, "%f", &f);
    yylval.ftype = f;
    dump_tokens("TYPE_FLOAT\t%s\t%d\t%d\t%f\n", yytext,yylineno,columnNo, f);
    return FLOATING;
}

{HEX_FLOAT} {
    float f ;
    sscanf(yytext, "%f", &f);
    yylval.ftype = f;    
    dump_tokens("HEX_FLOAT\t%s\t%d\t%d\t%f\n", yytext,yylineno,columnNo, f);
    return FLOATING;
}

{ID} {
    char *lexeme;
    lexeme = new char[yyleng + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    dump_tokens("ID\t\t%s\t%d\t%d\t\n", yytext,yylineno,columnNo);
    return ID;
}

{EOL} {
    columnNo = 0; //换行时列数置0
}

{WHITE} {
    columnNo+=1;
}



