#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXLINE 1000
#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXLINE) val[sp++] = f;
    else printf("error: stack full\n");
}

double pop(void) {
    if (sp > 0) return val[--sp];
    printf("error: stack empty\n");
    return 0.0;
}

int getop(char s[]) {
    int c, i;
    static int buf = EOF;
    if (buf != EOF) {
        c = buf;
        buf = EOF;
    } else {
        c = getchar();
    }

    while (c == ' ' || c == '\t')
        c = getchar();
    s[0] = c;
    s[1] = '\0';
    if (c == '-') {
        int next = getchar();
        if (isdigit(next) || next == '.') {
            s[1] = next;
            i = 2;
            c = next;
        } else {
            buf = next;
            return '-';
        }
    } else {
        i = 0;
    }

    if (!isdigit(c) && c != '.') return c;

    if (isdigit(c)) {
        if (i == 0) i = 1;
        while (isdigit(c = getchar())) s[i++] = c;
    }

    if (c == '.') {
        s[i++] = c;
        while (isdigit(c = getchar())) s[i++] = c;
    }

    s[i] = '\0';
    buf = c;
    return NUMBER;
}

int main() {
    char line[MAXLINE];
    char s[MAXOP];
    int type, pos;
    double op2;

    while (get_line(line, MAXLINE) > 0) {
        pos = 0;
        while ((type = getop_line(s, line, &pos)) != '\0') {
            switch (type) {
                case NUMBER:
                    push(atof(s));
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0) push(pop() / op2);
                    else printf("error: division by zero\n");
                    break;
                case '\n':
                    printf("\t%.8g\n", pop());
                    break;
                default:
                    printf("error: unknown command %s\n", s);
                    break;
            }
        }
    }
}