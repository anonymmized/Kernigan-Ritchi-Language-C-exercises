#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int lim);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

int get_line(char s[], int lim) {
    int i = 0, c;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c != '\n') {
        s[i++] = '\n';
    }
    s[i] = '\0';
    return i;
}

int strindex(char s[], char t[]) {
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && t[k] == s[j]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0') {
            return i;
        }
    }
    return -1;
}

int main() {
    char line[MAXLINE];
    int found = 0;
    while (get_line(line, MAXLINE) > 0) {
        if (strindex(line, pattern) >= 0) {
            printf("%s\n", line);
            found += 1;
        }
    }
    return found;
}