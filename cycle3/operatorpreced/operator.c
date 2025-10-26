#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX], input[MAX];
int top = -1;

/* Terminals used in precedence table (must match order) */
char symbols[] = {'+', '*', 'i', '(', ')', '$'};

/* Operator precedence table */
char prec[6][6] = {
    //    +    *    i    (    )    $
    /*+*/ {'>', '<', '<', '<', '>', '>'},
    /***/ {'>', '>', '<', '<', '>', '>'},
    /*i*/ {'>', '>', 'E', 'E', '>', '>'},
    /*(*/ {'<', '<', '<', '<', '=', 'E'},
    /*)*/ {'>', '>', 'E', 'E', '>', '>'},
    /*$*/ {'<', '<', '<', '<', 'E', '='}
};

/* Push symbol onto stack */
void push(char c) {
    stack[++top] = c;
}

/* Pop top of stack */
void pop() {
    if (top >= 0)
        top--;
}

/* Display current stack and remaining input */
void display(int i) {
    for (int k = 0; k <= top; k++)
        printf("%c", stack[k]);
    printf("\t");

    for (int k = i; k < strlen(input); k++)
        printf("%c", input[k]);
    printf("\t");
}

/* Return index of symbol in symbols array (for precedence table) */
int getIndex(char c) {
    for (int i = 0; i < 6; i++)
        if (symbols[i] == c)
            return i;
    return -1;
}

/* Get index of the topmost terminal in the stack */
int getTopTerminalIndex() {
    for (int j = top; j >= 0; j--) {
        int idx = getIndex(stack[j]);
        if (idx != -1)
            return idx;
    }
    return -1; // No terminal found
}

/* Attempt to reduce the top of the stack according to grammar rules */
int reduce() {
    // E + E or E * E → E
    if (top >= 2 && stack[top] == 'E' &&
        (stack[top - 1] == '+' || stack[top - 1] == '*') &&
        stack[top - 2] == 'E') {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    // ( E ) → E
    if (top >= 2 && stack[top] == ')' &&
        stack[top - 1] == 'E' &&
        stack[top - 2] == '(') {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    // i → E
    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'E';
        return 1;
    }

    return 0; // No valid reduction
}

int main() {
    int i = 0;
    char action;

    printf("Enter the input string ending with $: ");
    scanf("%s", input);

    push('$');

    printf("\nStack\tInput\tAction\n");

    while (1) {
        display(i);
        int row = getTopTerminalIndex(); // find nearest terminal on stack
        int col = getIndex(input[i]);    // current input symbol

        if (row == -1 || col == -1) {
            printf("Error (invalid symbol)\n");
            break;
        }

        // Accept condition: stack = $E and input = $
        if (input[i] == '$' && top == 1 && stack[0] == '$' && stack[1] == 'E') {
            printf("Accept\n");
            break;
        }

        action = prec[row][col];

        if ((action == '<' || action == '=') && input[i] != '$') {
            printf("Shift\n");
            push(input[i]);
            i++;
        } else if (action == '>') {
            if (reduce()) {
                printf("Reduce\n");
            } else {
                printf("Error (no valid reduction)\n");
                break;
            }
        } else {
            printf("Error (invalid precedence)\n");
            break;
        }
    }

    return 0;
}
