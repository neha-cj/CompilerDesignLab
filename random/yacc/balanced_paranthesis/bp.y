%{
#include <stdio.h>

int yylex();
void yyerror(const char *s);
%}

%token LP RP

%%

expr:

    |expr LP expr RP
    ;

%%

int main(){
    printf("enter paranthesis string:\n");
    if(yyparse()==0){
        printf("balanced queeen!\n");
    }
    return 0;
}
void yyerror(const char*s){
    printf("unbalanced parathesis\n");
}
     
