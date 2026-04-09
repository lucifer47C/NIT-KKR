#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long modInverse(long long e, long long phi) {
    long long t = 0, newt = 1;
    long long r = phi, newr = e;

    while (newr != 0) {
        long long q = r / newr;

        long long temp = newt;
        newt = t - q * newt;
        t = temp;

        temp = newr;
        newr = r - q * newr;
        r = temp;
    }

    if (t < 0) t += phi;
    return t;
}

long long modexp(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;

    while (exp) {
        if (exp & 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    long long p = 61, q = 53;  
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e = 17; 
    long long d = modInverse(e, phi);

    long long message = 65;

    long long cipher = modexp(message, e, n);
    long long decrypted = modexp(cipher, d, n);

    printf("Public Key (e, n): (%lld, %lld)\n", e, n);
    printf("Private Key (d, n): (%lld, %lld)\n", d, n);

    printf("Original Message: %lld\n", message);
    printf("Encrypted: %lld\n", cipher);
    printf("Decrypted: %lld\n", decrypted);

    return 0;
}