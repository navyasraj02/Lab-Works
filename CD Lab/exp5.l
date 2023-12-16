%option noyywrap
%{
        #include<stdio.h>
        int vowels=0,consonants=0;
%}
%%
[aeiouAEIOU] {vowels++;}
[a-zA-Z] {consonants++;}
. {;}
%%
int main(int argc,char *argv[]){
        yyin=fopen(argv[1],"r");
        yylex();
        fclose(yyin);
        printf("Vowels = %d, Consonants = %d\n",vowels,consonants);
}
