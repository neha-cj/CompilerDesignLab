%{
#include "y.tab.h"
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*   {return ID;}
.|\n                     {return yytext[0];}

%%
