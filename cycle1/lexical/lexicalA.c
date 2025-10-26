#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]){
    char keyword[32][10]={"auto", "break", "case", "char","const", "continue","void","main","int"};

    for(int i=0;i<32;++i){
        if(strcmp(keyword[i],buffer)==0)
            return 1;
    }
    return 0;
}

int main(){
    char c,buffer[31],operators[]="+-*/%=";
    FILE *fp;
    int i,j=0;
    fp=fopen("program.txt","r");
    if(fp==NULL){
        printf("error opening file\n");
        exit(0);
    }
    while((c=fgetc(fp))!=EOF){
        for(i=0;i<6;++i){
            if(c==operators[i])
                printf("%c is operator\n",c);
        }
        if(isalnum(c)){
            buffer[j++]=c;
        }
        else if((c==' '|| c=='\t' || c=='\n') && (j!=0)){
            buffer[j]= '\0';
            j=0;

            if(isKeyword(buffer)==1)
                printf("%s is keyword\n", buffer);
            else
                printf("%s is identifier\n", buffer);
        }
        
    }
    fclose(fp);
    return 0;
}
