#include "../c/ws2/ilrd_string.h" /* StrLen */
#include <ctype.h>  /* tolower */
#include <stdio.h> /* printf */
#include <assert.h> 


void RevLo(char *str)

int main()
{
    char word[] = "Do dA 9_$% OInk oiNk";
    printf("%s\n", word);
    RevLo(word);
    printf("%s\n", word);
    return 0;
}

void RevLo(char *str)
{
    char *s_head = NULL;
    char *s_tail = NULL;
    char tmp = 0;

    assert(str);

    s_head = str;
    s_tail = str + StrLen(str) - 1;

    while(s_head <= s_tail)
    {
        tmp = tolower(*s_tail);
        *s_tail = tolower(*s_head);
        *s_head = tmp;
        ++s_head;
        --s_tail;
    }
}


void TF(int num)
{

    size_t i = 1;
    int IsM3 = 0, IsM5 = 0;

    while(i < num)
    {
        IsM3 = (0 == i % 3);
        IsM5 = (0 == i % 5);
        if(IsM3 && IsM5)
        {
            printf("TF\n");
        }
        else if(IsM5)
        {
            printf("F\n");
        }
        else if(IsM3)
        {
            printf("T\n");
        }
        else
        {
            printf("%lu\n", i);
        }
        ++i;
    }


}
