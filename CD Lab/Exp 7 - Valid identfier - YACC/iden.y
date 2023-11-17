%{
#include<stdio.h>
#include<stdlib.h>
int yyerror();
%}
%token DIGIT
%token LETTER
%%

variable:LETTER alphanum;
alphanum: LETTER alphanum | DIGIT alphanum | LETTER | DIGIT;
%%
int main()
{
 printf("Enter identifier:");
 yyparse();
 printf("valid identifier\n");
 return 0;
}
int yyerror(){
printf("invalid identifier\n");
exit(0);
}
