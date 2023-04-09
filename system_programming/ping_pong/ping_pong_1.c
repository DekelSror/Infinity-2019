#define _POSIX_C_SOURCE (0x100000)

#include <semaphore.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

static void PPHandler(int sig);

static sem_t g_toggle = { 0 };

int main(void)
{
    pid_t fork_ret = { 0 };

    struct sigaction pp_handler = { 0 };
    sem_init(&g_toggle, 0, 0);

    fork_ret = fork();

    if (0 == fork_ret) /* child */
    {
        pp_handler.sa_handler = PPHandler;
        sigaction(SIGUSR1, &pp_handler, NULL);

        while (1)
        {
            kill(getppid(), SIGUSR2);
            sem_wait(&g_toggle);
        }
    }
    else if (0 < fork_ret) /* parent */
    {
        pp_handler.sa_handler = PPHandler;
        sigaction(SIGUSR2, &pp_handler, NULL);

        sem_post(&g_toggle);
        sleep(1);

        while (1)
        {
            sem_wait(&g_toggle);
            kill(fork_ret, SIGUSR1);
        }
    }
    else
    {
        perror("bad fork!\n");
    }

    return 0;
}

static void PPHandler(int sig)
{
    sem_post(&g_toggle);

    if (SIGUSR1 == sig)
    {
        printf("<<< Pong\n");
    }
    else if (SIGUSR2 == sig)
    {
        printf("Ping >>>\n");
    }
}
