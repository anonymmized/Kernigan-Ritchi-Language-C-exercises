#include <stdio.h>
#include <string.h>

void rec_itoa(int num, char *s, int *index) {
    if (num < 0) {
        s[(*index)++] = '-';
    }

    if (num / 10) {
        rec_itoa(num / 10, s, index);
    }

    s[(*index)++] = (num % 10) + '0';
}

int main() {
    int num = 123;
    char s[100];
    int index = 0;
    rec_itoa(num, s, &index);
    s[index] = '\0';
    printf(": %s", s);
    return 0;
}
