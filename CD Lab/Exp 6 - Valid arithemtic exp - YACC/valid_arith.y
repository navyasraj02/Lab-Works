%{
#include<stdio.h>
#include<stdlib.h>
int yyerror();
%}

%token NUM ID
%left '+' '-'
%left '*' '/'
%%
e: e '+' e | e '-' e | e '*' e | e '/' e | '('e')' | NUM | ID;
%%

int main(){
printf("Type the expression and press the enter key \n");
yyparse();
printf("Valid expression\n");
return 0;
}

int yyerror(){
printf("Invalid expression\n");
exit(0);
}
