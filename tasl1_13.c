#include <stdio.h>

int main() {
    int words[10];
    int c;
    int length = 0, cnt = 0;
    while (cnt < 10 && (c = getchar()) != EOF) {
        if (c != '\n' && c != ' ' && c != '\t') {
            length++;
        } else if (length != 0) {
            words[cnt++] = length;
            length = 0;
        }
    }
    if (length > 0 && cnt < 10) { 
        words[cnt++] = length;
    }
    for (int i = 0; i < 10; ++i) {
        printf("--------------------------------\n");
        printf("%2d. ", i + 1);
        for (int a = 0; a < words[i]; a++) {
            printf("#");
        }
        printf("\n");
    }
}