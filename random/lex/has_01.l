%{
#include <stdio.h>
int positive = 0, negative = 0;
%}

%%
.*01.*  {    printf("has \n");}
[ \t\n]+                ;
.                     ; // ignore other characters

%%

int main() {
     printf("Enter input:\n");
    yylex();
    return 0;
}
