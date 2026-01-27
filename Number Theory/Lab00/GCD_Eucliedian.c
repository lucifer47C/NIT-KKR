#include <stdio.h>

long long gcd(long long a, long long b) 
{
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main()
{
    long long a, b;
    printf("\nEnter a and b: "); 
    scanf("%lld %lld", &a, &b);
    printf("GCD = %lld\n", gcd(a, b));
    return 0;
}
