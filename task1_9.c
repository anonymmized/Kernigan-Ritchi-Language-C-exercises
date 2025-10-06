#include <stdio.h>

int main() {
    int c, p = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (!p) {
                putchar(' ');
                p = 1;
            }
        } else 
            putchar(c);
            p = 0;
    }
}