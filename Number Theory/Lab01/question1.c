#include <stdio.h>
#include <time.h>

int gcd_euclid(int a, int b, int *steps) {
    *steps = 0;
    while (b != 0) {
        (*steps)++;
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int gcd_binary(int a, int b, int *steps) {
    *steps = 0;
    int g = 1;

    if (a == 0) return b;
    if (b == 0) return a;

    while (((a | b) & 1) == 0) {
        a >>= 1;
        b >>= 1;
        g <<= 1;
        (*steps)++;
    }

    while (a != 0) {
        while ((a & 1) == 0) {
            a >>= 1;
            (*steps)++;
        }
        while ((b & 1) == 0) {
            b >>= 1;
            (*steps)++;
        }

        if (a >= b) {
            a = a - b;
        } else {
            b = b - a;
        }
        (*steps)++;
    }
    return b * g;
}

int main() {
    int a, b;
    printf("Enter values of a and b: ");
    scanf("%d %d", &a, &b);

    int steps1, steps2;
    clock_t start, end;
    double time1, time2;


    start = clock();
    int gcd1 = gcd_euclid(a, b, &steps1);
    end = clock();
    time1 = (double)(end - start) / CLOCKS_PER_SEC;


    start = clock();
    int gcd2 = gcd_binary(a, b, &steps2);
    end = clock();
    time2 = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nEuclidean Algorithm:");
    printf("\nGCD = %d", gcd1);
    printf("\nSteps = %d", steps1);
    printf("\nExecution Time = %lf seconds\n", time1);

    printf("\nBinary Euclidean Algorithm:");
    printf("\nGCD = %d", gcd2);
    printf("\nSteps = %d", steps2);
    printf("\nExecution Time = %lf seconds\n", time2);

    return 0;
}
