#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int mgetline(char *line, int lim) {
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        line[i++] = c;
    }
    if (c == '\n') line[i++] = '\n';
    line[i] = '\0';
    return i;
}

int main(int argc, char *argv[]) {
    int found = 0, lineno = 0, except = 0, number = 0;
    char line[MAXLINE];

    if (argc < 2) {
        printf("Use: ./find [-x] [-n] pattern\n");
        return -1;
    }
    
    while (--argc > 0 && (*++argv)[0] == '-') {
        char *opt = *argv + 1;
        while (*opt) {
            switch(*opt++) {
                case 'n':
                    number = 1;
                    break;
                case 'x':
                    except = 1;
                    break;
                default:
                    printf("Wrong option\n");
                    return -1;
            }
        }
    }

    if (argc != 1) {
        printf("Use: ./find [-x] [-n] pattern\n");
        return -1;
    }
    while (mgetline(line, MAXLINE) > 0) {
        lineno++;
        int match = strstr(line, *argv) != NULL;
        if (match != except) {
            if (number) {
                printf("%d: ", lineno);
            }
            printf("%s", line);
            found++;
        }
    }
    return found;
}