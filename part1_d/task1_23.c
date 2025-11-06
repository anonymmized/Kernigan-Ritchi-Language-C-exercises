#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000

int in_ml_comm = 0;

char* comm_getline(int lim);

int main() {
    char *line;
    while ((line = comm_getline(MAXLINE)) != NULL) {
        if (line[0] == '\0') {
            free(line);
            break;
        }
        printf("%s", line);
        free(line);
    }
    return 0;
}

char* comm_getline(int lim) {
    char s[lim];
    int c, i = 0;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = '\n';
    }
    s[i] = '\0';
    int ind = 0;
    int in_str = 0, in_char = 0, in_sl_comm = 0;
    char *res = malloc(lim);
    for (int i = 0; s[i] != '\0'; i++) {
        if (in_sl_comm) {
            if (s[i] == '\n') {
                in_sl_comm = 0;
                res[ind++] = s[i];
            }
            continue;
        }

        if (in_ml_comm) {
            if (s[i] == '*' && s[i + 1] == '/') {
                in_ml_comm = 0;
                ++i;
            }
            continue;
        }
        
        if (in_str) {
            res[ind++] = s[i];
            if (s[i] == '"' && s[i - 1] != '\\') {
                in_str = 0;
            }
            continue;
        }

        if (in_char) {
            res[ind++] = s[i]; 
            if (s[i] == '\'' && s[i - 1] != '\\') {
                in_char = 0;
            }
            continue;
        }

        if (s[i] == '"') {
            in_str = 1;
            res[ind++] = s[i];
            continue;
        }

        if (s[i] == '\'') {
            in_char = 1;
            res[ind++] = s[i];
            continue;
        }

        if (s[i] == '/' && s[i + 1] == '/') {
            in_sl_comm = 1;
            ++i;
            continue;
        }

        if (s[i] == '/' && s[i + 1] == '*') {
            in_ml_comm = 1;
            ++i;
            continue;
        } 

        res[ind++] = s[i];
    }
    res[ind] = '\0';
    return res;
}