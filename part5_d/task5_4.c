#include <string.h>
#include <stdio.h>

int strend(char *s, char *t) {
    int tt = strlen(t);
    int ss = strlen(s);
    if (tt > ss) return 0;
    s += ss - tt;
    while (*t) {
        if (*s++ != *t++) {
            return 0;
        }
    }
    return 1;
}
int main() {
    char s[] = "helloworld";
    char t[] = "world";
    int result = strend(s, t);
    printf("result: %d", result);
    return 0;
}