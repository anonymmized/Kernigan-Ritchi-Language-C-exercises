#include <stdio.h>

int main() {
    float fahr;
    int lower, upper, step, cels;
    cels = 0;
    upper = 10;
    step = 1;
    printf("Celsium\tFahrenheit\n");
    while (cels <= upper) {
        fahr = ((9.0 / 5.0) * cels) + 32;
        printf("%5d\t%8.1f\n", cels, fahr);
        cels = cels + step;
    }
}