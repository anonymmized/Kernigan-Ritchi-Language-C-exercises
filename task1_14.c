#include <stdio.h>

int main() {
    int c;
    int mas[256] = {0};
    int cnt = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            break;
        }
        mas[(unsigned char)c]++;
    }
    for (int i = 0; i < 256; i++) {
        if (mas[i] > 0){
            printf("%c - %d ", i, mas[i]);
        }
    }
}