#include <stdlib.h> /* NULL, size_t */
#include <stdio.h> /* printf */

/*===============================================================*/
/* WorkSheet 3 exercise 1 -                                      */
/* Implement the Josephus problem on n 'soldiers' using an array */
/* Return array index of survivor                                */
/* Dekel Sror */
/*===============================================================*/


size_t Flavius(size_t participants[], size_t knights)
{

    size_t i = 0;
    size_t *sword_guy = NULL, *next_kill = NULL;

/* initial target assignements */
    for (i = 0; i < knights; ++i)
    {
        participants[i] = (i + 1) % knights;
    }
/* initial active knights */
    sword_guy = &participants[0];
    next_kill = &(participants[*sword_guy]);

    while (*next_kill != *sword_guy)
    {
        *sword_guy = *next_kill;
        sword_guy = &(participants[*sword_guy]);
        next_kill = &(participants[*sword_guy]);
    }

    return *next_kill;
}


int main(void)
{
    size_t t1[31] = { 0 };
    size_t t2[32] = { 0 };
    size_t t3[33] = { 0 };

    printf("\n%lu\n", Flavius(t1, 31));
    printf("\n%lu\n", Flavius(t2, 32));
    printf("\n%lu\n", Flavius(t3, 33));

    return 0;
}
