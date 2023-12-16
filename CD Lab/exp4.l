%option noyywrap
%{
        #include<string.h>
%}
%%
"abc" {strcpy(yytext,"ABC");ECHO;}
. {ECHO;}
%%
int main(int argc,char *argv[]){
        yyin=fopen(argv[1],"r");
        yylex();
        fclose(yyin);
}
