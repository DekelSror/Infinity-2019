/*==============================================================================
System Programming - Simple WatchDog
app for child processes
Dekel Sror
==============================================================================*/
#include <stdio.h>      /* printf       */
#include <sys/types.h>  /* pid_t        */
#include <sys/wait.h>   /* waitpid      */
#include <unistd.h>     /* fork, execvp */

int main(int argc, char const *argv[])
{
    (void)argc;

    printf("I inherited this message: %s\n", argv[1]);
    printf("my pid (%d), parent (%d)\n", getpid(), getppid());


    sleep(2);

    printf("bye-bye!\n");

    return 0;
}
