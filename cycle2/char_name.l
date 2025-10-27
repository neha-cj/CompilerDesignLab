%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char prefix[5];
int initialized=0;
%}

%% 
[ \t\r]+   ;
[\n]       ;
[a-zA-Z0-9]+   {
                    if(!initailized){
                        strncpy(prefix, yytext,4);
                        prefix[4]='\0';
                        printf("stored prefix: %s\n",prefix);
                        printf("now enter word to check (type exit to quit):\n");
                        initailized=1;
                    }else{
                        if(strcmp(yytext, "exit")==0){
                            printf("Exitig...\n");
                            exit(0);
                        }
                        if(strstr(yytext, prefix)==NULL){
                            printf("Accepted:%s\n ",yytext);
                        }
                        else{
                            printf("Rejected: %s\n",yytext);
                        }
                    }
     
                }

[^a-zA-Z0-9 \t\r\n]+   { printf("Ignored special characters: %s\n", yytext);} // Unexpected or special characters
%%

int main() {
    printf("Enter your name (first input): ");
    yylex();
    return 0;
}
