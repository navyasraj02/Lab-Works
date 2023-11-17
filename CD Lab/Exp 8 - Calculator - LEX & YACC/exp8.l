%option noyywrap
%{
#define YYSTYPE double
#include "calc.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+(\.[0-9]*)? { yylval=atof(yytext); return NUMBER; }
\n { return 0; }
[\t] ;
. { return yytext[0]; }
%%
