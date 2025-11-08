#include <stdio.h>
#include <time.h>
#include <ctype.h>

#define N 100000

int binsearch(int x, int v[], int n) {
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else if (x > v[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int opt_binsearch(int x, int v[], int n) {
    int low, mid, high;
    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return (v[low] == x) ? low : -1;
}

void bubble_sort(int mas[], int n) {
    for (int i = 0; i < n; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (mas[j] > mas[j + 1]) {
                int temp = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    clock_t start, end;
    int result;
    int n;
    printf("Enter length: ");
    scanf("%d", &n);

    int v[n];
    for (int i = 0; i < n; i++) {
        printf("Enter %d num: ", i + 1);
        scanf("%d", &v[i]);
    }
    bubble_sort(v, n);
    for (int i = 0; i < n; i++) {
        printf("%d. %d\n", i + 1, v[i]);
    }
    start = clock();
    for (int i = 0; i < N; i++) {
        result = binsearch(i, v, n);
    }
    end = clock();
    printf("Standart binary search: %f сек\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    start = clock();
    for (int i = 0; i < N; i++) {
        result = opt_binsearch(i, v, n);
    }
    end = clock();
    printf("Single search binary search: %f сек\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}