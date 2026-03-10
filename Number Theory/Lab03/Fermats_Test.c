#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long modexp(long long a, long long e, long long m) {
    long long result = 1;
    a = a % m;

    while (e > 0) {
        if (e & 1)
            result = (result * a) % m;
        a = (a * a) % m;
        e >>= 1;
    }
    return result;
}

int fermat_test(long long n, int k) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;

    for (int i = 0; i < k; i++) {
        long long a = 2 + (rand() % (n - 3));
        if (modexp(a, n - 1, n) != 1)
            return 0;  // composite
    }
    return 1;  // probably prime
}

int main() {
    srand(time(NULL));

    long long n;
    int k = 10;  

    printf("Enter a number: ");
    scanf("%lld", &n);

    if (fermat_test(n, k))
        printf("%lld is probably prime (Fermat test)\n", n);
    else
        printf("%lld is composite\n", n);

    return 0;
}
