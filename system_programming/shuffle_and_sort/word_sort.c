/*==============================================================================
Shuffle and Sort
Module
Dekel Sror
Review - Ran Doody
==============================================================================*/
#include <sys/stat.h>  /* stat 		  		 */
#include <sys/types.h> /* struct stat, off_t */
#include <unistd.h>    /* write, lseek		 */
#include <sys/mman.h>  /* mmap and friends   */
#include <fcntl.h>     /* open, close		 */
#include <pthread.h>   /* thread API   		 */
#include <string.h>    /* memset, memmove	 */
#include <stdlib.h>    /* calloc, free, rand */

#include "quick_sort.h" /* QuickSort		 */

#define NUM_ARGS (4)

/* types */
typedef struct sort_arg_s
{
	char **start_index;
	size_t num_lines;
} sort_arg_t;

typedef struct file_data_s
{
	void *map;
	size_t lines;
	size_t size;
	int fd;

} file_data_t;

typedef enum status_e
{
	SUCCESS, ERR_STAT, ERR_FD, ERR_NOMEM, ERR_MMAP, ERR_ARGS, ERR_THREADS
} status_t;

/* ====================== static function declerations ====================== */
static void *SortSubArr(void *arg); /* thread function */

static void ShufflePointers(char **arr, size_t nmemb);
static void FillWordBuff(char **buffer, const char *map, size_t lines);
static void SwapPointers(char **arr, size_t index_1, size_t index_2);

static int LineCmp(const void *s1, const void *s2);
static size_t LineCount(const char *buffer);
static size_t LineLen(const char *str);

static void MergeSorted(char **src_buff,
						char **dest_buff,
						size_t segment_size,
						size_t num_threads,
						size_t lines);

static void MergePtrArrs(char **src_buff,
						 char **dest_buff,
						 size_t start,
						 size_t end,
						 size_t middle);

static void BuffToFile( const char **buff,
						const char *path,
						size_t lines,
						size_t bytes);

static void WriteFromAddrBuff(const char **addr_buff,
							char *dest_buff,
							size_t lines);

static int PrepFile(const char *path, file_data_t *file_data);
static void InitThreadArgs( sort_arg_t **args,
							size_t num_threads,
							char **buff,
							size_t segment_size,
							size_t buff_size);

