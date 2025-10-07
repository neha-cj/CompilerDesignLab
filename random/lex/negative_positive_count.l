%{
#include <stdio.h>
int positive = 0, negative = 0;
%}

%%

-?[0-9]+    {
                int num = atoi(yytext);
                if(num >= 0) positive++;
                else negative++;
                printf("Number: %s\n", yytext);
            }
[ \t\n]+    ; // ignore whitespace
.           ; // ignore other characters

%%

int main() {
    printf("Enter numbers:\n");
    yylex();
    printf("Positive numbers: %d\n", positive);
    printf("Negative numbers: %d\n", negative);
    return 0;
}
/*  ? used for zero or one appearance ie no - or 1 - */
