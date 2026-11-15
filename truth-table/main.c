#include <stdio.h>
#include <string.h>

#define A 0
#define B 1
#define C 2
#define D 3
#define X 4
#define Y 5
#define Q 6

#define PARTS 3
#define MAX_VARS 4
#define MAX_OPS 6
#define KNOWN_CHARS 14
#define MAX_PART_LEN 20

enum OPERATORS {
    OR = 0,
    AND,
    XOR,
    NOR,
    NAND,
    XNOR
};

int isPartInv(const char *string, int len);
char findNthChar(const char *string, int len, int nth, int invVars[MAX_VARS], int place);
int findOperation(const char *string, int len, const char knownOps[MAX_OPS / 2]);
char isInvalidChar(const char *string, int len, const char knownChars[KNOWN_CHARS]);
void removeSpaces(char *string, int len);
int calc(int a, int b, int operation);
void calcX(int table[7][16], const char varOrder[MAX_VARS], const int invVars[MAX_VARS], int isPartInv, int operation);
void calcY(int table[7][16], const char varOrder[MAX_VARS], const int invVars[MAX_VARS], int isPartInv, int operation);
void calcQ(int table[7][16], int isPartInv, int operation);

int or(int a, int b);
int and(int a, int b);
int xor(int a, int b);

int main(void) {
    char x[MAX_PART_LEN], y[MAX_PART_LEN], q[MAX_PART_LEN];

    const char knownChars[KNOWN_CHARS] = {'a', 'b', 'c', 'd', 'x', 'y', 'Q', '&', '|', '^', '!', '(', ')', '\n'};
    const char knownOps[MAX_OPS / 2] = {'&', '|', '^'};
    int xLen, yLen, qLen;

    int table[7][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
        {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {0},
        {0},
        {0}
    };

    printf("Please ONLY USE: a, b, c, d, x, y, Q, &, |, ^, !, (, )\n");
    printf("& = and, | = or, ^ = xor, !& = nand, !| = nor, !^ = xnor\n");
    printf("!a = not a, !b = not b, !c = not c, !d = not d\n");
    printf("!(a & b) = not (a and b)...\n\n");

    printf("Example: if Q = (not ((a nand not b) or (not (not c xor d))))\n");
    printf("This equals: Q = (!((a !& !b) | (!(!c ^ d))))\n");
    printf("From that: x = (a !& !b), y = !(!c ^ d), Q = !(x | y)\n");

    printf("\nSpecial case: Only two variables are in brackets instead of four:\nIf there is one \"and\" and one \"or\", put the \"and\" expression in brackets.\n");
    printf("If there are multiple same (or-or / and-and) expressions without brackets, put the second one in brackets\n");
    printf("-> Q = (a and b) or c and d   equals   Q = (a and b) or (c and d)\n");
    printf("-> Q = (a nor b) and not c and d   equals   Q = (a nor b) and (not c and d)\n");

    printf("\n\nPlease enter x, y and Q\n\n");

    {
        printf("x = ");

        fgets(x, MAX_PART_LEN, stdin);
        xLen = (int) strlen(x);
        removeSpaces(x, xLen);
        char ret = isInvalidChar(x, MAX_PART_LEN, knownChars);

        if (ret) {
            printf("\nInvalid input (%c), please restart", ret);
            getchar();
            return 1;
        }

        printf("y = ");

        fgets(y, MAX_PART_LEN, stdin);
        yLen = (int) strlen(y);
        removeSpaces(y, yLen);
        ret = isInvalidChar(y, MAX_PART_LEN, knownChars);

        if (ret) {
            printf("\nInvalid input (%c), please restart", ret);
            getchar();
            return 1;
        }

        printf("Q = ");

        fgets(q, MAX_PART_LEN, stdin);
        qLen = (int) strlen(q);
        removeSpaces(q, qLen);
        ret = isInvalidChar(q, MAX_PART_LEN, knownChars);

        if (ret) {
            printf("\nInvalid input (%c), please restart", ret);
            getchar();
            return 1;
        }
    } // Input

    int invVars[MAX_VARS] = {0};
    char varOrder[MAX_VARS] = {'\0'};
    varOrder[0] = findNthChar(x, xLen, 1, invVars, 0);
    varOrder[1] = findNthChar(x, xLen, 2, invVars, 1);
    varOrder[2] = findNthChar(y, yLen, 1, invVars, 2);
    varOrder[3] = findNthChar(y, yLen, 2, invVars, 3);

    calcX(table, varOrder, invVars, isPartInv(x, xLen), findOperation(x, xLen, knownOps));
    calcY(table, varOrder, invVars, isPartInv(y, yLen), findOperation(y, yLen, knownOps));
    calcQ(table, isPartInv(q, qLen), findOperation(q, qLen, knownOps));


    printf("\n\n\n");
    for (int i = 0; i < 16; i++) {
        printf("%d\n", table[Q][i]);
    }

    getchar();

    return 0;
}

int isPartInv(const char *string, const int len) {
    for (int i = 0; i < len - 1; i++) {
        if (string[i] == '!' && string[i + 1] == '(') {
            return 1;
        }
    }

    return 0;
}

char findNthChar(const char *string, const int len, int nth, int invVars[MAX_VARS], const int place) {
    for (int i = 0; i < len; i++) {
        if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z')) {
            nth--;

            if (nth == 0) {
                if (i > 0) {
                    if (string[i - 1] == '!') {
                        invVars[place] = 1;
                    } else {
                        invVars[place] = 0;
                    }
                }

                return string[i];
            }
        }
    }

    return '\0';
}


