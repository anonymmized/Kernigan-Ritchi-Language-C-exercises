#include <stdio.h>

#define MAXLINE 1000
#define MAXLINES 100

char lines[MAXLINES][MAXLINE];
int liner = 0;

void tail(int n) {
    int start = liner > n ? liner - n : 0;
    for (int i = start; i < liner; i++) {
        printf("%s", lines[i]);   // \n уже есть в строке
    }
}

int mgetline(char *line, int lim) {
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return i;
}

int my_atoi(char *s) {
    int n = 0;
    for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++)
        n = 10 * n + (s[i] - '0');
    return n;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: %s n\n", argv[0]);
        return 1;
    }

    int n = my_atoi(argv[1]);

    while (liner < MAXLINES && mgetline(lines[liner], MAXLINE) > 0)
        liner++;

    tail(n);
    return 0;
}
    