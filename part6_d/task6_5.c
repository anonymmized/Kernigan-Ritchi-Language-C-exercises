#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXLINE 1000

struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);
char *my_strdup(char *s);
unsigned hash(char *s);
int my_getline(char *line, int lim);
int parse_line(char *line);
int undef(char *name);

int undef(char *name) {
    struct nlist *np, *prev;
    unsigned hashval = hash(name);

    prev = NULL;
    for (np = hashtab[hashval]; np != NULL; np = np->next) {
        if (strcmp(name, np->name) == 0) {
            if (prev == NULL) {
                hashtab[hashval] = np->next;
            } else {
                prev->next = np->next;
            }
            free(np->name);
            free(np->defn);
            free(np);
            return 0;
        }
        prev = np;
    }
    return -1;
}

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}

char *my_strdup(char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval;
}

int my_getline(char *line, int lim) {
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') line[i++] = c;
    if (c == '\n') {
        line[i++] = '\n';
    }
    line[i] = '\0';
    return i;
}

int parse_line(char *line) {
    int i = 0;
    while (line[i] != '\0') {
        while (line[i] != '\0' && !isalnum(line[i])) i++;
        int start = i;
        while (line[i] != '\0' && isalnum(line[i])) i++;
        int len = i - start;
        if (len == 0) continue;
        char *word = malloc(len + 1);
        if (word == NULL) return -1;
        strncpy(word, line + start, len);
        word[len] = '\0';
        printf("word's '%s' hash: %u\n", word, hash(word));
    }
    return 0;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = malloc(sizeof(*np));
        if (np == NULL || (np->name = my_strdup(name)) == NULL) return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }
    if ((np->defn = my_strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

int main() {
    char line[MAXLINE];
    while (my_getline(line, MAXLINE) > 1) {
        parse_line(line);
    }
}