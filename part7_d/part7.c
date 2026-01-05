#include <stdio.h>

void filecopy(FILE *fin, FILE *fout) {
    int c;
    while ((c = getc(fin)) != EOF) putc(c, fout);
}

int main(int argc, char *argv[]) {
    FILE *fp;
    if (argc == 1) {
        filecopy(stdin, stdout);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("cat: cannot open file %s\n", *argv);
                return 1;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    return 0;
}
