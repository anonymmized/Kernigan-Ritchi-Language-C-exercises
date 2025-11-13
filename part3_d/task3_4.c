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

void itoa(char s[], int n) {
    long long temp = n;
    int is_negative = 0;
    int i = 0;
    if (temp < 0) {
        is_negative = 1;
        temp = -temp;
    }
    do {
        s[i++] = temp % 10 + '0';
    } while ((temp /= 10) > 0);
    if (is_negative) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main() {
    int n = -123542;
    char s[100];
    printf("%d\n", n);
    itoa(s, n);
    printf("'%s'\n", s);
    return 0;
}