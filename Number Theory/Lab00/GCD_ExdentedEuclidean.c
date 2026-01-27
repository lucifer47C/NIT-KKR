#include <stdio.h>

long long extended_gcd(long long a, long long b, long long *s, long long *t) 
{
    long long s1 = 1, s2 = 0;
    long long t1 = 0, t2 = 1;

    while (b != 0) {
        long long q = a / b;
        long long r = a % b;

        a = b;
        b = r;

        long long temp_s = s1 - q * s2;
        long long temp_t = t1 - q * t2;

        s1 = s2;
        t1 = t2;
        s2 = temp_s;
        t2 = temp_t;
    }

    *s = s1;
    *t = t1;
    return a;
}

int main() 
{
    long long a, b, s, t;
    scanf("%lld %lld", &a, &b);

    long long g = extended_gcd(a, b, &s, &t);

    printf("gcd = %lld\n", g);
    printf("s = %lld, t = %lld\n", s, t);
    printf("Check: %lld*%lld + %lld*%lld = %lld\n", a, s, b, t, a*s + b*t);
    if (g != 1)
        printf("Inverse does not exist\n");
    else
        printf("Inverse of %lld in Z%lld is: %lld\n", a, b, t);
        
    return 0;
}
