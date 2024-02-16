#include "input.h"

#include <stdbool.h>
#include <stdio.h>

char* getStringInput(char* prompt) {
    printf("%s", prompt);
    char* str;
    scanf("%s", str);
    printf("\n");
    return str;
}

int getIntInput(char *prompt, int max, int min) {
    while (true) {
        printf("%s", prompt);
        int x;
        int scan = scanf("%d", &x);
        if (scan != 1)
            continue;
        return x;
    }
}