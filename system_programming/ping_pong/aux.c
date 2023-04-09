#define _POSIX_C_SOURCE (0x100000)

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

static void PPHandler(int sig);

static sem_t g_toggle = { 0 };

int main(int argc, char const *argv[])
{
	struct sigaction pp_handler = { 0 };

	sem_init(&g_toggle, 0, 0);

	pp_handler.sa_handler = PPHandler;
	sigaction(SIGUSR1, &pp_handler, NULL);

	while (1)
	{
		sem_wait(&g_toggle);
		kill(getppid(), SIGUSR2);
	}

	return 0;
}

static void PPHandler(int sig)
{
    sem_post(&g_toggle);

    printf("Ping >>>\n");
}
