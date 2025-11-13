#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
    int i, j, c;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itob(int n, char s[], int b) {
    char dict_16[17] = "0123456789ABCDEF";
    int i = 0, is_negative = 0, temp = n;
    if (n < 0) {
        is_negative = 1;
        temp = -temp;
    }
    do {
        s[i++] = dict_16[temp % b];
    } while ((temp /= b) > 0);
    if (is_negative) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main() {
    int n = 27;
    int b = 16;
    char s[100];
    printf("digit: %d\nbase: %d\n", n, b);
    itob(n, s, b);
    printf("string: %s\n", s);
    return 0;
}