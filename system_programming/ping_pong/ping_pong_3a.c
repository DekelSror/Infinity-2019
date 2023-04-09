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
volatile pid_t other_pid = { 0 };

int main(void)
{
	struct sigaction pp_handler = { 0 };
	siginfo_t pp_info = { 0 };
	sem_init(&g_toggle, 0, 0);

	printf("first program is %d\n", getpid());
	sleep(1);

	pp_handler.sa_flags = SA_SIGINFO;
	pp_handler.sa_sigaction = PPHandler;
	sigaction(SIGUSR2, &pp_handler, NULL);

	while(1)
	{
		sem_wait(&g_toggle);
	}

	return 0;
}

static void PPHandler(int sig, siginfo_t *info, void *ucontext)
{
	sem_post(&g_toggle);
	printf("Ping >>> %lu\n", g_switch_counter);
	++g_switch_counter;
	kill(info->si_pid, SIGUSR1);
}
