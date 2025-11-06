#include <stdio.h>
#include <limits.h>

int main() {
    printf("signed int: from %d to %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: from 0 to %u\n", UINT_MAX);
    printf("signed long: from %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: from 0 to %lu\n", ULONG_MAX);
    printf("signed char: from %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("unsigned char: from 0 to %d\n", UCHAR_MAX);
    printf("signed short: from %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: from 0 to %d\n", USHRT_MAX);
    return 0;
}