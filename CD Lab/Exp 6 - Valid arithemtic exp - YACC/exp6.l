%option noyywrap
%{
        #include<stdio.h>
        #include "y.tab.h"
        int yyerror();
%}
%%
[a-zA-Z_][a-zA-Z0-9_]* {return ID;}
[0-9]+(\.[0-9]+)? {return NUM;}
[\t] ;
[-+*/()] {return yytext[0];}
\n {return 0;}
. {yyerror();}
%%
