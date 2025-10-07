/* lex to recognize strings ending with ing */



%{
#include <stdio.h>
%}

%%
[a-zA-Z]*ing   { printf("ending with ing\n"); }
[a-zA-Z]+    {printf("not ending with ing\n"); }
[ \t\n]+   ;
.          ;
%%

int main() {
    printf("Enter a string:\n");
    yylex();
    return 0;
}


/*output 
Enter a string:
xjojxxj
not ending with ing
xsichiocjho
not ending with ing
inxuhsing
ending with ing
sxhsiuxhsinghh
not ending with ing
*/
