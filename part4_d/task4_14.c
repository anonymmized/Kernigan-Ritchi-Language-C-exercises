#include <stdio.h>

#define swap(t, x, y) do { \
    t _tmp = (x);          \
    (x) = (y);             \
    (y) = _tmp;            \
} while (0)                \

int main() {
    int a = 10, b = 20;
    printf("A: %d\tB: %d\n", a, b);
    swap(int, a, b);
    printf("A: %d\tB: %d", a, b);
    return 0;
}