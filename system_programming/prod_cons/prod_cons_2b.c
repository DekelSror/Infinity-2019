#include <stdio.h>		/* printf 				  */
#include <stdlib.h>		/* system 				  */
#include <pthread.h>	/* pthread_t, pthread API */
#include <semaphore.h>	/* sem_t, semaphore API   */
#include <signal.h>		/* sig_atomic_t 		  */
#include <unistd.h>		/* usleep 				  */


#include "dllist.h"

#define NUM_SIMU (5)

pthread_mutex_t g_msg_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t g_msg_sem = { 0 };
dlist_t *g_msg_list = NULL;
sig_atomic_t g_killswitch = 0;


static void PostMessage(dlist_t *list);
static void *Produce(void *arg);
static void *Consume(void *arg);

int main(void)
{
    size_t i = 0;

    pthread_t prod_ids[NUM_SIMU] = { 0 };
    pthread_t cons_ids[NUM_SIMU] = { 0 };


    g_msg_list = DLCreate();
	sem_init(&g_msg_sem, 0, 0);

    for (i = 0; i < NUM_SIMU; ++i)
    {
        if (0 != pthread_create(&cons_ids[i], NULL, Consume, NULL))
        {
            return 7;
        }
    }

    for (i = 0; i < NUM_SIMU; ++i)
    {
        if (0 != pthread_create(&prod_ids[i], NULL, Produce, NULL))
        {
            return 7;
        }
    }


	system("stty -icanon -echo");
    getchar();
	__sync_lock_test_and_set(&g_killswitch, 1);
	system("stty icanon echo");

    for (i = 0; i < NUM_SIMU; ++i)
    {
        if (0 != pthread_join(prod_ids[i], NULL))
        {
            return 8;
        }
    }

    for (i = 0; i < NUM_SIMU; ++i)
    {
        if (0 != pthread_join(cons_ids[i], NULL))
        {
            return 8;
        }
    }

    printf("\nempty list messages\n\n");
    while (!DLIsEmpty(g_msg_list))
    {
        PostMessage(g_msg_list);
    }

    DLDestroy(g_msg_list);

    return 0;
}

static void *Produce(void *arg)
{
    static long msg_counter = 0;
    (void)arg;

    while (0 == g_killswitch)
    {
		pthread_mutex_lock(&g_msg_lock);
        DLPushBack(g_msg_list, (void *)msg_counter);
        ++msg_counter;
        pthread_mutex_unlock(&g_msg_lock);

		sem_post(&g_msg_sem);

        usleep(100000);
    }

    return NULL;
}

static void *Consume(void *arg)
{
    (void)arg;

    while (0 == g_killswitch)
    {
		sem_wait(&g_msg_sem);

	    pthread_mutex_lock(&g_msg_lock);
        PostMessage(g_msg_list);
        pthread_mutex_unlock(&g_msg_lock);

        usleep(100000);
    }

    return NULL;
}


static void PostMessage(dlist_t *list)
{
    printf("msg#%ld, tid %ld\n",(long)DLGetData(DLBegin(list)), pthread_self());
    DLPopFront(list);
}
