#include <stdlib.h> /* NULL, size_t, malloc, free */
#include <stdio.h> /* printf */
#include <ctype.h> /* tolower */
#include "../ws2/ilrd_string.h" /* string operations */

#define UNUSED(x) (void)(x)

/*========================================================================*/
/* WorkSheet 4 exercise 2 -                                               */
/* Copy the environment of the program to a buffer in lowercase and print */
/* Properly free allocated memory                                         */
/* Dekel Sror */
/*========================================================================*/

size_t GetEnvLines(char **thing);
char **EnvDupLo(char **env);
void EnvPrint(char **lines);
void EnvFree(char **env);

int main(int argc, char const *argv[], char **envp)
{
    char **test = EnvDupLo(envp);

    UNUSED(argc);
    UNUSED(argv);
    EnvPrint(test);
    EnvPrint(envp);
    EnvFree(test);

    return 0;
}


void EnvPrint(char **lines)
{
    printf("you env, sir - - -\n");

    while (*lines)
    {
        printf("%s\n", *lines);
        ++lines;
    }
}

size_t GetEnvLines(char **thing)
{
    size_t count = 0;
    char **base = thing;

    while (*thing)
    {
        ++thing;
        ++count;
    }
    thing = base;
    return count + 1;
}

/* WARNING -- this functions allocates memory */
/* caller is responsible to free */
char **EnvDupLo(char **env)
{
    char **buffer = NULL;
    char *env_line_head = NULL;
    char *buf_line_head = NULL;
    char **buf_head = NULL;

    char **env_head = env;
    size_t env_lines = GetEnvLines(env);

    /* allocation - pointer array*/
    buffer = (char**)malloc(sizeof(char*)*(env_lines));

    if (!buffer)
    {
        exit(1);
    }
    buf_head = buffer;

    /* allocation - string buffers */
    while (*env)
    {
        *buffer = (char*)malloc(StrLen(*env) + 1);

        if (!*buffer)
        {
            EnvFree(buffer);
            return NULL;
        }

        ++buffer;
        ++env;
    }

    buffer = buf_head;
    env = env_head;

    /* copy lowercase strings to buffer */
    while (*env)
    {
        env_line_head = *env;
        buf_line_head = *buffer;

        while (**env)
        {
            **buffer = tolower(**env);
            ++*buffer;
            ++*env;
        }

        **buffer = '\0';
        *env = env_line_head;
        *buffer = buf_line_head;
        ++buffer;
        ++env;
    }

    buffer = buf_head;
    env = env_head;

    return buffer;
}

void EnvFree(char **env)
{
    /* 'parent' buffer will be freed last */
    char **env_head = env;

    while (*env)
    {
        free(*env);
        *env = NULL;
        ++env;
    }

    env = env_head;
    free(env);
    env = NULL;
}
