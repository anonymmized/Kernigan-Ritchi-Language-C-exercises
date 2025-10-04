#include <stdio.h>

int main() {
    float cels, fahr;
    int step = 20, start = 300, end = 0;
    printf("Celsium\tFahrenheit\n");
    for (fahr = start; fahr >= end; fahr -= step) {
        cels = (5.0 / 9.0) * (fahr + 32);
        printf("%6.0f\t%9.3f\n", fahr, cels);
    }
}