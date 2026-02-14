#include <stdio.h>

int main() {
    int a, p;
    int found = 0;

    printf("Enter a and prime p: ");
    scanf("%d %d", &a, &p);

    a = a % p;

    for (int i = 0; i < p; i++) {
        if ((i * i) % p == a) {
            printf("Square root of %d mod %d is %d\n", a, p, i);
            printf("Other root is %d\n", (p - i) % p);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No square root exists modulo %d\n", p);
    }

    return 0;
}