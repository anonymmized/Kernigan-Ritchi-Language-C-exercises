#include <stdio.h>
#include <stdlib.h>
#define TAB_SIZE 4
#define MAXLINE 1000

char* m_getline(int lim);

int main() {
    char *line;
    while ((line = m_getline(MAXLINE)) != NULL) {
        if (line[0] == '\0') {
            break;
        }
        printf("%s", line);
        free(line);
    }
    return 0;
}

char* m_getline(int lim) {
    int c, i;
    int a = 0, b = 0;
    char s[lim];
    int cnt_tabs = 0;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
        if (c == '\t') cnt_tabs += 1;
    }
    if (c == '\n') {
        s[i++] = '\n';
    }
    s[i] = '\0';  
    char *res = malloc(i + cnt_tabs * (TAB_SIZE - 1) + 1);
    if (!res) return NULL;
    while (s[a] != '\0') {
        if (s[a] == '\t') {
            for (int j = 0; j < TAB_SIZE; j++) {
                res[b++] = ' ';
            }
        } else {
            res[b++] = s[a];
        }
        a++;
    }
    res[b] = '\0';
    return res;
}