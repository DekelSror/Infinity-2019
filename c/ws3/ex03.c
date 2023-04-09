#include <stdio.h> /* printf */
#include <stdlib.h> /* size_t, wchar_t, div_t */

/*========================================================================*/
/* WorkSheet 3 exercise 3 -                                               */
/* Print out the data types' names and sizes                              */
/*                                                                        */
/* Dekel Sror */
/*========================================================================*/

void TypesList(void)
{
    printf("Basic C types\n\n");
    printf("char:   \t%lu bytes\n", sizeof(char));
    printf("short:  \t%lu bytes\n", sizeof(short));
    printf("int:    \t%lu bytes\n", sizeof(int));
    printf("long:   \t%lu bytes\n", sizeof(long));
    printf("float:  \t%lu bytes\n", sizeof(float));
    printf("double: \t%lu bytes\n", sizeof(double));
    printf("pointer:\t%lu bytes\n\n", sizeof(void*));

    printf("Stadard library types\n\n");
    printf("size_t: \t%lu bytes\n", sizeof(size_t));
    printf("wchar_t:\t%lu bytes\n", sizeof(wchar_t));
    printf("div_t:  \t%lu bytes\n", sizeof(div_t));
}


int main(void)
{
    TypesList();

    return 0;
}
