#include <unistd.h>  /* usleep                 */
#include <pthread.h> /* pthread_t, pthread API */
#include <string.h>  /* memest                 */
#include <stdio.h>   /* printf                 */

#include "dllist.h"

#define NUM_SIMU (5)

pthread_mutex_t g_msg_lock = PTHREAD_MUTEX_INITIALIZER;
dlist_t *g_msg_list = NULL;

static void PostMessage(dlist_t *list);
static void *Produce(void *arg);
static void *Consume(void *arg);

int main(void)
{
    size_t i = 0;

    pthread_t prod_ids[NUM_SIMU] = { 0 };
    pthread_t cons_ids[NUM_SIMU] = { 0 };
    unsigned char prod_kills[NUM_SIMU] = { 0 };
    unsigned char cons_kills[NUM_SIMU] = { 0 };

    g_msg_list = DLCreate();

    for (i = 0; i < NUM_SIMU; ++i)
    {
        if (0 != pthread_create(&cons_ids[i], NULL, Consume, &cons_kills[i]))
        {
            return 7;
        }
    }

    for (i = 0; i < NUM_SIMU; ++i)
    {
        if (0 != pthread_create(&prod_ids[i], NULL, Produce, &prod_kills[i]))
        {
            return 7;
        }
    }

    system("stty -icanon -echo");
    getchar();
    system("stty icanon echo");

    memset(prod_kills, 1, NUM_SIMU);
    memset(cons_kills, 1, NUM_SIMU);

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
    unsigned char *killswitch = (unsigned char *)arg;
    static long msg_counter = 0;

    while (0 == *killswitch)
    {
        pthread_mutex_lock(&g_msg_lock);

        DLPushBack(g_msg_list, (void *)msg_counter);

        ++msg_counter;
        pthread_mutex_unlock(&g_msg_lock);

        usleep(100);
    }

    return NULL;
}

static void *Consume(void *arg)
{
    unsigned char *killswitch = (unsigned char *)arg;

    while (0 == *killswitch)
    {
        pthread_mutex_lock(&g_msg_lock);

        if (!DLIsEmpty(g_msg_list))
        {
            PostMessage(g_msg_list);
        }

        pthread_mutex_unlock(&g_msg_lock);

        usleep(100);
    }

    return NULL;
}


static void PostMessage(dlist_t *list)
{
    printf("msg#%ld, tid %ld\n",(long)DLGetData(DLBegin(list)), pthread_self());
    DLPopFront(list);
}
