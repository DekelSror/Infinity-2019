#include <stdio.h>		/* printf 				  */
#include <stdlib.h>		/* system 				  */
#include <pthread.h>	/* pthread_t, pthread API */
#include <semaphore.h>	/* sem_t, semaphore API   */
#include <signal.h>		/* sig_atomic_t 		  */
#include <unistd.h>		/* usleep 				  */
#include <string.h> 	/* memcmp 				  */


#define NUM_CONSUMERS (5)

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_switch = PTHREAD_COND_INITIALIZER;
static sem_t g_cons_count = { 0 };
static long g_msg_counter = 0;
static volatile sig_atomic_t g_exit_flag = 0;

static void *Produce(void *arg);
static void *Consume(void *arg);
static int MakeThreads(pthread_t *ids);
static int CollectThreads(pthread_t *ids);
static void Cleanup(void);

int main(void)
{
	pthread_t thread_ids[NUM_CONSUMERS + 1] = { 0 };

	if (0 != MakeThreads(thread_ids))
	{
		Cleanup();

		return 1;
	}

	usleep(1000000);
	__sync_lock_test_and_set(&g_exit_flag, 1);

	if (0 != CollectThreads(thread_ids))
	{
		Cleanup();

		return 2;
	}

	Cleanup();

	return 0;
}

static void *Produce(void *arg)
{
	size_t i = 0;

	(void)arg;

	while (1)
	{
		/* wait for all consumers to be ready */
		for (i = 0; i < NUM_CONSUMERS; ++i)
		{
			sem_wait(&g_cons_count);
		}

		/* work on resource */
		++g_msg_counter;

		pthread_mutex_lock(&g_lock);
		if (g_exit_flag)
		{
			g_msg_counter = -1;

			break;
		}

		pthread_mutex_unlock(&g_lock);
		pthread_cond_broadcast(&g_switch);
	}

	pthread_mutex_unlock(&g_lock);
	pthread_cond_broadcast(&g_switch);

	return NULL;
}

static void *Consume(void *arg)
{
	long message = 0;

	(void)arg;

	while (1)
	{
		/* announce ready to consume */
		pthread_mutex_lock(&g_lock);
		sem_post(&g_cons_count);
		/* wait for signal */
		pthread_cond_wait(&g_switch, &g_lock);
		pthread_mutex_unlock(&g_lock);

		message = g_msg_counter;
		if (-1 == message)
		{
			break;
		}

		printf("msg #%ld\n", message);
	}

	return NULL;
}

static void Cleanup(void)
{
	pthread_cond_destroy(&g_switch);
	pthread_mutex_destroy(&g_lock);
	sem_destroy(&g_cons_count);
}

static int CollectThreads(pthread_t *ids)
{
	size_t i = 0;
	int status = 0;

	for (i = 0; i < NUM_CONSUMERS + 1; ++i)
	{
		if (0 != pthread_join(*ids, NULL))
		{
			status = 1;
		}

		++ids;
	}

	return status;
}

static int MakeThreads(pthread_t *ids)
{
	size_t i = 0;
	int status = 0;

	if (0 != pthread_create(ids, NULL, Produce, NULL))
	{
		return 1;
	}

	++ids;

	for (i = 1; NUM_CONSUMERS + 1 > i; ++i)
	{
		if (0 != pthread_create(ids, NULL, Consume, NULL))
		{
			status = 1;
		}

		++ids;
	}

	return status;
}
