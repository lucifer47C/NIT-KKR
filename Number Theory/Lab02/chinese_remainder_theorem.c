#include <stdio.h>

int extendedGCD(int a, int b, int *s, int *t) {
    int r1 = a, r2 = b;
    int s1 = 0, s2 = 1;
    int t1 = 1, t2 = 0;

    while (r2 != 0) {
        int q = r1 / r2;

        int r = r1 - q * r2;
        r1 = r2; r2 = r;

        int s_temp = s1 - q * s2;
        s1 = s2; s2 = s_temp;

        int t_temp = t1 - q * t2;
        t1 = t2; t2 = t_temp;
    }

    *s = s1;
    *t = t1;

    return r1;
}

int modInverse(int a, int m) {
    int s, t;
    int gcd = extendedGCD(a, m, &s, &t);

    if (gcd != 1)
        return -1;

    return (t % m + m) % m;
}

int areCoprime(int mod[], int n) {
    int s, t;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (extendedGCD(mod[i], mod[j], &s, &t) != 1)
                return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    printf("Enter number of equations: ");
    scanf("%d", &n);

    int a[n], mod[n];

    printf("Enter a[i]:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter n[i] (pairwise coprime):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &mod[i]);

    if (!areCoprime(mod, n)) {
        printf("CRT not applicable: moduli are not pairwise coprime\n");
        return 0;
    }

    int N = 1;
    for (int i = 0; i < n; i++)
        N *= mod[i];

    int x = 0;
    for (int i = 0; i < n; i++) {
        int Ni = N / mod[i];
        int Mi = modInverse(Ni, mod[i]);

        if (Mi == -1) {
            printf("Modular inverse does not exist\n");
            return 0;
        }

        x += a[i] * Ni * Mi;
    }

    x = x % N;
    if (x < 0)
        x += N;

    printf("Solution: x = %d (mod %d)\n", x, N);

    return 0;
}
