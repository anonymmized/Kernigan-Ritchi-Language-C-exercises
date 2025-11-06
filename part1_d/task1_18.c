#include <stdio.h>
#define MAXLINE 1000

int norm_getline(char s[], int lim);

int main() {
    char line[MAXLINE];
    int len;
    while((len = norm_getline(line, MAXLINE)) > 0) {
        if (line[0] != '\0' && !(len == 1 && line[0] == '\n'))
            printf("%s", line);
    }
    return 0;
}

int norm_getline(char s[], int lim) {
    int a = 0, b = 0, in_space = 0;
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    while (s[a] != '\0') {
        if (s[a] == ' ' || s[a] == '\t') {
            if (!in_space) {
                s[b++] = ' ';
                in_space = 1;
            }
        } else {
            s[b++] = s[a];
            in_space = 0;
        }
        a++;
    }
    s[b] = '\0';
    return b;
}