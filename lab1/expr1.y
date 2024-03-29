%{
/*********************************************
将所有的词法分析功能均放在 yylex 函数内实现，为 +、-、*、/、(、 ) 每个运算符及整数分别定义一个单词类别，在 yylex 内实现代码，能
识别这些单词，并将单词类别返回给词法分析程序。
实现功能更强的词法分析程序，可识别并忽略空格、制表符、回车等
空白符，能识别多位十进制整数。
YACC file
**********************************************/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#ifndef YYSTYPE
#define YYSTYPE char*
#endif
int yylex();
extern int yyparse();
FILE* yyin;
void yyerror(const char* s);
char num[20] = {0};  //支持的最长数字长度为20
char name[20] ={0};

%}

//TODO:给每个符号定义一个单词类别
%token ADD MINUS MULT DIV LEFTPAR RIGHTPAR
%token NUMBER
%left ADD MINUS
%left MULT DIV
%right UMINUS       

%%


lines   :       lines expr ';' { printf("%s\n", $2); }
        |       lines ';'
        |
        ;
//TODO:完善表达式的规则
expr    :       expr ADD expr   { $$ = (char *)malloc(41); strcpy($$,$1); strcat($$,$3); strcat($$,"+ "); }
        |       expr MINUS expr   { $$ = (char *)malloc(41); strcpy($$,$1); strcat($$,$3); strcat($$,"- "); }
        |       expr MULT expr  { $$ = (char *)malloc(41); strcpy($$,$1); strcat($$,$3); strcat($$,"* "); }
        |       expr DIV expr   { $$ = (char *)malloc(41); strcpy($$,$1); strcat($$,$3); strcat($$,"/ "); }
        |       LEFTPAR expr RIGHTPAR { $$ = (char *)malloc(41); strcpy($$,$2); }
        |       MINUS expr %prec UMINUS   { $$ = (char *)malloc(21); strcpy($$,"-"); strcat($$,$2); }
        |       NUMBER   { $$ = (char *)malloc(20); strcpy($$,$1);strcat($$," ");}
        ;



%%

// programs section

int yylex()
{
    int t;
    while(1){
        t=getchar();
        if(t==' '||t=='\t'||t=='\n'){
            //do noting
        }else if(isdigit(t)){
            int m = 0;
            while(1){
                num[m++] = t;
                t = getchar();
                if(!isdigit(t)){
                   ungetc(t,stdin);
                    break;
                }
            }
            num[m] = 0;
            yylval = num;
            return NUMBER;

            //TODO:解析多位数字返回数字类型 
        }else if(t=='+'){
            return ADD;
        }else if(t=='-'){
            return MINUS;
        }//TODO:识别其他符号
        else if(t=='*'){
            return MULT;
        }
        else if(t=='/'){
            return DIV;
        }
        else if(t=='('){
            return LEFTPAR;
        }
        else if(t==')'){
            return RIGHTPAR;
        }
        else{
            return t;
        }
    }
}

int main(void)
{
    yyin=stdin;
    do{
        yyparse();
    }while(!feof(yyin));
    return 0;
}
void yyerror(const char* s){
    fprintf(stderr,"Parse error: %s\n",s);
    exit(1);
}