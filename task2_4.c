#include <stdio.h>

void squeeze(char s1[], char s2[]) {
    int i, j, k;
    for (i = j = 0; s1[i] != '\0'; i++) {
        int found = 0;
        for (k = 0; s2[k] != '\0'; k++) {
            if (s1[i] == s2[k]) {
                found = 2;
                break;
            }
        }
        if (!found) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}

int main() {
    char s1[1000];
    char s2[1000];
    printf("Enter s1: ");
    scanf("%999s", s1);
    printf("Enter s2: ");
    scanf("%999s", s2);
    squeeze(s1, s2);
    printf("%s", s1);
}