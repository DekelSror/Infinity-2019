/*==============================================================================
System Programming - Simple WatchDog
shell command executor
Dekel Sror
==============================================================================*/
#include <stdio.h>  /* printf */
#include <string.h> /* memcmp */

#define EXIT_CMD ("!!")

static int IsExitCmd(const char *str);

int main(void)
{
    static char input_buffer[0x100u] = { 0 };
    int err_system = 0;

    printf("type %s to exit\n", EXIT_CMD);

    while (!IsExitCmd(input_buffer))
    {
        scanf("%s", input_buffer);

        err_system = system(input_buffer);

        if (-1 == err_system)
        {
            printf("error when executing command - %d\n", err_system);

            break;
        }
    }

    return 0;
}

static int IsExitCmd(const char *str)
{
    if (0 == memcmp(str, EXIT_CMD, 2))
    {
        return 1;
    }

    return 0;
}
