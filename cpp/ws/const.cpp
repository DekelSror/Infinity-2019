#include <iostream>


int main()
{
	const int i = 5;
	int* ip = (int *)&i;
	
	*ip = 4;

	printf("i: %d, *ip: %d\n", i, *ip);

	return 0;
}
