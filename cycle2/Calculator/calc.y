%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%union{
    int num;
}

%token <num> NUMBER
%left '+' '-'
%left '*' '/'
%left UMINUS

%type <num> expr

%%

input:
      /* empty */
    | input expr '\n'   { printf("Result: %d\n", $2); }
    ;

expr:
      NUMBER              { $$ = $1; }
    | expr '+' expr       { $$ = $1 + $3; }
    | expr '-' expr       { $$ = $1 - $3; }
    | expr '*' expr       { $$ = $1 * $3; }
    | expr '/' expr       {
                            if ($3 == 0) {
                                printf("Error: Division by zero\n");
                                $$ = 0;
                            } else {
                                $$ = $1 / $3;
                            }
                          }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')'        { $$ = $2; }
    ;

%%

int main() {
    printf("Enter arithmetic expressions (Ctrl+C to exit):\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    printf("Syntax error: %s\n", s);
}
