#include <stdio.h>
#include <string.h>

void gen_code_for_operator(char *inp, char op , char *reg){
    int i=0,j=0;
    char temp[100];
    while(inp[i]!='\0'){
        if(inp[i]==op){
            printf("%c\t%c\t%c\t%c\n",op, *reg, inp[i-1], inp[i+1]);
            temp[j-1]= *reg;
            i+=2;
        }else{
            temp[j++]=inp[i];
        }
        i++;
    }
    temp[j]='\0';
    strcpy(inp,temp);
    (*reg)--;
}

void gen_code(char *inp){
    char reg='Z'; 
    gen_code_for_operator(inp, '/', &reg);
    gen_code_for_operator(inp, '*', &reg);
    gen_code_for_operator(inp, '+', &reg);
    gen_code_for_operator(inp, '-', &reg);
    gen_code_for_operator(inp, '=', &reg);
}

int main(){
    char inp[100];
    printf("Enter expression: ");
    scanf("%s",inp);
    printf("Oprt\tDestn\tOp1\tOp2\n");
    gen_code(inp);
}
