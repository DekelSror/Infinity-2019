#include <unistd.h> /* sleep  */
#include <stdio.h>	/* printf */

#include "watch_dog.h"



int main(int argc, char *argv[])
{
	WDKeepAlive(argc, argv);

	printf("served and protected! %d\n", getpid());

	return 0;
}
