#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long f(long long x, long long c, long long n) {
    return ((x * x) % n + c) % n;
}

long long pollards_rho(long long n) {

    if (n % 2 == 0)
        return 2;

    long long x = 2, y = 2, s = 1;
    long long c = 1;

    while (s == 1) {

        x = f(x, c, n);          // tortoise
        y = f(f(y, c, n), c, n); // hare

        s = gcd(llabs(x - y), n);

        if (s == n)
            return -1; // failure
    }

    return s;
}

int main() {

    long long n;
    printf("Enter number: ");
    scanf("%lld", &n);

    long long factor = pollards_rho(n);

    if (factor == -1)
        printf("Failure, try again\n");
    else
        printf("Non-trivial factor: %lld\n", factor);

    return 0;
}