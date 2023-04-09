#include <stdio.h>			/* printf 				  			*/
#include <stdlib.h>			/* system 				  			*/
#include <pthread.h>		/* pthread_t, pthread API */
#include <semaphore.h>	/* sem_t, semaphore API   */
#include <signal.h>			/* sig_atomic_t 		  		*/
#include <unistd.h>			/* usleep 				  			*/
#include <string.h> 		/* memcmp 				  			*/

#include "fsq.h"

#define QSIZE (4)
#define NUM_SIMU (5)

static void *Consume(void *arg);
static void *Produce(void *arg);

/* atrocities */
pthread_mutex_t g_prod_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_cons_lock = PTHREAD_MUTEX_INITIALIZER;
int g_msg_counter = 0;

sem_t g_prod_count = { 0 };
sem_t g_cons_count = { 0 };
sig_atomic_t g_killswitch = 0;

int main(void)
{
	fsq_t *msg_queue = FSQCreate(QSIZE);
	pthread_t prod_ids[NUM_SIMU] = { 0 };
	pthread_t cons_ids[NUM_SIMU] = { 0 };
	size_t i = 0;

	sem_init(&g_prod_count, 0, QSIZE);
	sem_init(&g_cons_count, 0, 0);

	/* create */
	for (i = 0; i < NUM_SIMU; ++i)
	{
		if (0 != pthread_create(&prod_ids[i], NULL, Produce, (void *)msg_queue))
		{
			return 1;
		}
	}

	for (i = 0; i < NUM_SIMU; ++i)
	{
		if (0 != pthread_create(&cons_ids[i], NULL, Consume, (void *)msg_queue))
		{
			return 1;
		}
	}

	system("stty -icanon -echo");
	getchar();
	__sync_lock_test_and_set(&g_killswitch, 1);
	system("stty icanon echo");

	/* join producers */
	for (i = 0; i < NUM_SIMU; ++i)
	{
		pthread_join(prod_ids[i], NULL);
	}

	/* join consumers using poison apples */
	for (i = 0; i < NUM_SIMU; ++i)
	{
		sem_wait(&g_prod_count);

		FSQEnqueue(msg_queue, -1);

		sem_post(&g_cons_count);
	}

	for (i = 0; i < NUM_SIMU; ++i)
	{
		pthread_join(cons_ids[i], NULL);
	}

	FSQDestroy(msg_queue);
	msg_queue = NULL;

	pthread_mutex_destroy(&g_prod_lock);
	pthread_mutex_destroy(&g_cons_lock);
	sem_destroy(&g_cons_count);
	sem_destroy(&g_prod_count);

	return 0;
}

static void *Consume(void *arg)
{
	fsq_t *t_arg = (fsq_t *)arg;

	while (1)
	{
		int rc = 0;

		sem_wait(&g_cons_count);
		pthread_mutex_lock(&g_cons_lock);

			rc = FSQDequeue(t_arg);

		pthread_mutex_unlock(&g_cons_lock);
		sem_post(&g_prod_count);

		if (-1 == rc)
		{
			break;
		}
	}

	return NULL;
}

static void *Produce(void *arg)
{
	fsq_t *t_arg = (fsq_t *)arg;

	while (0 == g_killswitch)
	{
		sem_wait(&g_prod_count);
		pthread_mutex_lock(&g_prod_lock);

			FSQEnqueue(t_arg, g_msg_counter);
			++g_msg_counter;

		pthread_mutex_unlock(&g_prod_lock);
		sem_post(&g_cons_count);

		printf("m %d", g_msg_counter);
	}

	printf("\n\nbyebye\n");

	return NULL;
}

/*
static void *Produce(void *arg)
{
	fsq_t *t_arg = (fsq_t *)arg;

	while (!g_killswitch)
	{
		sem_wait(&g_prod_count);
		pthread_mutex_lock(&g_prod_lock);

			FSQEnqueue(t_arg, g_msg_counter);
			++g_msg_counter;

		sem_post(&g_cons_count);
		pthread_mutex_unlock(&g_prod_lock);
	}

	return NULL;
}

static void *Consume(void *arg)
{
	fsq_t *t_arg = (fsq_t *)arg;
	int rc = 0;

	while (1)
	{
		sem_wait(&g_cons_count);
		pthread_mutex_lock(&g_cons_lock);

			rc = FSQDequeue(t_arg);

		sem_post(&g_prod_count);
		pthread_mutex_unlock(&g_cons_lock);

		printf("msg #%d\n", rc);

		if (-1 == rc)
		{
			printf("%ld TERMINATED!!\n", pthread_self());

			break;
		}
	}

	return NULL;
}
*/
