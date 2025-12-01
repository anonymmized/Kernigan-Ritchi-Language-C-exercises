#include <stdio.h>
#include <string.h>

#define MAXTAB 4

int detab(char *s, int tb_size) {
    int i = 0, pos = 0;
    while (s[i] != '\0') {
        if (s[i] == '\t') {
            int to_space = tb_size - (pos % tb_size);
            for (; to_space > 0; to_space--) s[j++] = ' ';
            pos += (tb_size - (pos % tb_size));
        } else {
            s[j++] = s[i];
            if (s[i] == '\n') pos = 0;
            else pos++;
        }
        i++;
    }
    s[j] = '\0';
    return j;
}


int entab(char *s, int tb_size) {
    int i = 0, j = 0, nb = 0, pos = 0;
    while (s[i] != '\0') {
        if (s[i] == ' ') {
            nb++;
            i++;
        } else {
            int to_tb = tb_size - (pos % tb_size);
            if (nb >= to_tb) {
                s[j++] = '\t';
                pos += to_tb;
                nb -= to_tb;
            }
            for (; nb > 0; nb--) {
                s[j++] = ' ';
                pos++;
            }
            s[j++] = s[i];
            if (s[i] == '\n') pos = 0;
            else pos += 1;
            i++;
        }
    }
    int to_tb = tb_size - (pos % tb_size);
    if (nb >= to_tb) {
        s[j++] = '\t';
        pos += to_tb;
        nb -= to_tb;
    }
    for (; nb > 0; nb--) {
        s[j++] = ' ';
        pos++;
    }
    s[j] = '\0';
    return j;
}

int atoi(char *s) {
    int n = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            n = 10 * n + (s[i] - '0');
        }
    }
    return n;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Too many arguments\n");
        return 1;
    }
    int tb_size = (argc < 2) ? MAXTAB : atoi(argv[1]);
    char s[] = "e   x     a         mple";
    printf("  %s\n", s);
    entab(s, tb_size);
    printf(": %s\n", s);
    return 0;
}