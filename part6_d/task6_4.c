#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000
#define PRIME 101
#define MAXWORDS 101

struct tword {
    char *word;
    int count;
};

struct tword *words[MAXWORDS];
int words_index = 0;

int my_getline(char *line, int lim) {
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        line[i++] = c;
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

void add_word(char *s) {
    for (int i = 0; i < words_index; i++) {
        if (words[i] != NULL && strcmp(words[i]->word, s) == 0) {
            words[i]->count++;
            free(s);
            return;
        }
    }

    struct tword *p = malloc(sizeof(struct tword));
    if (p == NULL) {
        free(s);
        return;
    }
    p->word = s;
    p->count = 1;
    words[words_index++] = p;
}

int parse_line(char *line) {
    int i = 0;
    while (line[i] != '\0') {
        while (line[i] != '\0' && !isalnum(line[i])) i++;
        int start = i;
        while (line[i] != '\0' && isalnum(line[i])) i++;
        int len = i - start;
        if (len == 0) {
            continue;
        }
        char *word = malloc(len + 1);
        if (word == NULL) return -1;
        strncpy(word, line + start, len);
        word[len] = '\0';
        add_word(word);
    }
    return 0;
}

void to_sort(void) {
    for (int i = 0; i < words_index; i++) {
        for (int j = 0; j < words_index - 1 - i; j++) {
            if (words[j]->count > words[j + 1]->count) {
                struct tword *temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

int main() {
    char line[MAXLINE];
    int len;
    while ((len = my_getline(line, MAXLINE)) > 1) {
        parse_line(line);
    }
    to_sort();
    for (int i = 0; i < words_index; i++) {
        struct tword *p = words[i];
        printf("%s - %d\n", p->word, p->count);    
    }
    return 0;
}