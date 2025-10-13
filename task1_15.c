#include <stdio.h>

int to_cels(int upper, int step) {
    int lower = 0;
    int fahr, cels;
    fahr = lower;
    while (fahr <= upper) {
        cels = 5 * (fahr - 32) / 9;
        printf("%d\t%d\n", fahr, cels);
        fahr += step; 
    }
    return 0;
}

int main() {
    int upper, step;
    printf("Функция по переводу температур\n");
    printf("Введите верхнюю границу: ");
    scanf("%d", &upper);
    printf("Введите значение для шага: ");
    scanf("%d", &step);
    to_cels(upper, step);
}