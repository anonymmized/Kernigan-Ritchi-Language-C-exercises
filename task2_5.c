#include <stdio.h>

int any(char s1[], char s2[]) {
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }
    return -1;
}

int main() {
    char s1[1000];
    char s2[1000];
    printf("Enter s1: ");
    scanf("%999s", s1);
    printf("Enter s2: ");
    scanf("%999s", s2);
    int result = any(s1, s2);
    if (result != -1) {
        printf("Index of matching characters: %d", result);
    } else {
        printf("No matching characters");
    }
    return 0;
}