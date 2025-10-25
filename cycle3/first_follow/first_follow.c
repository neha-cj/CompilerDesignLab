#include <stdio.h>
#include <string.h>

#define MAX 50

int n; // number of productions
char productions[MAX][MAX];
char firsts[26][MAX];
char follows[26][MAX];
int first_done[26];
int follow_done[26];

int isTerminal(char c) {
    return (c < 'A' || c > 'Z'); // terminal if not uppercase
}

// Add a character to set if not already present
void addToSet(char set[], char c) {
    if (c == '\0') return;
    for (int i = 0; set[i] != '\0'; i++)
        if (set[i] == c) return;
    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
}

void computeFirst(char nonterm) {
    if (first_done[nonterm - 'A']) return;
    char result[MAX] = "";
    
    for (int p = 0; p < n; p++) {
        if (productions[p][0] != nonterm) continue;

        for (int i = 2; productions[p][i] != '\0'; i++) {
            char symbol = productions[p][i];
            if (isTerminal(symbol)) {
                addToSet(result, symbol);
                break;
            } else {
                computeFirst(symbol);
                for (int j = 0; firsts[symbol - 'A'][j] != '\0'; j++)
                    addToSet(result, firsts[symbol - 'A'][j]);

                if (strchr(firsts[symbol - 'A'], 'e') == NULL) break; // no epsilon
            }
        }
    }
    strcpy(firsts[nonterm - 'A'], result);
    first_done[nonterm - 'A'] = 1;
}

void computeFollow(char nonterm) {
    if (follow_done[nonterm - 'A']) return;
    char result[MAX] = "";

    if (nonterm == productions[0][0]) addToSet(result, '$'); // start symbol

    for (int p = 0; p < n; p++) {
        for (int i = 2; productions[p][i] != '\0'; i++) {
            if (productions[p][i] == nonterm) {
                if (productions[p][i + 1] != '\0') {
                    char next = productions[p][i + 1];
                    if (isTerminal(next))
                        addToSet(result, next);
                    else
                        for (int j = 0; firsts[next - 'A'][j] != '\0'; j++)
                            if (firsts[next - 'A'][j] != 'e')
                                addToSet(result, firsts[next - 'A'][j]);
                }
                if (productions[p][i + 1] == '\0' || 
                    (productions[p][i + 1] >= 'A' && strchr(firsts[productions[p][i + 1]-'A'], 'e'))) {
                    if (productions[p][0] != nonterm) {
                        computeFollow(productions[p][0]);
                        for (int j = 0; follows[productions[p][0]-'A'][j] != '\0'; j++)
                            addToSet(result, follows[productions[p][0]-'A'][j]);
                    }
                }
            }
        }
    }

    strcpy(follows[nonterm - 'A'], result);
    follow_done[nonterm - 'A'] = 1;
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (like E=TR):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", productions[i]);

    for (int i = 0; i < 26; i++) first_done[i] = follow_done[i] = 0;

    // Compute FIRST
    for (int i = 0; i < n; i++)
        computeFirst(productions[i][0]);

    // Compute FOLLOW
    for (int i = 0; i < n; i++)
        computeFollow(productions[i][0]);

    printf("\nFIRST sets:\n");
    for (int i = 0; i < 26; i++)
        if (first_done[i]) printf("%c : %s\n", i + 'A', firsts[i]);

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < 26; i++)
        if (follow_done[i]) printf("%c : %s\n", i + 'A', follows[i]);

    return 0;
}
