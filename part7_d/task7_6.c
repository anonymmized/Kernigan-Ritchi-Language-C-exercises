#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000

char *rem_tab(char *line) {
    char *p = line;
    while (*p == ' ' || *p == '\t')
        p++;
    return p;
}

int main(int argc, char *argv[]) {
    char fp1l[MAXLINE], fp2l[MAXLINE];
    FILE *fp1, *fp2;
    if (argc < 2) {
        printf("need 2 files\n");
        return 1;
    }
    fp1 = fopen(*++argv, "r");
    if (fp1 == NULL) {
        printf("fp1: error with opening\n");
        return 1;
    }
    fp2 = fopen(*++argv, "r");
    if (fp2 == NULL) {
        printf("fp2: error with opening\n");
        fclose(fp1);
        return 1;
    }

    while ((fgets(fp1l, MAXLINE, fp1)) && (fgets(fp2l, MAXLINE, fp2))) {
        if (strcmp(fp1l, fp2l) != 0) {
            printf("strings not compare:\n");
            printf("fp1-line: %s", rem_tab(fp1l));
            printf("fp2-line: %s", rem_tab(fp2l));
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