int findOperation(const char *string, const int len, const char knownOps[MAX_OPS / 2]) {
    char operationCh = '\0';
    int invert = 0;
    int operationNum = 0;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < MAX_OPS / 2; j++) {
            if (string[i] == knownOps[j]) {
                operationCh = knownOps[j];

                if (i > 0) {
                    if (string[i - 1] == '!') {
                        invert = 1;
                    }
                }

                break;
            }
        }

        if (operationCh != '\0') {
            break;
        }
    }

    if (invert) {
        operationNum = 3; // verschiebung um 3 bedeutet inversion der operation durch passende struktur im enum
    }

    switch (operationCh) {
        case '|': break;
        case '&': operationNum += 1; break;
        case '^': operationNum += 2; break;
        default: break;
    }

    return operationNum;
}

char isInvalidChar(const char *string, const int len, const char knownChars[KNOWN_CHARS]) {
    for (int i = 0; i < len; i++) {
        int isUnknown = 1;
        for (int j = 0; j < KNOWN_CHARS; j++) {
            if (string[i] == knownChars[j]) {
                isUnknown = 0;
                break;
            }
        }

        if (isUnknown) {
            return string[i];
        }
    }

    return '\0';
}

void removeSpaces(char *string, const int len) {
    char *addr = strchr(string, '\n');

    if (addr != NULL) {
        *addr = '\0';
    }

    for (int i = 0; i < len; i++) {
        if (string[i] == ' ') {
            if (i < len - 1) {
                for (int j = i; j < len - 1; j++) {
                    string[j] = string[j + 1];
                }

                string[len - 1] = '\0';
            } else {
                string[i] = '\0';
            }

            i--;
        }
    }
}

int calc(const int a, const int b, int operation) {
    switch (operation) {
        case OR: return (a || b);
        case AND: return (a && b);
        case XOR: return (a ^ b);
        case NOR: return !(a || b);
        case NAND: return !(a && b);
        case XNOR: return !(a ^ b);
        default: return 0;
    }
}

void calcX(int table[7][16], const char varOrder[MAX_VARS], const int invVars[MAX_VARS], const int isPartInv, const int operation) {
    for (int i = 0; i < 16; i++) {
        int v1 = table[varOrder[0] - 'a'][i];
        int v2 = table[varOrder[1] - 'a'][i];
        int result = 0;

        if (invVars[0]) {
            v1 = !v1;
        } if (invVars[1]) {
            v2 = !v2;
        }

        result = calc(v1, v2, operation);

        if (isPartInv) {
            result = !result;
        }

        table[X][i] = result;
    }
}

void calcY(int table[7][16], const char varOrder[MAX_VARS], const int invVars[MAX_VARS], const int isPartInv, const int operation) {
    for (int i = 0; i < 16; i++) {
        int v1 = table[varOrder[2] - 'a'][i];
        int v2 = table[varOrder[3] - 'a'][i];
        int result = 0;

        if (invVars[2]) {
            v1 = !v1;
        } if (invVars[3]) {
            v2 = !v2;
        }

        result = calc(v1, v2, operation);

        if (isPartInv) {
            result = !result;
        }

        table[Y][i] = result;
    }
}

void calcQ(int table[7][16], const int isPartInv, const int operation) {
    for (int i = 0; i < 16; i++) {
        const int v1 = table[X][i];
        const int v2 = table[Y][i];
        int result = 0;

        result = calc(v1, v2, operation);

        if (isPartInv) {
            result = !result;
        }

        table[Q][i] = result;
    }
}