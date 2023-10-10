%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int yylex();
extern int yyparse();
FILE* yyin;
void yyerror(const char* s);

// 符号表项
struct STE {   //symboltableentry
    char name[50];
    double value;
};

struct STE symbolTable[100];
int symNum = 0;

// 函数声明
double searchSymbol(char *name);
struct STE* allocSymbol(char *name, double value);
%}

%union {
    double val;
    char* name;
}

%token ADD MINUS MULT DIV ASSIGN LEFTPAR RIGHTPAR
%token <val> NUMBER
%token <name> ID

%left ADD MINUS
%left MULT DIV

%right UMINUS ASSIGN

%type <val> expr
%type <val> factor
%type <name> assign

%%

lines   :       lines stmt 
        |       stmt 
        |
        ;


stmt    :       assign ';'
        |       expr    ';'
        ;

assign  :       ID ASSIGN expr { allocSymbol($1,$3);printf("assign!\n");}
        ;

expr    :       expr ADD expr   { $$ = $1 + $3;printf("ADD ,Result is %f\n",$$); }
        |       expr MINUS expr   {$$ = $1 - $3; printf("MINUS,Result is %f\n",$$); }
        |       expr MULT expr  { $$ = $1 * $3;printf("MULT,Result is %f\n",$$); }
        |       expr DIV expr   { $$ = $1 / $3;printf("DIV,Result is %f\n",$$); }
        |       LEFTPAR expr RIGHTPAR { $$ = $2; }
        |       MINUS expr %prec UMINUS   { $$ = -$2; }
        |       NUMBER   { $$ = $1;}
        |       factor  {$$ = $1;}
        ;

factor  :       ID      {$$=searchSymbol($1);printf("%s stands for %f\n",$1,$$);}

%%

int yylex() 
{
    int t;
    char identifier[50]; // 用于存储标识符
    while (1) 
    {
        t = getchar();
        if (t == ' ' || t == '\t' || t == '\n') {
            // 忽略空白字符
        } else if (isdigit(t)) {
            // 识别整数
            ungetc(t, stdin); 
            int num;
            scanf("%d", &num);
            yylval.val = num; // 将识别的整数存储在yylval中
            return NUMBER;
        } else if (isalpha(t)) {
            // 识别标识符
            int i = 0;
            while (isalnum(t)) {  //识别字母开头，数字和字母组成的标识符
                identifier[i++] = t;
                t = getchar();
            }
            ungetc(t, stdin); // 将多读的字符放回输入流
            identifier[i] = '\0';
            yylval.name = strdup(identifier); // 存储标识符字符串
            return ID;
        } else if (t == '+') {
            return ADD;
        } else if (t == '-') {
            return MINUS;
        } else if (t == '*') {
            return MULT;
        } else if (t == '/') {
            return DIV;
        } else if (t == '=') {
            return ASSIGN;
        } else if (t == '(') {
            return LEFTPAR;
        } else if (t == ')') {
            return RIGHTPAR;
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

double searchSymbol(char *name) {
    for (int i = 0; i < symNum; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return symbolTable[i].value;
        }
    }
    printf( "Error: Undefined variable %s\n", name);
    exit(1);
}

struct STE* allocSymbol(char *name, double value) {
    for (int i = 0; i < symNum; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            symbolTable[i].value = value;
            return &symbolTable[i];
        }
    }
    strcpy(symbolTable[symNum].name, name);
    symbolTable[symNum].value = value;
    symNum++;
    return &symbolTable[symNum];
}

void yyerror(const char* s){
    fprintf(stderr,"Parse error: %s\n",s);
    exit(1);
}