/* =============================== main ===================================== */
/* usage: ./a.out [num_threads] [input file] [output file] */
/* test: diff [input file] [output file]. No output - success */
int main(int argc, char const *argv[])
{
	size_t i = 0;
	size_t num_threads = 0;
	size_t segment_size = 0;

	file_data_t dict_data = { 0 };
	status_t prep_file_status = 0;

	char **addr_buff = NULL;
	char **merge_buff = NULL;
	pthread_t *thread_ids = NULL;
	sort_arg_t *sort_args = NULL;
/* ============================= initialization ============================= */
	if (NUM_ARGS != argc)
	{
		return ERR_ARGS;
	}

	num_threads = (size_t)atoi(argv[1]);

	/* get input file descriptor, stats and map */
	prep_file_status = PrepFile(argv[2], &dict_data);
	if (SUCCESS != prep_file_status)
	{
		return prep_file_status;
	}

	/* allocate dynamic memory */
	thread_ids = calloc(num_threads, sizeof(pthread_t));
	sort_args  = calloc(num_threads, sizeof(sort_arg_t));
	addr_buff  = calloc(dict_data.lines, sizeof(char *));
	merge_buff = calloc(dict_data.lines, sizeof(char *));

	if ((NULL == thread_ids) ||
		(NULL == sort_args)  ||
		(NULL == addr_buff))
	{
		free(thread_ids);
		thread_ids = NULL;

		free(sort_args);
		sort_args = NULL;

		free(addr_buff);
		addr_buff = NULL;

		free(merge_buff);
		addr_buff = NULL;

		return ERR_NOMEM;
	}
/* ================================= work =================================== */
	/* fill and shuffle the address buffer from map */
	FillWordBuff(addr_buff, dict_data.map, dict_data.lines);
	ShufflePointers(addr_buff, dict_data.lines);

	/* prepare thread function arguments */
	segment_size = dict_data.lines / num_threads;
	InitThreadArgs( &sort_args,
					num_threads,
					addr_buff,
					segment_size,
					dict_data.lines);

	/* create joinable sorting threads */
	for (i = 0; i < num_threads; ++i)
	{
		if (0 != pthread_create(thread_ids + i, NULL, SortSubArr, sort_args + i))
		{
			free(addr_buff);
			addr_buff = NULL;

			free(merge_buff);
			addr_buff = NULL;

			free(thread_ids);
			thread_ids = NULL;

			free(sort_args);
			sort_args = NULL;

			return ERR_THREADS;
		}
	}
	/* join sorting threads */
	for (i = 0; i < num_threads; ++i)
	{
		if (0 != pthread_join(thread_ids[i], NULL))
		{
			free(addr_buff);
			addr_buff = NULL;

			free(merge_buff);
			addr_buff = NULL;

			free(thread_ids);
			thread_ids = NULL;

			free(sort_args);
			sort_args = NULL;

			return ERR_THREADS;
		}
	}

	/* merge sorted segments */
	MergeSorted(addr_buff,
				merge_buff,
				segment_size,
				num_threads,
				dict_data.lines);

	/* write to output file */
	BuffToFile((const char **)addr_buff,
				argv[3],
				dict_data.lines,
				dict_data.size);

	/* cleanup */
	close(dict_data.fd);
	munmap(dict_data.map, dict_data.size);

	free(addr_buff);
	addr_buff = NULL;

	free(merge_buff);
	addr_buff = NULL;

	free(thread_ids);
	thread_ids = NULL;

	free(sort_args);
	sort_args = NULL;

	return SUCCESS;
}

/* ====================== static function definitions ======================= */
static void MergeSorted(char **src_buff,
						char **dest_buff,
						size_t segment_size,
						size_t num_threads,
						size_t lines)
{
	size_t i = 0;

	while (1 < num_threads)
	{
		segment_size <<= 1;
		num_threads >>=1;

		/* calculate arguments for MergePtrArrs */
		for (i = 0; i < num_threads; ++i)
		{
			size_t merge_start = i * segment_size;
			size_t merge_end = segment_size * (i + 1);

			if (merge_end + segment_size > lines)
			{
				merge_end += lines % segment_size;
			}

			MergePtrArrs(src_buff,
						dest_buff,
						merge_start,
						merge_end,
						merge_start + (segment_size >> 1));
			}
		}

		MergePtrArrs(src_buff,
					 dest_buff,
					 0,
					 lines,
					 segment_size >> 1);
}

static void MergePtrArrs(char **src_buff,
						 char **dest_buff,
						 size_t start,
						 size_t end,
						 size_t middle)
{
	const size_t border = middle;
	const size_t length = end - start;
	const size_t write_start = start;
	char **dest_write = dest_buff + start;

	while ((start < border) && (middle < end))
	{
		if (0 < LineCmp(src_buff + start, src_buff + middle))
		{
			*dest_write = *(src_buff + middle);
			++middle;
		}
		else
		{
			*dest_write = *(src_buff + start);
			++start;
		}

		++dest_write;
	}

	/* handle remainders */
	while (start < border)
	{
		*dest_write = *(src_buff + start);
		++start;
		++dest_write;
	}

	while (middle < end)
	{
		*dest_write = *(src_buff + middle);
		++middle;
		++dest_write;
	}

	memmove(src_buff + write_start,
			dest_buff + write_start,
			length * sizeof(char *));
}

