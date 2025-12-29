#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

char buf[100];
int bufp = 0;

int getch(void);
void ungetch(int);

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= 100) {
        printf("ungetch: error\n");
    } else {
        buf[bufp++] = c;
    }
}

void skip_line(void) {
    int c;
    while ((c = getch()) != EOF && c != '\n') 
        ;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;
    while (isspace(c = getch())) 
        ;
    if (c != EOF) {
        *w++ = c;
    }
    if (c == '#' || c == '"') {
        skip_line();
        return getword(word, lim);
    }
    if (c == '/') {
        int d;
        if ((d = getch()) == '/' || d == '*') {
            skip_line();
            return getword(word, lim);
        } else {
            ungetch(d);
        }
    }
    for (; --lim; w++) {
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

int main() {
    char word[MAXLINE];
    int c;
    while ((c = getword(word, MAXLINE)) > 0) {
        printf("%s\n", word);
    }
    return 0;
}