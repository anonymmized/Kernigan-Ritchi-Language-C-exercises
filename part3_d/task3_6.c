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

void itoa(int n, char s[], int width) {
    int is_negative = 0;
    long long temp = n;
    int i = 0;
    if (n < 0) {
        is_negative = 1;
        temp = -temp;
    }

    do {
        s[i++] = temp % 10 + '0';
    } while ((temp /= 10) > 0);
    
    if (is_negative) s[i++] = '-';
    s[i] = '\0';
    reverse(s);

    int len = strlen(s);
    if (len < width) {
        int pad = width - pad;
        for (int i = len; i >= 0; i--) {
            s[i + pad] = s[i];
        }

        for (int i = 0; i < pad; i++) {
            s[i] = ' ';
        }
    }
}

int main() {
    int n = 123;
    int width = 5;
    char s[100];
    printf("digit: %d\nwidth: %d\n", n, width);
    itoa(n, s, width);
    printf("string: %s\n", s);
    return 0;
}