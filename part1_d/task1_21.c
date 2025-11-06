#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define TAB_SIZE 4

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
    int c, i, cnt_spaces = 0;
    char s[lim];
    int a = 0, b = 0;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] ='\n';
    }
    s[i] = '\0';

    int space_count = 0;
    for (int k = 0; k < i; k++) {
        if (s[k] == ' ') space_count += 1;
    }

    char *res = malloc(i + space_count * (TAB_SIZE - 1) + 1);
    if (!res) return NULL;

    while (s[a] != '\0') {
        if (s[a] == ' ') {
            cnt_spaces++;
            if ((b + cnt_spaces) % TAB_SIZE == 0) {
                res[b++] = '\t';
                cnt_spaces = 0;
            }
        } else {
            while (cnt_spaces > 0) {
                res[b++] = ' ';
                cnt_spaces--;
            }
            res[b++] = s[a];
        }
        a++;
    }
    if (cnt_spaces > 0) {
        res[b++] = ' ';
        cnt_spaces--;
    }
    res[b] = '\0';
    return res;
}