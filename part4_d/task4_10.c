#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 1000
#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL) val[sp++] = f;
    else printf("error: stack full\n");
}

double pop(void) {
    if (sp > 0) return val[--sp];
    printf("error: stack empty\n");
    return 0.0;
}

int get_line(char s[], int lim) { 
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') 
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}

int getop_line(char s[], char line[], int *pos) {
    int i = 0;
    char c;

    while ((c = line[*pos]) == ' ' || c == '\t')
        (*pos)++;

    s[0] = c;
    s[1] = '\0';

    if (c == '\0') return '\0';

    (*pos)++;

    if (!isdigit(c) && c != '.') return c;

    i = (i > 0) ? i : 0;
    if (isdigit(c)) {
        while (isdigit(s[i++] = line[*pos])) 
            (*pos)++;
    }

    if (line[*pos] == '.') {
        s[i++] = line[*pos];
        (*pos)++;
        while (isdigit(s[i++] = line[*pos])) 
            (*pos)++;
    }

    s[i] = '\0';
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