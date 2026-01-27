#include <stdio.h>

long long euler_function(long long n) {
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

int main() {
    long long n;
    printf("Enter the n for phi(n): ");
    scanf("%lld", &n);

    printf("\nEuler Function phi(%lld) = %lld\n", n, euler_function(n));

    return 0;
}
