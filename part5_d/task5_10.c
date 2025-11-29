#include <stdio.h>

#define BUFLEN 1000
#define NUMBER '0'

char stack[BUFLEN];
int sp = 0;

void push(int n) {
    if (sp < BUFLEN) {
        stack[sp++] = n;
    } else {
        printf("error: no memory space\n");
    }
}

int pop(void) {
    if (sp > 0) {
        return stack[--sp];
    }
    printf("error: stack empty\n");
    return 0;
}

int misdigit(char *s) {
    if (s == NULL || *s == '\0') {
        return 0;
    }
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int atoi(char *s) {
    int n = 0;
    for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++) {
        n = 10 * n + (s[i] - '0');
    }
    return n;
}

int main(int argc, char *argv[]) {
    argv++;
    while (--argc > 0) {
        char *p = *argv++;  
        if (misdigit(p)) {
            push(atoi(p));
        } 
        else if (*p == '+') {
            push(pop() + pop());
        } 
        else if (*p == '-') {
            int a = pop();
            push(pop() - a);
        } 
        else if (*p == '/') {
            int a = pop();
            if (a != 0) {
                push(pop() / a);
            }
        }
        else if (*p == '*') {
            push(pop() * pop());
        }
        else {
            printf("Unknown operator: %s\n", p);
            return 1;
        }
    }
    printf("Result: %d", pop());
    return 0;
}