#include <stdio.h>

int legendre(int a, int p)
{
    
    if (a == 0)
        return 0;
    if (a == 1)
        return 1;
  
    a = a % p;
    if (a < 0)
        a += p;

    if (a % 2 == 0)
    {
        int sign;
        if (p % 8 == 1 || p % 8 == 7)
            sign = 1;
        else
            sign = -1;

        return sign * legendre(a / 2, p);
    }

    int sign = 1;
    if ((a % 4 == 3) && (p % 4 == 3))
        sign = -1;

    return sign * legendre(p % a, a);
}

int main()
{
    int a, p;

    printf("Enter a and prime p: ");
    scanf("%d %d", &a, &p);

    int result = legendre(a, p);

    printf("Legendre symbol (%d/%d) = %d\n", a, p, result);

    return 0;
}
