#include <stdio.h>
#include <math.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int isPerfectPower(long long n) {
    for (int b = 2; b <= log2(n); b++) {
        long long a = pow(n, 1.0 / b);
        if (a > 1) {
            long long p = 1;
            for (int i = 0; i < b; i++) 
                p *= a;
            if (p == n) 
                return 1;
        }
    }
    return 0;
}

int multiplicativeOrder(long long n, int r) {
    if (gcd(n, r) != 1) 
        return 0;
    long long k = 1, cur = n % r;
    while (cur != 1) {
        cur = (cur * n) % r;
        k++;
        if (k > r) 
            return 0;
    }
    return k;
}

int findR(long long n) {
    double logn2 = pow(log2(n), 2);
    for (int r = 2; ; r++) {
        if (gcd(n, r) == 1 && multiplicativeOrder(n, r) > logn2)
            return r;
    }
}

void polyMul(long long *a, long long *b, long long *res, int r, long long n) {
    long long temp[r];
    for (int i = 0; i < r; i++) temp[i] = 0;

    for (int i = 0; i < r; i++)
        for (int j = 0; j < r; j++)
            temp[(i + j) % r] = (temp[(i + j) % r] + a[i] * b[j]) % n;

    for (int i = 0; i < r; i++) res[i] = temp[i];
}

void polyPow(long long *base, long long exp,
             long long *res, int r, long long n) {
    long long temp[r], cur[r];

    for (int i = 0; i < r; i++) {
        res[i] = (i == 0);
        cur[i] = base[i];
    }

    while (exp > 0) {
        if (exp & 1) {
            polyMul(res, cur, temp, r, n);
            for (int i = 0; i < r; i++) res[i] = temp[i];
        }
        polyMul(cur, cur, temp, r, n);
        for (int i = 0; i < r; i++) cur[i] = temp[i];
        exp >>= 1;
    }
}

int polyCheck(long long n, int a, int r) {
    long long base[r], lhs[r], rhs[r];

    for (int i = 0; i < r; i++) base[i] = 0;
    base[0] = a % n;
    base[1] = 1;

    polyPow(base, n, lhs, r, n);

    for (int i = 0; i < r; i++) rhs[i] = 0;
    rhs[0] = a % n;
    rhs[n % r] = 1;

    for (int i = 0; i < r; i++)
        if (lhs[i] != rhs[i]) return 0;

    return 1;
}

int aks(long long n) {
    if (isPerfectPower(n)) 
        return 0;
    printf("Passed 1\n");
    
    int r = findR(n);

    for (int a = 2; a <= r; a++) {
        long long g = gcd(a, n);
        if (g > 1 && g < n) return 0;
    }
    printf("Passed 2\n");

    if (n <= r) 
        return 1;
    printf("Passed 3\n");

    int limit = sqrt(r) * log2(n);
    for (int a = 1; a <= limit; a++)
        if (!polyCheck(n, a, r)) 
            return 0;

    return 1;
    printf("Passed 4\n");
}

int main() {
    long long n;
    scanf("%lld", &n);

    if (n <= 1) 
        printf("Neither Prime nor Composite\n");
    else
        printf("%s\n", aks(n) ? "Prime" : "Composite");
    return 0;
}