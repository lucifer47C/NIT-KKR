#include <stdio.h>

long long modexp(long long a, long long e, long long p) {
    long long r = 1;
    a %= p;
    while (e) {
        if (e & 1) 
            r = (r * a) % p;
        a = (a * a) % p;
        e >>= 1;
    }
    return r;
}

long long legendre(long long a, long long p) {
    return modexp(a, (p - 1) / 2, p);
}

long long shanks(long long a, long long p) {
    if (legendre(a, p) != 1)
        return -1;  

    // Step 1: find n with (n/p) = -1
    long long n = 2;
    while (legendre(n, p) != p - 1)
        n++;

    // Step 2: p-1 = 2^e * q
    long long q = p - 1;
    int e = 0;
    while ((q & 1) == 0) {
        q >>= 1;
        e++;
    }

    // Step 3: initialization
    long long y = modexp(n, q, p);
    int r = e;
    long long x = modexp(a, (q - 1) / 2, p);
    long long b = (a * x % p * x) % p;
    x = (a * x) % p;

    // Step 4: loop
    while (b != 1) {
        int m;
        long long temp = b;
        for (m = 1; m < r; m++) {
            temp = (temp * temp) % p;
            if (temp == 1)
                break;
        }

        long long t = modexp(y, 1LL << (r - m - 1), p);
        y = (t * t) % p;
        r = m;
        x = (x * t) % p;
        b = (b * y) % p;
    }

    return x;
}

int main() {
    long long a, p;
    printf("Enter a and prime p: ");
    scanf("%lld %lld", &a, &p);

    long long root = shanks(a, p);

    if (root == -1) {
        printf("No square root exists modulo %lld\n", p);
    } else {
        printf("Square roots of %lld mod %lld are %lld and %lld\n",
               a, p, root, (p - root) % p);
    }

    return 0;
}
