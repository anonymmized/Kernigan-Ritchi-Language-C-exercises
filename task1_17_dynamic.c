#include <stdio.h>
#include <stdlib.h>

char* m_getline(void) {
    int size = 10, c, i = 0;
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
    while (1) {
        char* line = m_getline();
        size_t len = 0;
        while (line[len]) {
            len++;
        }
        if (len > 80) {
            for (int i = 0; i < len; i++) {
                printf("%c", line[i]);
            }
            free(line);
        } 
    }
    return 0;
}