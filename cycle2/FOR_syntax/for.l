%{
#include "for.tab.h"
%}

%%
"for"               { return FOR; }
"++"                { return PLUSPLUS; }
"="                 { return ASSIGN; }
"=="|"<"|">"|"<="|">=" { return RELOP; }
[0-9]+              { return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
[ \t\n]+            { /* ignore whitespace */ }
.                   { return yytext[0]; }
%%

int yywrap(void) {
    return 1;
}
