%{
#include <stdio.h>
%}

%%

[0-9]{10}    { printf("Valid mobile number: %s\n", yytext); }

.|\n         ; // ignore other characters

%%

int main() {
    printf("Enter text:\n");
    yylex();
    return 0;
}
