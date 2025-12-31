#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 1000
#define HASHSIZE 101

struct nlist *lookup(char *s);
char *my_strdup(char *s);
unsigned hash(char *s);
int my_getline(char *line, int lim);
int parse_line(char *line);
struct nlist *install(char *name, char *defn);


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
    return hashval % HASHSIZE;
}

int my_getline(char *line, int lim) {
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        line[i++] = c;
    }
    if (c == '\n') {
        line[i++] = '\n';
    }
    line[i] = '\0';
    return i;
}

int check_define(char *line) {
    char name[MAXLINE];
    char defn[MAXLINE];
    if (strncmp(line, "#define", 7) != 0) {
        return 0;
    }
    if (sscanf(line + 7, "%s %[^\n]", name, defn) != 2) {
        return -1;
    }
    install(name, defn);
    printf("Installation was successful\n");
    printf("Installed name: %s\n", name);
    printf("Installed define: %s\n", defn);
    return 1;
}

int parse_line(char *line) {
    int i = 0;
    int res = check_define(line);
    if (res != 0) {
        return res < 0 ? -1 : 0;
    } 
    while (line[i] != '\0') {
        while (line[i] != '\0' && !isalnum(line[i])) i++;
        int start = i;
        while (line[i] != '\0' && isalnum(line[i])) i++;
        int len = i - start;
        if (len == 0) {
            i++;
            continue;
        }
        char *word = malloc(len + 1);
        if (word == NULL) return -1;
        strncpy(word, line + start, len);
        if (!word) return -1;
        unsigned hashval_w = hash(word);
        word[len] = '\0';
        printf("Hash: %u\n", hashval_w);
        free(word);
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
    return 0;
}