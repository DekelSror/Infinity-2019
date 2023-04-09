#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* strlen  */

/*========================================================================*/
/* Quiz #5                                                                */
/* IsStrRotation                                                          */
/* in-place                                                               */
/* Dekel Sror */
/*========================================================================*/

int IsStrRotation(const char *s1, const char * s2);

int main(void)
{
    char s_num1[] = "121234";
    char s_num2[] = "123412";
    printf("%s\n%s\nIsStrRotation: %d\n", s_num1, s_num2, IsStrRotation(s_num1, s_num2));
    return 0;
}


int IsStrRotation(const char *s1, const char * s2)
{
    const char *ps1 = NULL, *ps2 = NULL;
    size_t offset = 0, start = 0;

    ps1 = s1; ps2 = s2;

    if(strlen(ps1) != strlen(ps2))
    {
        return 0;
    }

    while(*ps1)
    {

        while(*ps1 != *ps2)
        {
            ++start;
            ++ps2;
        }

        while(*ps1 == *ps2)
        {
            ++ps1; ++ps2;

            if(!*ps1)
            {
                return 1;
            }

            if(!*ps2)
            {
                ps2 = s2;
            }
        }

        if(ps2 >= s2 + strlen(s2) - offset)
        {
            return 0;
        }

        else
        {
            ++offset;
            ps1 = s1;
            ps2 = s2 + offset;
        }
    }

    return 0;
}
