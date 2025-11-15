#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getop(char []);
void push(double f);
double pop(void);

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) printf("ungetch: too many characters\n");
    else buf[bufp++] = c;
}

void push(double f) {
    if (sp < MAXVAL) val[sp++] = f;
    else printf("error: the stack is full, %g does not fit\n", f);
}

double pop(void) {
    if (sp > 0) return val[--sp];
    else {
        printf("error: the stack is empty\n");
        return 0.0;
    }
}

int getop(char s[]) {
    int c, i;
    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;
    if (c == '-') {
        int next = getch();
        if (isdigit(next) || next == '.') {
            s[0] = c;
            c = next;
            i = 1;
        } else {
            ungetch(next);
            return '-';
        }
    }
    if (!isdigit(c) && c != '.') return c;
    i = (i > 0) ? i : 0;
    if (isdigit(c)) {
        s[i++] = c;
        while (isdigit(c = getch()))
            s[i++] = c;
    }
    if (c == '.') {
        s[i++] = '.';
        while (isdigit(c = getch()))
            s[i++] = c;
    }
    s[i] = '\0';
    if (c != EOF) ungetch(c);
    return NUMBER;
}

int main() {
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
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
                if (op2 != 0.0) push(pop() );
                else printf("error: division by zero");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0) push(fmod(pop(), op2));
                else printf("error: division by zero");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown operation %s\n", s);
                break;
        }
    }
    return 0;
}