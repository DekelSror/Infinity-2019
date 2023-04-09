#include <stdio.h>   /* printf */
#include <pthread.h> /* pthread API */
#include <string.h>  /* memcmp */

void *ThreadFillArr(void *arg);

#define NUM_THREADS (100000)

static size_t array[NUM_THREADS] = { 0 };

int main(void)
{
	size_t i = 0;
	static size_t validation_array[NUM_THREADS] = { 0 };
	static pthread_t thread_ids[NUM_THREADS] = { 0 };


	for (i = 0; i < NUM_THREADS; ++i)
	{
		validation_array[i] = i;
	}

	for (i = 0; i < NUM_THREADS; ++i)
	{
		int create_err = pthread_create(&thread_ids[i],
								NULL,
								ThreadFillArr,
								(void *)i);

		if (create_err)
		{
			perror("could not create thread\n");

			break;
		}
	}

	if (0 != memcmp(array, validation_array, NUM_THREADS * sizeof(size_t)))
	{
		printf("nein! *dotodotodotodotodotodotodotodoto* nein!\n");
	}
	else
	{
		printf("YASSS\n");
	}

	return 0;
}

void *ThreadFillArr(void *arg)
{
	size_t index = *(size_t *)&arg;

	array[index] = index;
	++index;

	return NULL;
}
