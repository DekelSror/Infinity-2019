/*==============================================================================
System Programming - Simple WatchDog
fork / exec and system
Dekel Sror
==============================================================================*/
#include <stdio.h>      /* printf       */
#include <sys/types.h>  /* pid_t        */
#include <sys/wait.h>   /* waitpid      */
#include <unistd.h>     /* fork, execvp */
#include <stdlib.h>     /* system       */

int main(void)
{
    int child_status = 0;
    static char *child_args[] = { "./app.out",  "hi. I am child", NULL };

    printf("exit with ctrl + c\n\n\n");

    while (1)
    {
        pid_t test = fork();
        /* error */
        if (0 > test)
        {
            printf("error! find out how to get more info\n");
            break;
        }
        /* child */
        if (0 == test)
        {
            int err_exec = execvp(child_args[0], child_args);
            if (-1 == err_exec)
            {
                printf("execution of %s failed with error %d\n"
                        , child_args[0], err_exec);
                break;
            }

        }
        /* parent */
        if (0 < test)
        {
            pid_t child_pid = waitpid(-1, &child_status, 0);

            if (-1 == child_pid)
            {
                printf("error on waitpid\n");

                break;
            }

            printf("\nchild is %d, status %d, child pid (%d)\n\n"
                , test, child_status, child_pid);
        }
    }

    printf("\n=== call with system command ===\n\n");

    if (-1 == system("./app.out this_is_system"))
    {
        printf("error when calling system\n");
    }

    return 0;
}
