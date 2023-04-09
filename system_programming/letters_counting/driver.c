#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
	size_t i = 0;

	for (i = 0; i < NUM_RUNS; ++i)
	{

		pid_t fork = fork();

		if (0 < fork) /* error */
		{

		}
		if (0 == fork) /* child */
		{
			exec(argv[1], argv + 2);
		}
		if (0 > fork) /* parent */
		{
			waitpid(fork, NULL);
		}
	}
}
