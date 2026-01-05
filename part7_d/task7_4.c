#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

#define MAXSIZE 1000

static int buf = 0;

int getch(void) {
    int c;
    if (buf != 0) {
        c = buf; 
        buf = 0;
        return c;
    }
    return getchar();
}

void ungetch(int c) {
    buf = c;
}

int getint(int *pn) {
    int c, sign;
    while (isspace(c = getch()))
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') c = getch();

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * (*pn) + (c - '0');
    }

    *pn *= sign;

    if (c != EOF) ungetch(c);
    return 1;
}

int minscanf(char *fmt, ...) {
    va_list ap;
    int c, cnt = 0;
    char *p;
    int *ival;
    char *sval;
  
    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            if ((c = getch()) != *fmt) break;
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int *);
                if (getint(ival))
                    cnt++;
                else 
                    goto end;
                break;
            case 's': 
                sval = va_arg(ap, char *);
                while (isspace(c = getch()))
                    ;
                if (c == EOF) goto end;
                for (; !isspace(c) && c != EOF; c = getch()) {
                    *sval = c;
                    sval++;
                }
                *sval = '\0';
                cnt += 1;
                break;
            default:
                break;
        }
    }
end:
    va_end(ap);
    return cnt;
}

int main() {
    int dig;
    printf("Enter digit: ");
    minscanf("%d", &dig);
    printf("Entered digit: %d", dig);
    return 0;
}
