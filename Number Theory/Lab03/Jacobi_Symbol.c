#include <stdio.h>

int jacobi(int a, int n) {
    if (a == 0)
        return (n == 1) ? 1 : 0;
    if (a == 1)
        return 1;

    if (a < 0)
        return jacobi(-a, n) * ((n % 4 == 1) ? 1 : -1);
    if (a >= n)
        return jacobi(a % n, n);

    if (a % 2 == 0) {
        int sign = ((n * n - 1) / 8) % 2 == 0 ? 1 : -1;
        return sign * jacobi(a / 2, n);
    }

    int sign = ((a - 1) * (n - 1) / 4) % 2 == 0 ? 1 : -1;
    return sign * jacobi(n % a, a);
}

int main() {
    int a, n;

    printf("Enter a and n (n must be odd): ");
    scanf("%d %d", &a, &n);

    if (n <= 0 || n % 2 == 0) {
        printf("n must be a positive odd integer.\n");
        return 1;
    }

    printf("Jacobi symbol (%d/%d) = %d\n", a, n, jacobi(a, n));
    return 0;
}
