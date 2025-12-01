#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 100
#define MAXLINE 1000
#define LAST 10

int mgetline(char *s, int lim) {
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') s[i++] = c;
    if (c == '\n') {
        s[i++] = '\n';
    }
    s[i] = '\0';
    return i;
}

int aatoi(char *s) {
    int n = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            n = 10 * n + (s[i] - '0');
        }
    }
    return n;
}

int main(int argc, char *argv[]) {
    int len;
    char line[MAXLINE];
    int last_strings = (argc < 2) ? LAST : aatoi(argv[1]);
    if (last_strings <= 0) last_strings = LAST;
    char *buffer[last_strings];
    int i = 0;
    while ((len = mgetline(line, MAXLINE)) > 0) {
        char *p = malloc(strlen(line) + 1);
        strcpy(p, line);
        buffer[i % last_strings] = p;
        i++;
    }
    int start = (i >= last_strings) ? i % last_strings : 0;
    int count = (i < last_strings) ? i : last_strings;
    for (int j = 0; j < count; j++) {
        int idx = (j + start) % last_strings;
        printf("%s", buffer[idx]);
    }
    for (int j = 0; j < count; j++) {
        int idx = (j + start) % last_strings;
        free(buffer[idx]);
    }

}