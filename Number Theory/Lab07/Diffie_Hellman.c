#include <stdio.h>

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
    long long p = 23; 
    long long g = 5; 


    long long a = 6; 
    long long A = modexp(g, a, p);


    long long b = 15;
    long long B = modexp(g, b, p);

    
    long long keyA = modexp(B, a, p);
    long long keyB = modexp(A, b, p);

    printf("Public values: p=%lld, g=%lld\n", p, g);
    printf("User A sends: %lld\n", A);
    printf("User B sends: %lld\n", B);

    printf("Shared key (A): %lld\n", keyA);
    printf("Shared key (B): %lld\n", keyB);

    return 0;
}