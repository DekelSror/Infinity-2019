
#include <stdio.h>

#define SIZEOF_VAR(x)  ((unsigned char *)(&x + 1) - (unsigned char *)(&x))
#define MAX2(a, b)     ((a) > (b) ? (a) : (b))
#define SIZEOF_TYPE(t) ((unsigned int *)((t *)0 + 1))
#define MAX3(a, b, c)  (MAX2(MAX2(a,b), (c)))


typedef short(*smalla)(int, char *);




int main(void)
{
    int test[] = { 1, 6, 426004 };
    smalla my_smalla = 0;

    printf("%ld\n", MAX3(16, 5, 20));
    printf("%ld\n", MAX3(1460, 1000, -2000));
    printf("%ld\n", MAX3(1460, 10000, 200));
    printf("%lu\n", SIZEOF_VAR(test[2]));

    printf("%lu\n", SIZEOF_TYPE(short));




    return 0;
}
