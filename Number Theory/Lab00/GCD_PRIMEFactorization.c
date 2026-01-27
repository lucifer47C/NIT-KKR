#include <stdio.h>

long long gcd_prime_factorization(long long a, long long b) 
{
    long long gcd = 1;
    long long i = 2;

    printf("Prime factors of first number:\n");
    long long temp_a = a;

    while (i * i <= temp_a) 
    {
        int count = 0;
        while (temp_a % i == 0) 
        {
            temp_a /= i;
            count++;
        }
        if (count > 0)
            printf("%lld^%d ", i, count);
        i++;
    }
    if (temp_a > 1)
        printf("%lld^1", temp_a);
    printf("\n");

    printf("Prime factors of second number:\n");
    long long temp_b = b;
    i = 2;

    while (i * i <= temp_b) 
    {
        int count = 0;
        while (temp_b % i == 0) 
        {
            temp_b /= i;
            count++;
        }
        if (count > 0)
            printf("%lld^%d ", i, count);
        i++;
    }
    if (temp_b > 1)
        printf("%lld^1", temp_b);
    printf("\n");


    i = 2;
    while (i * i <= a && i * i <= b) 
    {
        int count_a = 0, count_b = 0;

        while (a % i == 0) 
        {
            a /= i;
            count_a++;
        }

        while (b % i == 0) 
        {
            b /= i;
            count_b++;
        }

        int min_count = (count_a < count_b) ? count_a : count_b;

        for (int j = 0; j < min_count; j++)
            gcd *= i;

        i++;
    }

    if (a == b)
        gcd *= a;

    return gcd;
}

int main() 
{
    long long a, b;
    scanf("%lld %lld", &a, &b);

    printf("\nGCD = %lld\n",
           gcd_prime_factorization(a, b));

    return 0;
}
