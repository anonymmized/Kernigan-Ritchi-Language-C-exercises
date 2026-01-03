#include <stdio.h>
#include <string.h>
#include <ctype.h>

int my_printf(void) {
    int c, len = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            printf("\\n\n");
            len = 0;
        } else if (c == '\t') {
            printf("\\t\t");
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
    return 0;
}

int main() {
    my_printf();
    return 0;
}
