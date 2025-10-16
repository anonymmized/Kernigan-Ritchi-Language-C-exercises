#include <stdio.h>
#include <stdlib.h>

char* dynamic_getline(void) {
    int c, size = 10, i = 0;
    char* buffer = malloc(size);
    if (!buffer) {
        return NULL;
    }
    while ((c = getchar()) != EOF && c != '\n') {
        if (i + 1 >= size) {
            size *= 2;
            char* temp = realloc(buffer, size);
            if (!temp) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
        buffer[i++] = (char)c;
    }
    if (c == '\n') {
        if (i + 1 >= size) {
            char* temp = realloc(buffer, size + 1);
            if (!temp) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
        buffer[i++] = '\n';
    }
    buffer[i] = '\0';
    return buffer;
}
int main() {
    char* longest = NULL;
    size_t max_len = 0;
    while (1) {
        size_t len = 0;
        char* line = dynamic_getline();
        while (line[len]) {
            len++;
        }
        if (len > max_len) {
            max_len = len;
            longest = line;
        } else {
            free(line);
        }
    }
    if (longest) {
        printf("Longest line:\n%s", longest);
        free(longest);
    }
    return 0;
}