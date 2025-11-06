// УЧИТЕСЬ ПОКА ЖИВ
#include <stdio.h>
#include <ctype.h>

int hexCharToInt(char c) {
    c = tolower(c);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

int htol(char *s) {
    int start = 0;
    int result = 0;
    if (s[0] == '0' && (s[1] == 'X' || s[1] == 'x')) start = 2;
    for (int i = start; s[i] != '\0'; i++) {
        int val = hexCharToInt(s[i]);
        if (val == -1) break;
        result = result * 16 + val;
    }
    return result;
}

int main() {
    char s[1000];
    printf("Enter hex-number: ");
    scanf("%s", s);
    int result = htol(s);
    printf("Result: %d", result);
    return 0;
}