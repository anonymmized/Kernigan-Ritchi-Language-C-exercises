#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000
#define MAXLINES 100

struct tword {
    char *word;
    int lines[MAXLINES];
    int nlines;
    struct tword *left;
    struct tword *right;
};

int line_number = 0;

int my_getline(char *, int);
struct tword *addtree(struct tword *, char *, int);
struct tword *talloc(void);
char *my_strdup(const char *);
void parse_line(char *, struct tword *);
void treeprint(struct tword *);

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

struct tword *addtree(struct tword *p, char *word, int line) {
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = my_strdup(word);
        p->lines[0] = line;
        p->nlines = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(word, p->word)) == 0) {
        if (p->nlines < MAXLINES) {
            p->lines[p->nlines++] = line;
        }
    } else if (cond < 0) {
        p->left = addtree(p->left, word, line);
    } else {
        p->right = addtree(p->right, word, line);
    }
}

void parse_line(char *line, struct tword **root) {
    int i = 0;
    while (line[i] != '\0') {
        while (line[i] != '\0' && !isalpha(line[i])) i++;

        int start = i;
        while (line[i] != '\0' && isalpha(line[i])) i++;
        int len = i - start;
        char *word = malloc(len + 1);
        if (word == NULL) {
            return;
        }

        strncpy(word, line + start, len);
        word[len] = '\0';
        *root = addtree(*root, word, line_number);
        free(word);
    }
}

void treeprint(struct tword *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%s:", p->word);
        for (int i = 0; i < p->nlines; i++)
            printf(" %d", p->lines[i]);
        printf("\n");
        treeprint(p->right);
    }
}

struct tword *talloc(void) {
    return malloc(struct tword);
}

char *my_strdup(char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

int main() {
    struct tword *root = NULL;
    char line[MAXLINE];

    while (my_getline(line, MAXLINE) > 0) {
        line_number++;
        parse_line(line, &root);
    }
    treeprint(root);
    return 0;
}