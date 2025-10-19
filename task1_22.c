#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define MAXWIDTH 40

char* m_getline(int lim);

int main() {
    char *line;
    while ((line = m_getline(MAXLINE)) != NULL) {
        if (line[0] == '\0') {
            free(line);
            break;
        }
        printf("%s", line);
        free(line);
    }
    return 0;
}

char* m_getline(int lim) {
    int c, i;
    char s[lim];
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = '\n';
    }
    s[i] = '\0';

    char *res = malloc(2 * lim);
    if (!res) return NULL;

    int start = 0;
    int last_space = -1;
    int cur_pos = 0;
    for (int j = 0; j < i; j++) {
        res[pos++] = s[j];
        if (s[j] == ' ' || s[j] == '\t') {
            last_space = pos - 1;
        }
        if ((pos - start) >= MAXWIDTH) {
            if (last_space != -1) {
                res[last_space] = '\n';
                start = last_space + 1;
                last_space = -1;
            } else {
                res[pos++] = '\n';
                start = pos;
                last_space = -1;
            }
        } 
    }
    res[pos] = '\0';
    return res;
}