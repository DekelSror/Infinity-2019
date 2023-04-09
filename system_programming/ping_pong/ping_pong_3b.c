#define _POSIX_C_SOURCE (0x100000)

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

static void PPHandler(int sig, siginfo_t *info, void *ucontext);

static sem_t g_toggle = { 0 };
static size_t g_switch_counter = 0;


int main(int argc, char const *argv[])
{
	struct sigaction pp_handler = { 0 };
	siginfo_t pp_info = { 0 };

	int first_pid = 0;

	if (2 > argc)
	{
		return 5;
	}

	first_pid = atoi(argv[1]);
	sem_init(&g_toggle, 0, 0);

	pp_handler.sa_flags = SA_SIGINFO;
	pp_handler.sa_sigaction = PPHandler;

	sigaction(SIGUSR1, &pp_handler, NULL);

	while (1)
	{
		kill(first_pid, SIGUSR2);
		sem_wait(&g_toggle);
	}

	return 0;
}

static void PPHandler(int sig, siginfo_t *info, void *ucontext)
{
	++g_switch_counter;
	printf("<<< Pong, %lu\n", g_switch_counter);
	sem_post(&g_toggle);
}
