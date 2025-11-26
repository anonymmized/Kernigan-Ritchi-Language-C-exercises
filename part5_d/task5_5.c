#include <stdio.h>

char* strncpy_(char *dest, char *src, size_t n) {
    char *p = dest;
    while (n-- && *src) {
        *dest++ = *src++;
    }
    return p;
}

char* strncat_(char *dest, char *src, size_t n) {
    char *p = dest;
    while (*dest) 
        dest++;
    while (n-- && *src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return p;
}

int strncmp_(char *dest, char *src, size_t n) {
    while (n--) {
        if (*dest != *src) return *dest - *src;
        if (*dest == '\0') return 0;
        dest++;
        src++;
    }
    return 0;
}

int main() {
    char dest[20] = "abcdefghi";
    char src[] = "abcasd";
    size_t n = 4;

    // strncpy_(dest, src, n);
    // strncat_(dest, src, n);
    int result = strncmp_(dest, src, n);

    printf("dest = %s\nres: %d", dest, result);
    return 0;
}