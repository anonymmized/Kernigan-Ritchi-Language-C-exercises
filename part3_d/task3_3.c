#include <stdio.h>
#include <string.h>
#include <ctype.h>

void expand(const char s1[], char s2[]) {
    int idx = 0;
    for (int i = 0; i < strlen(s1) - 2; i++) {
        if (((s1[i] >= 'a' && s1[i] <= 'z') && (s1[i + 1] == '-') && (s1[i + 2] >= 'a' && s1[i + 2] <= 'z')) || ((s1[i] >= 'A' && s1[i] <= 'Z') && (s1[i + 1] == '-') && (s1[i + 2] >= 'A' && s1[i + 2] <= 'Z'))) {
            if (s1[i] < s1[i + 2]) {
                for (int j = 0; j <= s1[i+2] - s1[i]; j++) {
                    s2[idx++] = s1[i] + j;
                }
                i += 2;
                continue;
            }
        } 
        else if (isdigit(s1[i]) && s1[i + 1] == '-' && isdigit(s1[i + 2])) {
            if ((s1[i] - '0') < (s1[i + 2] - '0')) {
                for (int j = 0; j <= (s1[i + 2] - '0') - (s1[i] - '0'); j++) {
                    s2[idx++] = s1[i] + j;
                }
                i += 2;
                continue;
            }
        }
        s2[idx++] = s1[i];
    }
    s2[idx] = '\0';
}

int main() {
    char s1[] = "";
    char s2[100];
    expand(s1, s2);
    for (int i = 0; i < strlen(s2); i++) {
        printf("%c", s2[i]);
    }
    return 0;
}
