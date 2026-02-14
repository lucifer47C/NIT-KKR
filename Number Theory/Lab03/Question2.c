#include <stdio.h>

int extendedGCD(int a, int b, int *s, int *t)
{
    int r1 = a, r2 = b;
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    while (r2 != 0) {
        int q = r1 / r2;

        int r = r1 - q * r2;
        r1 = r2;
        r2 = r;

        int s_temp = s1 - q * s2;
        s1 = s2;
        s2 = s_temp;

        int t_temp = t1 - q * t2;
        t1 = t2;
        t2 = t_temp;
    }

    *s = s1;
    *t = t1;
    return r1;
}

int modInverse(int a, int m)
{
    int s, t;
    int g = extendedGCD(a, m, &s, &t);

    if (g != 1)
        return -1;

    return (s % m + m) % m;
}

int modExp(int base, int exp, int mod)
{
    int result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int CRT(int a[], int mod[], int n)
{
    int N = 1;
    for (int i = 0; i < n; i++)
        N *= mod[i];

    int x = 0;
    for (int i = 0; i < n; i++) {
        int Ni = N / mod[i];
        int Mi = modInverse(Ni, mod[i]);
        x += a[i] * Ni * Mi;
    }

    x %= N;
    if (x < 0)
        x += N;

    return x;
}

int main()
{
    int a, n, p, q;

    printf("Enter a, n, p, q (n = p*q): ");
    scanf("%d %d %d %d", &a, &n, &p, &q);

    if (p * q != n) {
        printf("Error: n must be equal to p*q\n");
        return 1;
    }

    int sp = modExp(a, (p + 1) / 4, p);
    int sq = modExp(a, (q + 1) / 4, q);

    int a_vals[2], mod_vals[2];
    a_vals[0] = sp;
    a_vals[1] = sq;

    mod_vals[0] = p;
    mod_vals[1] = q;

    int root = CRT(a_vals, mod_vals, 2);

    printf("\nOne square root of %d modulo %d is:\n", a, n);
    printf("%d\n", root);

    return 0;
}
