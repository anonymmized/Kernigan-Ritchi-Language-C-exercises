#include <string.h>
#include <stdio.h>

void reverse(char s[]) {
    int i, j, c;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int main() {
    char s[100] = "hello";
    reverse(s);
    printf("%s\n", s);
    return 0;
}