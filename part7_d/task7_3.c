#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

void print_octal(unsigned int num) {
    char buf[32];
    int i = 0;
    if (num == 0) {
        putchar('0');
        return;
    }

    while (num > 0) {
        buf[i++] = '0' + (num % 8);
        num /= 8;
    }

    while (i-- > 0) {
        putchar(buf[i]);
    }
}

void print_hex(unsigned int num) {
    char *mas = "0123456789abcdef";
    char buf[32];
    int i = 0;
    if (num == 0) {
        putchar('0');
        return;
    }

    while (num > 0) {
        buf[i++] =  mas[num % 16];
        num /= 16;
    }

    while (i-- > 0) {
        putchar(buf[i]);
    }
}

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    int cval;
    unsigned int oval;
    unsigned int hval;
    void *pval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f",dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                if (sval == NULL) {
                    printf("error: no string\n");
                    break;
                }
                for (; *sval; sval++) putchar(*sval);
                break;
            case 'c':
                cval = va_arg(ap, int);
                printf("%c", (char)cval);
                break;
            case 'o':
                oval = va_arg(ap, unsigned int);
                print_octal(oval);
                break;
            case 'x':
                hval = va_arg(ap, unsigned int);
                print_hex(hval);
                break;
            case 'p':
                pval = va_arg(ap, void *);
                uintptr_t addr = (uintptr_t)pval;
                putchar('0');
                putchar('x');
                print_hex(addr);
                break;
            case '%':
                putchar('%');
                break;
            default: 
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}

int main() {
    char simb = 'v';
    unsigned int num = 26;
    //print_hex(num);
    //print_octal(8);
    //printf("%u", res);
    minprintf("Hello world char: %c, hex: %x", simb, num);
    return 0;
}
