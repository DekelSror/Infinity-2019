#include <stdio.h>			/* printf 	*/
#include <pthread.h>		/* thread 	*/
#include <errno.h>			/* errno	*/

#define NUM_THREADS (40)
#define INPUT_NUMBER (3200000000lu)

static size_t array[NUM_THREADS] = { 0 };

typedef struct range_s
{
	size_t begin;
	size_t end;
} range_t;

void *ThreadDivSum(void *arg);

int main(void)
{
	size_t i = 0;

	size_t part_sum = 0;
	size_t total_sum = 0;

	static range_t range_array[NUM_THREADS] = { 0 };
	static pthread_t thread_ids[NUM_THREADS] = { 0 };

	for (i = 0; i < NUM_THREADS; ++i)
	{
		range_array[i].begin = ((INPUT_NUMBER / NUM_THREADS) * (i)) + 1;
		range_array[i].end = (INPUT_NUMBER / NUM_THREADS) * (i + 1) + 1;
	}

	for (i = 0; i < NUM_THREADS; ++i)
	{
		int create_err = pthread_create(&thread_ids[i],
										NULL,
										ThreadDivSum,
										&range_array[i]);

		if (create_err)
		{
			perror("could not create thread\n");
			printf("thread #%lu, %d\n", i, errno);

			break;
		}
	}

	for (i = 0; i < NUM_THREADS; ++i)
	{
		while (0 != pthread_join(thread_ids[i], (void **)&part_sum));

		total_sum += part_sum;
	}

	printf("total_sum for %lu : %lu\n", INPUT_NUMBER, total_sum);

	return 0;
}

void *ThreadDivSum(void *arg)
{
	size_t i = 0;
	size_t my_sum = 0;
	range_t my_range = *(range_t *)arg;

	for (i = my_range.begin; i <  my_range.end; ++i)
	{
		if (0 == (INPUT_NUMBER % i))
		{
			my_sum += i;
		}
	}

	return (void *)my_sum;
}
