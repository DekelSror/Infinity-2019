#include <pthread.h>
#include <stdio.h>
#include <signal.h>

#define CONT_SIZE (50000)

typedef enum switch_e { READ, WRITE } switch_t;

void *Cons(void *arg);
void *Prod(void *arg);

static int g_container[CONT_SIZE] = { 0 };
static sig_atomic_t g_switch = WRITE;

int main(void)
{
	size_t i = 0;
	pthread_t thread_ids[2] = { 0 };

	if (0 != pthread_create(&thread_ids[0], NULL, Cons, NULL))
	{
		return 1;
	}

	if (0 != pthread_create(&thread_ids[1], NULL, Prod, NULL))
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

		while (READ == g_switch);

		printf("producing...\n");
		++set_value;

		for (; setter < arr_end; ++setter)
		{
			*setter = set_value;
		}

		g_switch = READ;
	}

	return NULL;
}

void *Cons(void *arg)
{
	const int *arr_end = g_container + CONT_SIZE;

	(void)arg;

	while (1)
	{
		int *validator = g_container;
		int first = 0;

		while (WRITE == g_switch);

		printf("...consuming\n");
	 	first = *validator;
		++validator;

		for (; validator < arr_end; ++validator)
		{
			if (*validator != first)
			{
				printf("[%5.lu] - consumer had %d, expected %d\n"
						, (size_t)(validator - g_container), *validator, first);

				break;
			}
		}

		g_switch = WRITE;
	}

	return NULL;
}
