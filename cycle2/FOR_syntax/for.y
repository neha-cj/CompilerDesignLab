%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

/* Tokens from Lex */
%token FOR ID NUM RELOP ASSIGN PLUSPLUS

%%
stmt:
    FOR '(' assign_stmt ';' cond ';' assign_stmt ')' '{' '}'    {printf("Valid FOR loop syntax\n");}
;

assign_stmt:
      ID ASSIGN ID
    | ID ASSIGN NUM
    | ID PLUSPLUS
;

cond:
      ID RELOP ID
    | ID RELOP NUM
;
%%

void yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
}

int main() {
    printf("Enter a FOR loop:\n");
    yyparse();
    return 0;
}
