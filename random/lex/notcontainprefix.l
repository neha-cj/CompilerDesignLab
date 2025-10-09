%{
#include <stdio.h>
#include <string.h>
char prefix[5];
int initialized = 0;
%}

%%

[ \t\r\n]+ ;  // ignore whitespace/newlines

[a-zA-Z0-9]+ {
    if(!initialized) {
        // First word = name
        strncpy(prefix, yytext, 4);
        prefix[4] = '\0';
        initialized = 1;
        printf("Prefix stored: %s\n", prefix);
        printf("Enter words to check (type 'exit' to quit):\n");
    } else {
        if(strcmp(yytext, "exit") == 0) exit(0);
        if(strncmp(yytext, prefix, 4) == 0)
            printf("%s → Rejected (starts with prefix %s)\n", yytext, prefix);
        else
            printf("%s → Accepted\n", yytext);
    }
}

. ;  // ignore other characters

%%

int yywrap() { return 1; }

int main() {
    printf("Enter your name (first input): ");
    yylex();
    return 0;
}
