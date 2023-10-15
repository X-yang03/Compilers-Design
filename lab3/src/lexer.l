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
        char* name;//name
    };

    typedef struct SymbolTableEntry STE;
    

    unsigned int oct2dec(unsigned int oct){
        return oct/10*8+oct%10;
    }

    int charNum = 0;

    STE SymbolTable[100];

    int SymbolNum = 0;
    extern dump_type_t dump_type;

    //  dump_tokens用于输出token的信息
    inline void dump_tokens(const char* format, ...){  //变长参数
        va_list args;                                   //va_list表示可变参数列表类型，实际上是一个char*
        va_start(args, format);                         //初始化args，指向第一个可变参数，即format后的第一个参数
        if (dump_type == TOKENS)
            vfprintf(yyout, format, args);              //yyout中输出format格式化的字符串
        va_end(args);
        charNum += yyleng;      //charNum 加上yytext的长度yyleng

    }

    STE* appendSymbol(char* name){
        STE* entry = SymbolTable + SymbolNum;
        entry->name = name;
        SymbolNum++;
        return entry;
    }

    STE* LocateSymbol(char* name){
        STE* entry = SymbolTable;
        for(int i=0;i<SymbolNum;i++){
            entry += 1;
            if(entry->name == name){
                return entry;
            }
        }
        return NULL;
    }
    /* Your code here, if desired (lab3). */
%}
/* definitions section */
splice                  (\\[[:blank:]]*\n)*
SINGLECOMMENT   "//"[^\n]*   
CONST           const
WHILE           while
BREAK           break
CONTINUE        continue
DECIMIAL        ([1-9][0-9]*|0)
OCTAL           (0[1-7][0-7]*|0)
HEXDECIMAL      (0(X|x)[1-f][0-f]*|0)
FLOAT_NUMBER    ([1-9][0-9]*|0"."[0-9]*[1-9])
ID              [[:alpha:]_][[:alpha:][:digit:]_]*
EOL             (\r\n|\n|\r)
WHITE           [\t ]
%x COMMENT
/*  Your code here (lab3). */

%%
    /* rules section */
{SINGLECOMMENT} {
    charNum = 0;
}
[/]{splice}[*]          BEGIN(COMMENT);
<COMMENT>{
  [^*\\\n]+             /* eat anything that's not a '*' or line end */
  "*"+[^*/\\\n]*        /* eat up '*'s not followed by '/'s or line end */
  [*]{splice}[/]        BEGIN(INITIAL);
  [*\\]                 /* stray '*' or backslash */
  \n                    /* Reduce the amount of work needed for yylineno */
}


"int" {     //输出 INT  int    行号    列号
    dump_tokens("INT\t%s\t%d\t%d\n", yytext,yylineno,charNum); //yytext是识别到的字符串
}

"float" {
    dump_tokens("FLOAT\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"void" {
    dump_tokens("VOID\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"if" {
    dump_tokens("IF\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"else" {
    dump_tokens("ELSE\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"return" {
    dump_tokens("RETURN\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"=" {
    dump_tokens("ASSIGN\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"<="    {
    dump_tokens("LESS OR EQUAL\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"<" {
    dump_tokens("LESS\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

">="    {
    dump_tokens("GREATER OR EQUAL\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

">" {
    dump_tokens("GREATER\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"+" {
    dump_tokens("ADD\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"-" {
    dump_tokens("SUB\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"*" {
    dump_tokens("MUL\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}
"/" {
    dump_tokens("DIV\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

";" {
    dump_tokens("SEMICOLON\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"(" {
    dump_tokens("LPAREN\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

")" {
    dump_tokens("RPAREN\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"{" {
    dump_tokens("LBRACE\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"}" {
    dump_tokens("RBRACE\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}
"," {
    dump_tokens("PARSE\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"while" {
    dump_tokens("WHILE\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"continue"  {
    dump_tokens("CONTINUE\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"break" {
    dump_tokens("BREAK\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"const" {
    dump_tokens("CONST\t%s\t%d\t%d\n",yytext,yylineno,charNum);
}

{DECIMIAL} {
    int decimal;
    decimal = atoi(yytext);
    dump_tokens("DECIMAL\t%s\t%d\t%d\t%d\n", yytext,yylineno,charNum, decimal);
}
{OCTAL} {
    int octal;
    octal = oct2dec(atoi(yytext));
    dump_tokens("OCTAL\t%s\t%d\t%d\t%d\n", yytext,yylineno,charNum, octal);
}
{HEXDECIMAL} {
    int hex = 0;
    int tmp;
    sscanf(yytext,"%dx%016x",&tmp,&hex);
    dump_tokens("HEX\t%s\t%d\t%d\t%d\n", yytext,yylineno,charNum, hex);
}
{FLOAT_NUMBER} {
    float f ;
    sscanf(yytext, "%f", &f);
    dump_tokens("FLOAT\t%s\t%d\t%d\t%f\n", yytext,yylineno,charNum, f);
}
{ID} {
    STE* pos = LocateSymbol(yytext);
    if(pos == NULL){
        pos = appendSymbol(yytext);
    }
    dump_tokens("ID\t%s\t%d\t%d\t0x%016lx\n", yytext,yylineno,charNum,pos);
}

{EOL} {
    charNum = 0; //换行时列数置0
}

{WHITE} {
    charNum+=1;
}

    /*  Your code here (lab3). */
%%
/* user code section */
