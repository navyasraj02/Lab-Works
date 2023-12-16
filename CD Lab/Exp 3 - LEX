%option noyywrap
%{
        #include<stdio.h>
        int lines=0,words=0,chars=0;
%}
%%
[a-zA-Z]+ {words++;chars+=strlen(yytext);}
\n {chars++;lines++;}
. {chars++;}
%%
int main(int argc, char *argv[]){
        yyin=fopen(argv[1],"r");
        yylex();
        fclose(yyin);
        printf("%d lines, %d words, %d chars\n",lines,words,chars);
}
