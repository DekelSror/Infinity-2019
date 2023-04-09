#include <stdlib.h> /* NULL, size_t, malloc, realloc, free */
#include <stdio.h> /* printf */
#include <assert.h>
#include "ilrd_string.h" /* StrLen, StrCat, StrDup, StrTok */

/*=============================================*/
/* WorkSheet 2 exercise 15                     */
/* Remove white spaces from a string           */
/* Make changes in place                       */
/* Dekel Sror */
/*=============================================*/
#define WHITES " \t"

void RmSpaces(char *str);

int main(void)
{
    char test[] = "    T\the \t\tquick     brown fox j  umps  o  v er th  e la   zy   do g  \t\t  ";
    char *t = StrDup(test);

    RmSpaces(t);
    printf("%s\n", t);
    free(t);

    return 0;
}

void RmSpaces(char *str)
{
    char *runner = NULL;
    size_t original_buffer = StrLen(str) + 1;
    size_t new_buffer = 0;

    assert(str);

    runner = StrTok(str, WHITES);
    *str = 0;

    while(runner)
    {
        new_buffer += StrLen(runner);
        str = StrCat(str, runner);
        str = StrCat(str, " ");
        runner = StrTok(NULL, WHITES);
    }

    str = (char*)realloc(str, original_buffer - new_buffer + 1);
}
