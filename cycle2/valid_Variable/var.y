%{
#include <stdio.h>
#include <stdlib.h>

extern char *yytext;
int yylex(void);
void yyerror(const char *s);
%}

%token ID

%%
input: 
     | input line
     ;

line: 
     ID   {printf("valid!\nEnter a varibale name: ");}
    | '\n'      
    | error '\n'  {printf("invalid varibale name\n Enter a varibale name: "); yyerrok;}
    ;

%%
int main(){
    printf("enter a varibale name: ");
    yyparse();
    return 0;
}
void yyerror(const char *s){
    printf("error\n");
}
