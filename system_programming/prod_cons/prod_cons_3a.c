#include <stdio.h>			/* printf 				  			*/
#include <stdlib.h>			/* system 				  			*/
#include <pthread.h>		/* pthread_t, pthread API */
#include <semaphore.h>	/* sem_t, semaphore API   */
#include <signal.h>			/* sig_atomic_t 		  		*/
#include <unistd.h>			/* usleep 				  			*/

#include "fsq.h"

#define QSIZE (4)
#define NUM_SIMU (5)

static void *Consume(void *arg);
static void *Produce(void *arg);

/* atrocities */
pthread_mutex_t g_queue_lock = PTHREAD_MUTEX_INITIALIZER;

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

	/* create producers */
	for (i = 0; i < NUM_SIMU; ++i)
	{
		if (0 != pthread_create(&prod_ids[i], NULL, Produce, (void *)msg_queue))
		{
			while (0 < i)
			{
				pthread_join(prod_ids[i], NULL);
				--i;
			}

			return 1;
		}
	}

	/* create consumers */
	for (i = 0; i < NUM_SIMU; ++i)
	{
		if (0 != pthread_create(&cons_ids[i], NULL, Consume, (void *)msg_queue))
		{
			while (0 < i)
			{
				pthread_join(cons_ids[i], NULL);
				--i;
			}

			return 1;
		}
	}

	system("stty -icanon -echo");
	getchar();
	__sync_lock_test_and_set(&g_killswitch, 1);
	system("stty icanon echo");

	/* join */

	while (0 < i)
	{
		--i;
		pthread_join(cons_ids[i], NULL);
		pthread_join(prod_ids[i], NULL);
	}

	FSQDestroy(msg_queue);
	msg_queue = NULL;

	pthread_mutex_destroy(&g_queue_lock);
	sem_destroy(&g_cons_count);
	sem_destroy(&g_prod_count);

	return 0;
}

static void *Produce(void *arg)
{
	fsq_t *t_arg = (fsq_t *)arg;

	while (0 == g_killswitch)
	{
		sem_wait(&g_prod_count);
		pthread_mutex_lock(&g_queue_lock);

		FSQEnqueue(t_arg);

		pthread_mutex_unlock(&g_queue_lock);
		sem_post(&g_cons_count);
	}

	return NULL;
}

static void *Consume(void *arg)
{
	fsq_t *t_arg = (fsq_t *)arg;

	while (0 == g_killswitch)
	{
		int wait_val = sem_wait(&g_cons_count);
		pthread_mutex_lock(&g_queue_lock);

		printf("msg #%d\n", FSQDequeue(t_arg));

		pthread_mutex_unlock(&g_queue_lock);

		sem_post(&g_prod_count);
	}

	while (0 == sem_trywait(&g_cons_count))
	{
		pthread_mutex_lock(&g_queue_lock);
		printf("emptying...\n");

		printf("msg #%d\n", FSQDequeue(t_arg));

		pthread_mutex_unlock(&g_queue_lock);
	}

	return NULL;
}
