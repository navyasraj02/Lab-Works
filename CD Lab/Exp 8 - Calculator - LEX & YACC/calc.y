%{
#include<stdlib.h>
#include<stdio.h>
#define YYSTYPE double
int yylex();
int yyerror();
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%left '(' ')'
%right UMINUS

%%
stmt: expr { printf("%g\n",$1); }
expr: expr '+' expr {$$=$1+$3;}
    | expr '-' expr {$$=$1-$3;}
    | expr '*' expr {$$=$1*$3;}
    | expr '/' expr {$$=$1/$3;}
    | '-' expr %prec UMINUS {$$=-$2;}
    | '(' expr ')' {$$=$2;}
    | NUMBER {$$=$1;}
;
%%
int main()
{
 yyparse();
}
int yyerror(char*s)
{
 printf("%s-Invalid expression\n",s);
 return 0;
}
