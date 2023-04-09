#include <unistd.h> /* sleep  */
#include <stdio.h>	/* printf */

#include "watch_dog.h"

#define APP_RUN_TIME (5)


int main(int argc, char *argv[])
{
	int rem_slp = APP_RUN_TIME;

	if (0 != WDKeepAlive(argc, argv))
	{
		perror("WDKeepAlive failed!");
		return 2;
	}

	printf("IMPORTANT CODE STARTS\n");

	/* remove assignment to have infinite loop and test crashes */
	while (0 != rem_slp)
	{
		rem_slp = sleep(rem_slp);
	}

	printf("IMPORTANT CODE ENDS\n");

	WDFree();

	printf("NON-IMPORTANT CODE HERE!!\n");

	return 0;
}
