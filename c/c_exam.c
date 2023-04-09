/*
Dekel Sror

c language exam - question 1
Flip the digits of a integer

extra - base sensitive

O(log(n))
*/

#include <stdio.h> /* printf */

static int FlipInt(int num, int base);

int main(void)
{
    printf("%x\n",FlipInt(0xabcd, 16));
    printf("%o\n",FlipInt(006453, 8));

    printf("%d\n",FlipInt(-12345, 10));
    printf("%d\n",FlipInt(80818, 10));
    printf("%d\n",FlipInt(-9898945, 10));
    printf("%d\n",FlipInt(0, 10));

    return 0;
}


static int FlipInt(int num, int base)
{
    int result = 0;

    while (num)
    {
        result *=base;
        result += (num % base);
        num /= base;
    }

    return result;
}
