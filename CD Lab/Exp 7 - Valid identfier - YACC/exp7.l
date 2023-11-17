%option noyywrap
%{
#include "iden.tab.h"
int yyerror();
%}
%%
[0-9]+ {return DIGIT;}
[a-z_A-Z] {return LETTER;}
[ \t] ;
\n return 0;
. {yyerror();}

%%
