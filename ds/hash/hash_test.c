/*==============================================================================
Data Structures - Hash
Tests
Dekel Sror
Review - Maor Alankri
RC 1
==============================================================================*/
#include <stdio.h>  /* printf, FILE*, file API  */
#include <stdlib.h> /* calloc, free 		    */
#include <string.h> /* strlen, strcmp 		    */
#include <time.h>   /* clock_t, clock, difftime */

#include "hash.h"

static void FillBufferFromFile (char *buffer, const char *path);
static void HashFromBuffer 	   (hash_t *hash, char *buffer, size_t how_many);
static size_t WordHash		   (const void *str);
static int WordCompare 		   (const void *value, const void *hash_value);

#define WORDS_IN_DICT  (101825lu)
#define HASH_KEY_RANGE (204557lu)
#define AVG_WORD_SIZE  (10)

#define SPELL_OK  ("correctly. Good Job!\n")
#define SPELL_BAD ("incorrectly. Try again\n")

int main(int argc, const char *argv[])
{
	size_t hash_size = HASH_KEY_RANGE;
	 char *find_res = NULL;
	size_t res_count = 0;
	static const char *dict_path = "/usr/share/dict/american-english";
	clock_t timer = 0;
	int ret_main = 0;

	/* initilization */
	 char *buffer = calloc(WORDS_IN_DICT * AVG_WORD_SIZE, sizeof(char));
	hash_t *test = HashCreate(WordHash, WordCompare, hash_size);

	(void)argc;

	if (NULL == buffer || NULL == test)
	{
		return 1; /* no memory */
	}

	printf("expecting 1 - is empty? [%d]\n", HashIsEmpty(test));

	FillBufferFromFile(buffer, dict_path);

	HashFromBuffer(test, buffer, WORDS_IN_DICT);
	printf("expecting 0 - is empty? [%d]\n", HashIsEmpty(test));

	/* simple tests - isempty, count, find and remove */
	res_count = HashCount(test);

	if (WORDS_IN_DICT !=res_count)
	{
		printf("main inserted %lu words, wanted %lu\n"
				, res_count, WORDS_IN_DICT);
	}

	printf("find word: \"view\"\n");

	timer = clock();
	find_res = (char *)HashFind(test, "view");
	timer = difftime(clock(), timer);

	printf("supposed to find: %p has \"%s\"\n", (void *)find_res, find_res);
	printf("ticks for find: %ld\n", timer);


	printf("remove word: \"view\"\n");
	timer = clock();
	HashRemove(test, "view");
	timer = difftime(clock(), timer);
	find_res = (char *)HashFind(test, "view");
	printf("suppod to not find: %p has %s\n", (void *)find_res, find_res);
	printf("ticks for remove: %ld\n", timer);

	/* spell checking for command line argument */
	if (NULL == argv[1])
	{
		printf("next time, please enter a word to check");
		printf(" (\"view\" was removed)\n\n\n");

		ret_main = 2; /* err no word */
	}
	else
	{
		timer = clock();
		find_res = HashFind(test, argv[1]);
		timer = difftime(clock(), timer);

		printf("\"%s\" was spelled - ", argv[1]);

		if (NULL != find_res)
		{
			printf(SPELL_OK);
		}
		else
		{
			printf(SPELL_BAD);
		}

		printf("ticks for find: %ld\n", timer);
	}

	HashDestroy(test);

	free(buffer);

	return ret_main;
}

static void HashFromBuffer(hash_t *hash, char *buffer, size_t how_many)
{
	size_t i = 0;

	for (i = 0; i < how_many; ++i)
	{
		int err = HashInsert(hash, buffer);

		if (0 != err)
		{
			printf("insert failed with err %d\n", err);
		}

		buffer += strlen(buffer) + 1;
	}
}

static void FillBufferFromFile(char *buffer, const char *path)
{
	FILE *dictionary = fopen(path, "r");
	 char *tokenizer = NULL;
	long file_size_bytes = 0;
	int io_error = 0;

	if (NULL == dictionary)
	{
		printf("no file!\n");

		return;
	}

	io_error = fseek(dictionary, 0l, SEEK_END);

	file_size_bytes = ftell(dictionary);

	rewind(dictionary);
	io_error = fread(buffer, sizeof(char), file_size_bytes, dictionary);

	tokenizer = strtok(buffer, "\n");

	while (NULL != tokenizer)
	{
		tokenizer = strtok(NULL, "\n");
	}

	io_error = fclose(dictionary);

	(void)io_error;
}

static size_t WordHash(const void *value)
{
    size_t hashval = 0;
	const  char *word = value;

    for (hashval = 0; '\0' != *word; ++word)
	{
        hashval = *word + 31 * hashval;
	}

    return hashval % HASH_KEY_RANGE;
}

static int WordCompare(const void *value, const void *hash_value)
{
	return strcmp(value, hash_value);
}
