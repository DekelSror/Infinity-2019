#include <pthread.h>
#include <stdio.h>
#include <signal.h>

#define CONT_SIZE (50000)

void *Cons(void *arg);
void *Prod(void *arg);

static int g_container[CONT_SIZE] = { 0 };
static sig_atomic_t g_busy = 0;

int main(void)
{
	size_t i = 0;
	pthread_t thread_ids[2] = { 0 };

	if (0 != pthread_create(&thread_ids[0], NULL, Prod, NULL))
	{
		return 1;
	}

	if (0 != pthread_create(&thread_ids[1], NULL, Cons, NULL))
	{
		return 1;
	}

	for (i = 0; i < 2; ++i)
	{
		if (0 != pthread_join(thread_ids[i], NULL))
		{
			return 2;
		}
	}

	return 0;
}

void *Prod(void *arg)
{
	static size_t set_value = 0;
	const int *arr_end = g_container + CONT_SIZE;

	(void)arg;

	while (1)
	{
		int *setter = g_container;

		while (1 == __sync_lock_test_and_set(&g_busy, 1));

		++set_value;

		for (; setter < arr_end; ++setter)
		{
			*setter = set_value;
		}

		__sync_fetch_and_sub(&g_busy, 1);
	}
	return NULL;
}

void *Cons(void *arg)
{
	const int *arr_end = g_container + CONT_SIZE;
	int first = 0;

	(void)arg;

	while (1)
	{
		int *validator = g_container;

		while (1 == __sync_lock_test_and_set(&g_busy, 1));

		first = *validator;
		++validator;

		for (; validator < arr_end; ++validator)
		{
			if (*validator != first)
			{
				printf("[%lu] - consumer had %d, expected %d\n"
							, (size_t)(validator - g_container), *validator, first);

				break;
			}
		}

		__sync_fetch_and_sub(&g_busy, 1);
	}

	return NULL;
}
