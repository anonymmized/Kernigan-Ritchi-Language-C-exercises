#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

double atof(char *s) {
    double n = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            n = 10.0 * n + (s[i] - '0');
        }
    }
    return n;
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else 
        return 0;
}

int strcmp(char *s1, char *s2) {
    while (*s1 == *s2) {
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void qsort(void *v[], int left, int right, int rev, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right) return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (rev == 0) {
            if ((*comp)(v[i], v[left]) < 0) {
                swap(v, ++last, i);
            }
        } else if (rev == 1) {
            if ((*comp)(v[i], v[left]) > 0) {
                swap(v, ++last, i);
            }
        }
        
    }
    swap(v, left, last);
    qsort(v, left, last-1, comp);
    qsort(v, last, right+1, comp);
}



int main(int argc, char *argv[]) {
    int numeric = 0, rev = 0;
    int nlines;
    while (--argc && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    rev = 1;
                    break;
                case default:
                    printf("error: wrong argument: %c\n", c);
                    argc = 0;
                    break;
            }
        }
    }  
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void **) lineptr, 0, nlines - 1, rev, (int (*)(void*, void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Too many lines\n");
        return 1;
    }
}