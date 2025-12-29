#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *s, int lim);

int pref_len;

int main(int argc, char *argv[]) {
    struct tnode *root = NULL;
    char word[MAXWORD];

    if (argc == 2) {
        pref_len = argv[1];
    } else {
        pref_len = 6;
    }
    while (getword(word, MAXWORD) != EOF) { 
        if (isalpha(word[0])) {
            root = addtree(root, word, pref_len);
        }
    }
    treeprint(root);
    return 0;
}

struct tnode *addtree(struct tnode *p, char *word, int n) {
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = my_strdup(word);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strncmp(word, p->word, n)) == 0) {
        p->count += 1;
    } else if (cond > 0) {
        p->right = addtree(p->rigth, word, n);
    } else {
        p->left = addtree(p->left, word, n);
    }
    return p;
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode *talloc(void) {
    return malloc(sizeof(struct tnode));
}

char *my_strdup(char *s) {
    char *p;
    p = malloc(sizeof(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}