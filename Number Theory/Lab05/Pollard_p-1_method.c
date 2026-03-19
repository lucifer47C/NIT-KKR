#include <stdio.h>
#include <math.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long power_mod(long long a, long long j, long long n) {
    long long res = 1;
    a %= n;

    while (j > 0) {
        if (j & 1)
            res = (res * a) % n;

        a = (a * a) % n;
        j >>= 1;
    }
    return res;
}

long long pollards_p1(long long n, int B) {
    long long a = 2;

    for (int j = 2; j <= B; j++) {
        a = power_mod(a, j, n);

        long long p = gcd(a - 1, n);

        if (p > 1 && p < n)
            return p;
    }

    return -1; 
}

int main() {
    long long n;
    int B = 10000;

    printf("Enter n: ");
    scanf("%lld", &n);

    long long factor = pollards_p1(n, B);

    if (factor == -1)
        printf("Factor not found. Increase B.\n");
    else
        printf("Non-trivial factor: %lld\n", factor);

    return 0;
}