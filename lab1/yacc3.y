%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int yylex();
extern int yyparse();
FILE* yyin;
void yyerror(const char* s);

// 符号表结构
struct SymbolTableEntry {
    char name[50];
    double value;
};

// 符号表
struct SymbolTableEntry symbolTable[100];
int symbolCount = 0;

// 函数声明
double lookupSymbol(char *name);
void insertSymbol(char *name, double value);
%}

%union {
    double val;
    char *name;
}

%token ADD SUB MUL DIV ASSIGN 
%token <val> NUMBER
%token <name> IDENTIFIER

%left ADD SUB
%left MUL DIV

%right UMINUS ASSIGN

%type <val> expression
%type <val> term
%type <val> factor
%type <name> assignment

%%

program: statements
    ;

statements: statements statement
    | statement
    ;

statement: assignment ';' { printf ("MOV %s, %f\n", $1, lookupSymbol($1));}
    | expression ';' { printf("Result: %f\n", $1); }
    ;

assignment: IDENTIFIER ASSIGN expression { insertSymbol($1, $3); $$ = (char *)malloc(50*sizeof(char)); strcpy($$, $1);}
    ;

expression: expression ADD term { $$ = $1 + $3; printf("ADD Result, %f, %f\n", $1, $3);}
    | expression SUB term { $$ = $1 - $3; printf("SUB Result, %f, %f\n", $1, $3);}
    | term { $$ = $1; }
    ;

term: term MUL factor { $$ = $1 * $3; printf("MUL Result, %f, %f\n", $1, $3);}
    | term DIV factor { $$ = $1 / $3; printf("DIV Result, %f, %f\n", $1, $3);}
    | factor { $$ = $1; }
    ;

factor: NUMBER { $$ = $1; }
    | '-' factor %prec UMINUS { $$ = -$2; printf("SUB Result, 0, %f\n", $2);}
    | '(' expression ')' { $$ = $2; }
    | IDENTIFIER { $$ = lookupSymbol($1); }
    ;

%%

int yylex() {
    int t;
    char identifier[50]; // 用于存储标识符

    while (1) {
        t = getchar();
        if (t == ' ' || t == '\t' || t == '\n') {
            // 忽略空白字符
        } else if (isdigit(t)) {
            // 识别整数
            ungetc(t, stdin); // 将第一个数字放回输入流
            int num;
            scanf("%d", &num);
            yylval.val = num; // 将识别的整数存储在yylval中
            return NUMBER;
        } else if (isalpha(t)) {
            // 识别标识符
            int i = 0;
            while (isalnum(t) || t == '_') {
                identifier[i++] = t;
                t = getchar();
            }
            ungetc(t, stdin); // 将多读的字符放回输入流
            identifier[i] = '\0';
            yylval.name = strdup(identifier); // 存储标识符字符串
            return IDENTIFIER;
        } else if (t == '+') {
            return ADD;
        } else if (t == '-') {
            return SUB;
        } else if (t == '*') {
            return MUL;
        } else if (t == '/') {
            return DIV;
        } else if (t == '=') {
            return ASSIGN;
        } else if (t == '(') {
            return '(';
        } else if (t == ')') {
            return ')';
        } else {
            return t; // 未识别的字符直接返回ASCII值
        }
    }
}

int main(void) {
    yyin = stdin;
    do {
        yyparse();
    } while (!feof(yyin));
    return 0;
}

double lookupSymbol(char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return symbolTable[i].value;
        }
    }
    fprintf(stderr, "Error: Undefined variable %s\n", name);
    exit(1);
}

void insertSymbol(char *name, double value) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            symbolTable[i].value = value;
            return;
        }
    }
    strcpy(symbolTable[symbolCount].name, name);
    symbolTable[symbolCount].value = value;
    symbolCount++;
}

void yyerror(const char* s){
    fprintf(stderr,"Parse error: %s\n",s);
    exit(1);
}
