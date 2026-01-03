#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *parse_argv(char *name) {
    char *p = name + strlen(name) - 1;
    while (p > name && *(p - 1) != '/') {
        p--;
    }
    return p;
}

int main(int argc, char *argv[]) {
    char *name = parse_argv(argv[0]);
    if (strcmp(name, "upper") == 0) {
        int c;
        while ((c = getchar()) != EOF) {
            putchar(toupper((unsigned char)c));
        }
    } else if (strcmp(name, "lower") == 0) {
        int c;
        while ((c = getchar()) != EOF) {
            putchar(tolower((unsigned char)c));
        }
    }
    return 0;
}