#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int sp = 0;
double val[MAXVAL];

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void clear_stack(void) {
    sp = 0;
}

void upper_elem(void) {
    if (sp > 0) {
        double top = val[sp - 1];
        printf("%g\n", top);
        push(top);
    } else {
        printf("error: stack empty\n");
    }
}

void double_elem(void) {
    if (sp > 0) {
        push(val[sp - 1]);
    } else {
        printf("error: stack empty\n");
    }
}

void switch_elems(void) {
    if (sp >= 2) {
        double a = pop();
        double b = pop();
        push(a);
        push(b);
    } else {
        printf("error: need at least 2 elements\n");
    }
}

int getop(char s[]) {
    int c, next, i = 0;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (c == '-') {
        next = getch();
        if (isdigit(next) || next == '.') { 
            s[i++] = c;  
            c = next;    
        } else {
            ungetch(next); 
            return '-';    
        }
    }

    if (!isdigit(c) && c != '.')
        return c;

    if (isdigit(c)) {
        s[i++] = c;
        while (isdigit(c = getch()))
            s[i++] = c;
    }

    if (c == '.') {
        s[i++] = c;
        while (isdigit(c = getch()))
            s[i++] = c;
    }

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

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
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: division by zero\n");
            break;

        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: division by zero\n");
            break;

        case 'd': 
            double_elem();
            break;

        case 'u': 
            upper_elem();
            break;

        case 's': 
            switch_elems();
            break;

        case 'c': 
            clear_stack();
            break;

        case '\n':
            printf("\t%.8g\n", pop());
            break;

        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}
