/*==============================================================================
	System Programming - WatchDog
	Dekel Sror
	Version 1
	Review: Motti Zamir

	Requirements:
		Monitor a running program.
		Detect faults, take corrective actions upon detection

	Design requirements:
		Use signals as means of IPC
		Use Scheduler for timed messaging
==============================================================================*/
#include <signal.h>		/* SIGUSR1, SIGUSR2, sigaction	*/
#include <semaphore.h>  /* sem_t, semaphore API			*/
#include <pthread.h>	/* pthread API 					*/
#include <unistd.h>		/* fork, exevp					*/
#include <fcntl.h> 		/* O_ constants					*/
#include <sys/stat.h>   /* mode constants				*/
#include <string.h> 	/* strcmp, memmove				*/
#include <stdlib.h> 	/* malloc, free 				*/
#include <sys/wait.h> 	/* waitpid 						*/

#include <stdio.h> 		/* review						*/

#include "ilrd_uid.h"	/* ilrd_uid_t					*/
#include "scheduler.h"	/* sch_t, scheduler API 		*/
#include "watch_dog.h"

enum { DOG, APP };

/* forward declarations */
/* signal handlers */
static void U2Handler(int sig);
static void U1Handler(int sig);
/* scheduler tasks */
static int TaskPing(void *arg);
static int TaskMonitor(void *arg);
/* comm thread function */
static void *Watch(void *arg);
/* resoucres related functions */
static int InitResources(void);
static void Cleanup(void);
static int GetArgs(char **argv);

/* global resources */
static volatile size_t g_faults = 0;
static volatile sig_atomic_t g_job_done = 0;
static sch_t *g_scheduler = NULL;

static pthread_t g_comm_thread_id = { 0 };
static pid_t g_other_process_id = { 0 };

static pthread_mutex_t g_faults_lock = PTHREAD_MUTEX_INITIALIZER;
static sem_t *g_ready_sem = { 0 };

static struct sigaction g_action_usr1 = { 0 };
static struct sigaction g_action_usr2 = { 0 };

static int g_whoami = 0;

static char **g_argv = { NULL };
static int g_argc = 0;

/* ideally, these strings and macros belong in a config file */
static const char watch_dog_bin[] = "./watch_dog.out";
static const char sem_name[] = "watch_dog_ready_sem";
#define FAULT_TOLERANCE (5)
#define PING_INTERVAL (1)
#define NUM_RETRIES (3)

/* 	API functions   */
int WDKeepAlive(int argc, char *argv[])
{
	g_argc = argc;

	if (0 != InitResources())
	{
		Cleanup();

		return 1;
	}

	if (0 != strcmp(watch_dog_bin, argv[0]))
	{ 	/* I am app */
		pid_t fork_ret = { 0 };

		g_whoami = APP;

		if (0 != GetArgs(argv))
		{
			Cleanup();

			return 1;
		}

		fork_ret = fork();
		if (0 == fork_ret) /* child - dog */
		{
			execvp(g_argv[0], g_argv);
		}
		else if (0 < fork_ret) /* parent - app */
		{
			g_other_process_id = fork_ret;

			sem_wait(g_ready_sem);

			if (0 != pthread_create(&g_comm_thread_id, NULL, Watch, NULL))
			{
				Cleanup();

				return 1;
			}
		}
		else /* error - no dog */
		{
			perror("bad fork!");
			Cleanup();

			return 1;
		}
	}
	else
	{	/* I am dog */
		g_whoami = DOG;
		g_other_process_id = getppid();

		if (0 != GetArgs(argv))
		{
			Cleanup();

			return 1;
		}
		/* announce ready to start pinging */
		sem_post(g_ready_sem);
		Watch(NULL);
		/* acknowledge SIGUSR2 from app */
		kill(g_other_process_id, SIGUSR2);
		Cleanup();
	}

	printf("pid %d going back to main (%d)\n", getpid(), g_whoami);

	return 0;
}

