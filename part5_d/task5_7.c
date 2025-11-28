#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines, char *bufp, int bufsize);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int readlines(char *lineptr[], int maxlines, char *bufp, int bufsize) {
    int len;
    int nlines = 0;
    char line[MAXLEN];
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (bufp + len > buf + bufsize) return -1;
        line[len - 1] = '\0';
        strcpy(bufp, line);
        lineptr[nlines++] = bufp;
        bufp += len;
    }
    return nlines;
}

int get_line(char line[], int MAXLEN) {
    int c, i;
    for (i = 0; i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i++] = '\n';
    }
    line[i] = '\0';
    return i;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(char *v[], int left, int right) {
    int i, last;
    if (left >= right) return;
    swap(v, left, (right + left) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

int main() {
    int nlines;
    char bigbuf[10000];
    char *bufp = bigbuf;
    if ((nlines = readlines(lineptr, MAXLINES, bufp, 10000)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
    }
}