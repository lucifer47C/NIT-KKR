#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long euler_func(long long n) {
    long long result = n;

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result = result - result / i;
        }
    }

    if (n > 1)
        result = result - result / n;

    return result;
}

long long mod(long long a, long long exp, long long n) {
    

}

int main() {
    long long a, n;
    scanf("%lld %lld", &a, &n);

    if (gcd(a, n) != 1) {
        printf("Euler's theorem does NOT apply (gcd != 1)\n");
        return 0;
    }

    long long phi = euler_phi(n);
    long long value = mod(a, phi, n);

    printf("phi(%lld) = %lld\n", n, phi);
    printf("%lld^%lld mod %lld = %lld\n", a, phi, n, value);

    if (value == 1)
        printf("Euler's theorem VERIFIED\n");
    else
        printf("Something went wrong\n");

    return 0;
}