static int GetArgs(char **argv)
{
	int i = 0;

	/* original argc for DOG, +1 for APP */
	if (DOG == g_whoami)
	{
		/* +1 for NULL termination */
		g_argv = malloc(sizeof(char *) * (g_argc + 1));
	}
	else
	{
		g_argv = malloc(sizeof(char *) * (g_argc + 2));
	}

	if (NULL == g_argv)
	{
		return 1;
	}

	if (APP == g_whoami)
	{
		g_argv[0] = (char *)watch_dog_bin;
	}

	for (i = 0; i < g_argc; ++i)
	{
		g_argv[i + g_whoami] = argv[i];
	}

	g_argv[i + g_whoami] = NULL;

	return 0;
}

void WDFree(void)
{
	size_t retries = 0;

	while (NUM_RETRIES > retries)
	{
		kill(g_other_process_id, SIGUSR2);

		if (sem_trywait(g_ready_sem))
		{
			waitpid(g_other_process_id, NULL, 0);

			break;
		}

		++retries;
	}

	if (0 != pthread_join(g_comm_thread_id, NULL))
	{
		perror("failed to join comm thread");
	}

	Cleanup();
}

/* static functions definitions */
/* comm thread function */
static void *Watch(void *arg)
{
	(void)arg;

	SchRun(g_scheduler);

	return NULL;
}

/* scheduler tasks */
static int TaskMonitor(void *arg)
{
	(void)arg;

	if (FAULT_TOLERANCE < g_faults)
	{
		kill(g_other_process_id, SIGKILL);
		SchStop(g_scheduler);

		pthread_mutex_lock(&g_faults_lock);
		g_faults = 0;
		pthread_mutex_unlock(&g_faults_lock);

		if (DOG == g_whoami) /* app failed */
		{
			/* become app */
			execvp(g_argv[0] ,g_argv + 1);

			execvp("./app.out", args_of_app);
		}
		else /* dog failed */
		{
			/* re-fork for another dog */
			// WDKeepAlive(g_argc, g_argv + 1);
			WDKeepAlive(args_of_app);
		}

		return 1;
	}

	return 0;
}

static int TaskPing(void *arg)
{
	(void)arg;

	if (g_job_done)
	{
		SchStop(g_scheduler);

		return 1;
	}

	pthread_mutex_lock(&g_faults_lock);
	++g_faults;
	pthread_mutex_unlock(&g_faults_lock);

	kill(g_other_process_id, SIGUSR1);
	printf("(%d) says I (%d) dog, faults: %lu\n", getpid(), g_whoami, g_faults);

	return 0;
}

/* resources related functions */
static int InitResources(void)
{
	static ilrd_uid_t ping_task_id = { 0 };
	static ilrd_uid_t monitor_task_id = { 0 };
	(void)ping_task_id;
	(void)monitor_task_id;

	g_ready_sem = sem_open(sem_name, O_CREAT, S_IRUSR | S_IWUSR, 0);
	/* set signal handlers */
	g_action_usr1.sa_handler = U1Handler;
	g_action_usr2.sa_handler = U2Handler;
	sigaction(SIGUSR1, &g_action_usr1, NULL);
	sigaction(SIGUSR2, &g_action_usr2, NULL);
	/* init scheduler with tasks */
	g_scheduler = SchCreate();
	if (NULL == g_scheduler)
	{
		Cleanup();

		return 1;
	}

	ping_task_id = SchAdd(g_scheduler, PING_INTERVAL, TaskPing, NULL);
	monitor_task_id = SchAdd(g_scheduler, PING_INTERVAL, TaskMonitor, NULL);

	return 0;
}

static void Cleanup(void)
{
	pthread_mutex_destroy(&g_faults_lock);
	sem_destroy(g_ready_sem);

	free(g_argv);
	g_argv = NULL;
	SchDestroy(g_scheduler);
	g_scheduler = NULL;
}

/* signal handlers */
static void U1Handler(int sig)
{
	(void)sig;

	pthread_mutex_lock(&g_faults_lock);
	g_faults = 0;
	pthread_mutex_unlock(&g_faults_lock);
}

static void U2Handler(int sig)
{
	(void)sig;

	printf("%d got SIGUSR2\n", getpid());
	__sync_lock_test_and_set(&g_job_done, 1);
}
