%option noyywrap  
%option nounput
%option noinput
%option yylineno
%top{
    #include <stdarg.h>
    #include "common.h"
}
%{
    struct SymbolTableEntry{
        char name[20];//name

    };

    typedef struct SymbolTableEntry STE;
    
    int columnNo = 0;

    STE SymbolTable[100];

    int SymbolNum = 0;

    bool preToken = 0; //0表示加减号 ，1表示为正负号

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

    STE* appendSymbol(char* name){
        STE* entry = SymbolTable + SymbolNum;
        //entry->name = name;
        strcpy(entry->name,name);
        SymbolNum++;
        return entry;
    }

    STE* LocateSymbol(char* name){
        STE* entry = SymbolTable;
        for(int i=0;i<SymbolNum;i++){
            //printf("%s\n", entry->name);
            if(strcmp(entry->name,name) == 0){
                return entry;
            }
        entry += 1;            
        }
        return NULL;
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
digit           [0-9]
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


"int" {     //输出 INT  int    行号    列号
    dump_tokens("INT\t\t%s\t%d\t%d\n", yytext,yylineno,columnNo); //yytext是识别到的字符串
}

"float" {
    dump_tokens("FLOAT\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"void" {
    dump_tokens("VOID\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"if" {
    dump_tokens("IF\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"else" {
    dump_tokens("ELSE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"return" {
    dump_tokens("RETURN\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}
"==" {
    dump_tokens("EQ\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 1;
}

"=" {
    dump_tokens("ASSIGN\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 1; //跟在 = 后的+ -为正负号
}

"<="    {
    dump_tokens("LE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 1;
}

"<" {
    dump_tokens("LESS\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 1;
}

">="    {
    dump_tokens("GE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 1;
}

">" {
    dump_tokens("GREATER\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 1;
}

"+" {
    dump_tokens("ADD\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"-" {
    if(!preToken)
        dump_tokens("SUB\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    else
        dump_tokens("MINUS\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"*" {
    dump_tokens("MUL\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}
"/" {
    dump_tokens("DIV\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

";" {
    dump_tokens("SEMICOLON\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 1;
}

"(" {
    dump_tokens("LPAREN\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 1;
}

")" {
    dump_tokens("RPAREN\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 0;
}

"{" {
    dump_tokens("LBRACE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"}" {
    dump_tokens("RBRACE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}
"," {
    dump_tokens("PARSE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
    preToken = 1;
}

"while" {
    dump_tokens("WHILE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"continue"  {
    dump_tokens("CONTINUE\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"break" {
    dump_tokens("BREAK\t%s\t%d\t%d\n", yytext,yylineno,columnNo);
}

"const" {
    dump_tokens("CONST\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
}

"&&"    {
    dump_tokens("AND\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
    preToken = 1;
}

"||"    {
    dump_tokens("OR\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
    preToken = 1;
}

"!" {
    dump_tokens("NOT\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
}

"[" {
    dump_tokens("LBRACKET\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
}

"]" {
    dump_tokens("RBRACKET\t%s\t%d\t%d\n",yytext,yylineno,columnNo);
}


{DECIMIAL} {
    int decimal;
    decimal = atoi(yytext);
    dump_tokens("DECIMAL\t%s\t%d\t%d\t%d\n", yytext,yylineno,columnNo, decimal);
    preToken = 0;
}
{OCTAL} {
    int oct = 0;
    sscanf(yytext, "%o", &oct);
    dump_tokens("OCTAL\t%s\t%d\t%d\t%d\n", yytext,yylineno,columnNo, oct);
    preToken = 0;
}
{HEXDECIMAL} {
    int hex = 0;
    sscanf(yytext,"%016x",&hex);
    dump_tokens("HEX\t%s\t%d\t%d\t%d\n", yytext,yylineno,columnNo, hex);
    preToken = 0;
}
{FLOAT_NUMBER} {
    float f ;
    sscanf(yytext, "%f", &f);
    dump_tokens("FLOAT\t%s\t%d\t%d\t%f\n", yytext,yylineno,columnNo, f);
    preToken = 0;
}

{HEX_FLOAT} {
    float f ;
    sscanf(yytext, "%f", &f);
    dump_tokens("HEX_FLOAT\t%s\t%d\t%d\t%f\n", yytext,yylineno,columnNo, f);
    preToken = 0;
}

{ID} {
    STE* pos = LocateSymbol(yytext);
    if(pos == NULL){
        pos = appendSymbol(yytext);
    }
    dump_tokens("ID\t\t%s\t%d\t%d\t0x%016lx\n", yytext,yylineno,columnNo,pos);
    preToken = 0;
}

{EOL} {
    columnNo = 0; //换行时列数置0
}

{WHITE} {
    columnNo+=1;
}

    /*  Your code here (lab3). */
%%
/* user code section */

