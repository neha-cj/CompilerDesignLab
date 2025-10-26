%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+        { yylval.num = atoi(yytext); return NUMBER; }
[+\-*/()]     { return yytext[0]; }
[ \t\r]+      ;  // Ignore whitespace
\n            { return '\n'; }
.             { printf("Invalid character: %s\n", yytext); }

%%
int yywrap(void) {
    return 1;
}
