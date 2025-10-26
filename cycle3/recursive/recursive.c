#include <stdio.h>
#include <string.h>
// Production rules:
// E -> iZ
// Z -> +iZ
// Z -> ε

char inp[100];
int len = 0;
int curr = 0;

int Z()
{
    int result;
    if (inp[curr] == '+' && inp[curr + 1] == 'i')
    {
        curr += 2;
        result = Z();
        if (result == 1)
            return 1;
    }
    return 1;
}

int E()
{
    int result;
    if (inp[curr] == 'i')
    {
        curr++;
        result = Z();
        if (result == 1)
            return 1;
        else
            return -1;
    }
    return -1;
}

int main()
{
    printf("Enter input:\n");
    scanf("%s", inp);
    int res = E();
    if (res == 1 && curr == strlen(inp))
        printf("Input has been accepted.\n");
    else
        printf("Input has been rejected.\n");
}

// Valid strings
// "i+i+i"
// "i"
// "i+i"
