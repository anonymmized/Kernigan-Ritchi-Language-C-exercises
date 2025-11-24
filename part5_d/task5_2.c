#include <ctype.h>
#include <stdio.h>

static int buf = 0;
int in_buf = 0;

int getch(void) {
    if (in_buf) {
        in_buf = 0;
        return buf;
    } else {
        return getchar();
    }
}

void ungetch(int c) {
    if (in_buf) {
        printf("error: buffer is full\n");
    } else { 
        in_buf = 1;
        buf = c;
    }
}

int getfloat(float *pn) {
    int c, sign;
    while ((c = getch()) == ' ')
        ;
    if (!isdigit(c) && c != EOF && c != '-' && c != '+' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+') {
        int c2 = getch();
        if (!isdigit(c2)) {
            ungetch(c2);
            ungetch(c);
            return 0;
        }
        c = c2;
    }
    for (*pn = 0.0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }
    
    if (c == '.') {
        c = getch();
        float power = 1.0;
        float fractional = 0.0;
        for (; isdigit(c); c = getch()) {
            fractional = 10 * fractional + (c - '0');
            power *= 10;
        }
        *pn += fractional / power;
    }
    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }
    return 1;
}