#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 1000

void my_printf(void) {
    int c;
    int len = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            printf("\\n\n");
            len = 0;
        } else if (c == '\t') {
            printf("\\t");
            len += 2;
        } else if (isprint((unsigned char)c)) {
            putchar(c);
            len += 1;
        } else {
            printf("\\%03o", (unsigned char)c);
            len += 4;
        }

        if (len >= MAXLINE) {
            putchar('\n');
            len = 0;
        }
    }
}

int main() {
    my_printf();
    return 0;
}
