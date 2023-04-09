/*==============================================================================
System Programming - Simple WatchDog
SIGINT signal handler
Dekel Sror
==============================================================================*/
#include <stdio.h>  /* printf                                             */
#include <signal.h> /* struct sigaction, sigaction, signal numbers macros */
#include <sys/types.h>
#include <unistd.h> /*  sleep                                             */

static void PrintHandler(int sig);

/*
to run cleanly, exit with ctrl + z, then clear process from ps
*/

int main(void)
{
    int act_err = 0;
    size_t counter = 0;
    struct sigaction action = { 0 };

    action.sa_handler = PrintHandler;
    act_err = sigaction(SIGINT, &action, NULL);

    if (0 != act_err)
    {
        printf("got error %d \n", act_err);
    }

    printf("\nhit ctrl + c while running this\n\n");

    while (1)
    {
        printf("counter : %lu\n", counter);

        sleep(1);

        ++counter;
    }

    return 0;
}

static void PrintHandler(int sig)
{
    printf("got sig [%d], pid :%d\n", sig, getpid());
}