static void InitThreadArgs( sort_arg_t **args,
							size_t num_threads,
							char **buff,
							size_t segment_size,
							size_t lines)
{
	size_t i = 0;
	sort_arg_t *arg = *args + i;

	for (i = 0; i < num_threads - 1; ++i)
	{
		arg = *args + i;
		arg->start_index = buff + (segment_size * i);
		arg->num_lines = segment_size;
		lines -= segment_size;
	}

	arg = *args + i;
	arg->start_index = buff + (segment_size * i);
	arg->num_lines = lines;
}

static int PrepFile(const char *path, file_data_t *file_data)
{
	struct stat file_stats = { 0 };
	void *file_map = NULL;
	int file_fd = 0;

	file_fd = open(path, O_CREAT | O_RDONLY, 0);
	if (0 > file_fd)
	{
		return ERR_FD;
	}

	file_data->fd = file_fd;

	if (0 != stat(path, &file_stats))
	{
		return ERR_STAT;
	}

	file_data->size = file_stats.st_size;

	file_map = mmap(NULL,
					file_stats.st_size,
					PROT_READ,
					MAP_PRIVATE,
					file_data->fd,
					0);

	if (NULL == file_map)
	{
		return ERR_MMAP;
	}

	file_data->map = file_map;
	file_data->lines = LineCount(file_data->map);

	close(file_fd);

	return SUCCESS;
}

/* map file by path and write to it */
static void BuffToFile( const char **buff,
						const char *path,
						size_t lines,
						size_t bytes)
{
	int fd = open(path, O_RDWR, 0);
	void *map = mmap(NULL, bytes, PROT_WRITE, MAP_SHARED, fd, 0);

	/* stretch file to have physical addresses to write to */
	lseek(fd, bytes - 1, SEEK_SET);
	write(fd, "", 1);

	WriteFromAddrBuff(buff, map, lines);

	close(fd);
	munmap(map, bytes);
}

static void WriteFromAddrBuff(const char **src_buff,
							char *dest_buff,
							size_t lines)
{
	for(; 0 < lines; --lines)
	{
		size_t write_bytes = LineLen(*src_buff);

		memmove(dest_buff, *src_buff, write_bytes);

		dest_buff += write_bytes;
		*dest_buff = '\n';
		++dest_buff;
		++src_buff;
	}
}

static void FillWordBuff(char **buffer, const char *map, size_t lines)
{
	for (; 0 < lines; --lines)
	{
		*buffer = (char *)map;
		++buffer;
		/* skip over '\n' character */
		map += LineLen(map) + 1;
	}
}

static void ShufflePointers(char **arr, size_t nmemb)
{
	size_t i = 0;

	srand(getpid());

	for (i = 0; i < nmemb; ++i)
	{
		SwapPointers(arr, i, rand() % nmemb);
	}
}

/* thread function */
static void *SortSubArr(void *arg)
{
	sort_arg_t *thread_data = (sort_arg_t *)arg;

	QuickSort(thread_data->start_index,
			thread_data->num_lines,
			sizeof(char *),
			LineCmp);

	return NULL;
}

/* compar for QuickSort */
static int LineCmp (const void *elem_1, const void *elem_2)
{
	const unsigned char *s1 = *(const unsigned char **)elem_1;
	const unsigned char *s2 = *(const unsigned char **)elem_2;

	while ((*s1 == *s2) && ('\n' != *s1))
	{
		++s1;
		++s2;
	}

	return (int)*s1 - (int)*s2;
}

/* same as strcmp and strlen, but treats '\n' as '\0' */
static size_t LineLen(const char *str)
{
	const char *str_ptr = str;

	while (('\n' != *str_ptr) && ('\0' != *str_ptr))
	{
		++str_ptr;
	}

	return str_ptr - str;
}

static size_t LineCount(const char *buffer)
{
	size_t line_count = 0;

	while ('\0' != *buffer)
	{
		if ('\n' == *buffer)
		{
			++line_count;
		}

		++buffer;
	}

	return line_count;
}

static void SwapPointers(char **arr, size_t index_1, size_t index_2)
{
	char *swap = arr[index_1];

	arr[index_1] = arr[index_2];
	arr[index_2] = swap;
}
