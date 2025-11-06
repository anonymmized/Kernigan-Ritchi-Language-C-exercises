#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000

int m_getline(char s[], int lim);
char* reverse(char s[], int lenght);


int main() {
    int len;
    char *rev_line;
    char line[MAXLINE];
    while ((len = m_getline(line, MAXLINE)) > 0) {
        rev_line = reverse(line, len);
        printf("%s", rev_line);
    }
    return 0;
}

int m_getline(char s[], int lim) {
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = '\n';
    }
    s[i] = '\0';
    return i;
}

char* reverse(char s[], int lenght) {
    char *line = malloc(sizeof(char) * (lenght + 1));
    for (int i = 0; i < lenght; i++) {
        line[i] = s[lenght - 1 - i];
    }
    line[lenght] = '\0';
    return line;
}