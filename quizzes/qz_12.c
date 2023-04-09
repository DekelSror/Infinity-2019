#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*
Quiz #12 - reverse string by words
*/
void StrRev(char *str);

int main(void)
{
    char test[] = "Hello, my name is Inigo Montoya, you killed my father\
, prepare to die\0";

    char *word_start = test;
    char *word_end = test + 1;
    printf("%s\n", test);

    StrRev(test);

    while (*word_end)
    {
        while (' ' != *word_end)
        {
            ++word_end;

            if (!*word_end)
            {
                break;
            }
        }


        *word_end = 0;
        StrRev(word_start);
        *word_end = ' ';
        word_start = word_end;
        ++word_end;
    }

    printf("%s\n", test);

    return 0;
}

void StrRev(char *str)
{
    char *s_head = NULL;
    char *s_tail = NULL;
    char tmp = 0;

    assert(str);

    s_head = str;
    s_tail = str + strlen(str) - 1;

    while(s_head <= s_tail)
    {
        tmp = *s_tail;
        *s_tail = *s_head;
        *s_head = tmp;
        ++s_head;
        --s_tail;
    }
}
