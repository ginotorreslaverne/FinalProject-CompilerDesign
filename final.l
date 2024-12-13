%{
#include "final.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[\t ]+          ;
"("             { return LPAREN; }
")"             { return RPAREN; }
"+"             { return PLUS; }
"*"             { return MULT; }
\n              { return 0; } // End of input
.               { printf("Unexpected character: %s\n", yytext); return 0; }

%%
