#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int atoi_p(char *s) {
    int n = 0;
    while (*s >= '0' && *s <= '9') {
        n = 10 * n + (*s - '0');
        s++;
    }
    return n;
}

void reverse_p(char *s, char *line) {
    size_t len = strlen(s);
    char *end = s + len - 1;
    while (len--) {
        *line++ = *end--;
    }
    *line = '\0';
}

int main() {
    char s[] = "hello";
    char line[100]; 
    reverse_p(s, line);
    printf("Rev: %s", line);

    char number[] = "123";
    int result = atoi_p(number);
    printf("result: %d", result);
    
    return 0;
}