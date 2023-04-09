#include <sys/stat.h>  /* stat 		  		 */
#include <sys/types.h> /* struct stat, off_t */
#include <unistd.h>    /* write 			 */
#include <sys/mman.h>  /* mmap and friends   */
#include <fcntl.h>     /* open  			 */
#include <stdio.h>	   /* printf 			 */
#include <pthread.h>   /* thread API   		 */
#include <string.h>    /* memset 			 */


#define NUM_THREADS (1)
#define ASCII_RANGE (256)

static void *LSort(void *arg);

typedef struct thread_sort_s
{
	size_t segment_start;
	size_t segment_end;
	size_t *count_lut;
	char *map_ptr;
} thread_sort_t;

int main(int argc, char const *argv[])
{
	int syscall_status = 0;

	struct stat dict_stats = { 0 };
	void *dict_buffer = NULL;

	void *res_buffer = NULL;
	char *res_ptr = NULL;

	pthread_t thread_ids[NUM_THREADS] = { 0 };
	thread_sort_t thread_args[NUM_THREADS] = { { 0 } };
	size_t count_lut[ASCII_RANGE] = { 0 };

	size_t segment_size = 0;
	size_t rem_bytes = 0;
	size_t i = 0;

	/* get file descriptors */
	int dict_fd = open(argv[1], O_RDONLY, 0);
	int res_fd = open("output.txt", O_CREAT | O_RDWR, 0);

	(void)argc;

	if ((0 > dict_fd) || (0 > res_fd))
	{
		return 4;
	}

	syscall_status = stat(argv[1], &dict_stats);

	if (0 != syscall_status)
	{
		return 3;
	}

	/* map both files */
	dict_buffer = mmap(NULL, dict_stats.st_size,
						PROT_READ, MAP_PRIVATE, dict_fd, 0);

	res_buffer = mmap(NULL, dict_stats.st_size,
						PROT_WRITE, MAP_PRIVATE, res_fd, 0);

	if (NULL == dict_buffer || NULL == res_buffer)
	{
		return 2;
	}

	res_ptr = (char *)res_buffer;

	/* divide work load */
	segment_size = dict_stats.st_size / NUM_THREADS;
	rem_bytes = dict_stats.st_size;

	/* prepare thread args */
	for (i = 0; i < (NUM_THREADS - 1); ++i)
	{
		thread_args[i].map_ptr = dict_buffer;
		thread_args[i].count_lut = count_lut;
		thread_args[i].segment_start = (segment_size * i);
		thread_args[i].segment_end = (segment_size * (i + 1));

		rem_bytes -= segment_size;
	}

	/* handle remainder bytes */

	thread_args[i].map_ptr = dict_buffer;
	thread_args[i].count_lut = count_lut;
	thread_args[i].segment_start = (segment_size * i);
	thread_args[i].segment_end = thread_args[i].segment_start + rem_bytes;

	/* create threads */
	for (i = 0; i < NUM_THREADS; ++i)
	{
		pthread_create(thread_ids + i, NULL, LSort, thread_args + i);
	}

	/* join threads */
	for (i = 0; i < NUM_THREADS; ++i)
	{
		while (0 != pthread_join(thread_ids[i], NULL));
	}

	close(dict_fd);
	munmap(dict_buffer, dict_stats.st_size);

	/* prepare output_file */
	lseek(res_fd, dict_stats.st_size - 1, SEEK_SET);

	syscall_status = write(res_fd, "", 1);

	for (i = 'A'; i < 'Z'; ++i)
	{
		memset(res_ptr, (char)i, count_lut[i]);
		res_ptr += count_lut[i];
	}

	for (i = 'a'; i < 'z'; ++i)
	{
		memset(res_ptr, (char)i, count_lut[i]);
		res_ptr += count_lut[i];
	}

	close(res_fd);

	munmap(res_buffer, dict_stats.st_size);

	return 0;
}

/*

thread function - scan segment of buffer and increment LUT indices

*/
static void *LSort(void *arg)
{
	thread_sort_t *thread_data = (thread_sort_t *)arg;

	for(; thread_data->segment_start < thread_data->segment_end;
			++thread_data->segment_start)
	{
		++thread_data->count_lut[(unsigned char)thread_data->map_ptr
									[thread_data->segment_start]];
	}

	return NULL;
}
