#include <stdio.h>

void strcatt(char s[], char t[]) {
    while (*s) s++;
    while ((*s++ = *t++)) 
        ;   
}

int main() {
    char s[] = "hello";
    char t[] = "world";
    strcatt(s, t);
    printf("Result: %s", s);
    return 0;
}