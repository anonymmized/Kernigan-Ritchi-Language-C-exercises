#include <stdio.h>

int main() {
    int c, nl = 0, nt = 0, np = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            ++nl;
        } else if (c == '\t') {
            ++nt;
        } else if (c == ' ') {
            ++np;
        }
    }
    printf("Lines: %1d\n", nl);
    printf("Tabs: %2d\n", nt);
    printf("Spaces: %d\n", np);
}