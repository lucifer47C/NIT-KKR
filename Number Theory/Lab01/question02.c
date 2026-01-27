#include <stdio.h>

int extended_gcd(int a, int b, int *s, int *t) 
{
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;

    while (b != 0) {
        int q = a / b;
        int r = a % b;

        a = b;
        b = r;

        int temp_s = s1 - q * s2;
        int temp_t = t1 - q * t2;

        s1 = s2;
        t1 = t2;
        s2 = temp_s;
        t2 = temp_t;
    }

    *s = s1;
    *t = t1;
    return a;
}

int main() {
    int a, x, b, N, nx;
    printf("For equation a.x = b(modN)\n");
    printf("Enter the value of a: ");
    scanf("%d", &a);

    printf("\nEnter the value of b: ");
    scanf("%d", &b);

    printf("\nEnter the value of N: ");
    scanf("%d", &N);

    int s, t;
    int g = extended_gcd(N, a, &s, &t);

    if (b % g != 0){
        printf("No solution exists\n");
        return 0;
    }

    int a1 = a / g;
    int b1 = b / g;
    int N1 = N / g;

    
    int inv = ((t % N1) + N1) % N1;
    x = (inv * b1) % N1;

    printf("Number of solutions = %d\n", g);
    printf("Solutions:\n");

    for (int i = 0; i < g; i++) {
        printf("x = %d\n", (x + i * N1) % N);
    }

    return 0;
}
