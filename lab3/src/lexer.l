%option noyywrap   
%option nounput
%option noinput
%top{
    #include <stdarg.h>
    #include "common.h"
}
%{
    extern dump_type_t dump_type;

    yylineno = 0;

    int charNum = 0;

    inline void dump_tokens(const char* format, ...){  //变长参数
        va_list args;       //va_list表示可变参数列表类型，实际上是一个char*
        va_start(args, format); //初始化args，指向第一个可变参数，即format后的第一个参数
        if (dump_type == TOKENS)
            vfprintf(yyout, format, args);  //yyout中输出format格式化的字符串
        va_end(args);
        charNum += yyleng; //charNum 加上yytext的长度yyleng
        charNum++;   //加上空格
    }


    /* Your code here, if desired (lab3). */
%}

/* definitions section */
SINGLECOMMENT   //
COMNMENTBEGIN   /*
COMNMENTEND     */
CONST           const
WHILE           while
BREAK           break
CONTINUE        continue
RETURN          return
DECIMIAL        ([1-9][0-9]*|0)
ID              [[:alpha:]_][[:alpha:][:digit:]_]*
EOL             (\r\n|\n|\r)
WHITE           [\t ]
/*  Your code here (lab3). */

%%
    /* rules section */
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

"<" {
    dump_tokens("LESS\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

"+" {
    dump_tokens("ADD\t%s\t%d\t%d\n", yytext,yylineno,charNum);
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

{DECIMIAL} {
    int decimal;
    decimal = atoi(yytext);
    dump_tokens("DECIMAL\t%s\t%d\t%d\t%d\n", yytext,yylineno,charNum, decimal);
}

{ID} {
    dump_tokens("ID\t%s\t%d\t%d\n", yytext,yylineno,charNum);
}

{EOL} {
    yylineno++;
    charNum = 0; //换行时列数置0
}

{CONST} {
    dump_tokens("CONST\t%s\t%d\t%d\n",yytext,yylineno,charNum);
}

{WHITE}

    /*  Your code here (lab3). */
%%
/* user code section */
