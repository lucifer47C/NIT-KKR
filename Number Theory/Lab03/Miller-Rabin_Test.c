#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long modexp(long long a, long long e, long long n) {
    long long r = 1;
    a %= n;

    while (e > 0) {
        if (e & 1)
            r = (r * a) % n;
        a = (a * a) % n;
        e >>= 1;
    }
    return r;
}

int miller_rabin(long long n, int k) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;

    long long m = n - 1;
    int s = 0;
    while ((m & 1) == 0) {
        m >>= 1;
        s++;
    }

    for (int i = 0; i < k; i++) {
        long long a = 2 + (rand() % (n - 3));
        long long b = modexp(a, m, n);

        if (b == 1 || b == n - 1)
            continue;

        int composite = 1;
        for (int r = 1; r < s; r++) {
            b = (b * b) % n;

            if (b == n - 1) {
                composite = 0;
                break;
            }
            if (b == 1)
                return 0;
        }

        if (composite)
            return 0;
    }
    return 1;
}

int main() {
    srand(time(NULL));

    long long n;
    int k = 10;

    printf("Enter n: ");
    scanf("%lld", &n);

    if (miller_rabin(n, k))
        printf("Probably Prime\n");
    else
        printf("Composite\n");

    return 0;
}
