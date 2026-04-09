#include <stdio.h>
#include <math.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int isSquare(long long x) {
    long long s = sqrt(x);
    return (s * s == x);
}

long long cfrac(long long n) {

    long long a0 = sqrt(n);
    if (a0 * a0 == n) return a0;

    long long m = 0, d = 1, a = a0;

    long long num1 = 1, num = a;
    long long den1 = 0, den = 1;

    for (int i = 0; i < 10000; i++) {

        m = d * a - m;
        d = (n - m * m) / d;
        a = (a0 + m) / d;

        long long num2 = num1;
        num1 = num;
        num = a * num1 + num2;

        long long den2 = den1;
        den1 = den;
        den = a * den1 + den2;

        long long x = num;
        long long y = (x * x) % n;

        if (isSquare(y)) {
            long long y_sqrt = sqrt(y);

            long long factor = gcd(x - y_sqrt, n);
            if (factor > 1 && factor < n)
                return factor;
        }
    }

    return -1; 
}

int main() {
    long long n;
    printf("Enter n: ");
    scanf("%lld", &n);

    long long factor = cfrac(n);

    if (factor == -1)
        printf("Factor not found\n");
    else
        printf("Factor: %lld\n", factor);

    return 0;
}