#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int buf = 0;
int in_buf = 0;

void ungetch(int c) {
    if (in_buf) {
        printf("Error: buffer is full");
    } else {
        buf = c;
        in_buf = 1;
    }
}

int getch(void) {
    if (in_buf) {
        in_buf = 0;
        return buf;
    } else {
        return getchar();
    }
}

int getint(int *pn) {
    int c, sign;
    while ((c = getch()) == ' ')
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }
    return 1;
}

int main() {
    int pn;
    getint(&pn);
    return 0;
}