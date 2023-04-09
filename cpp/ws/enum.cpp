#include <iostream>


enum E1 {AA, BB, CC, DD};


int main()
{
	int i;
	E1 e = DD;

	i = e;
++e;

	std::cout << i << ' ' << e << '\n';

	return 0;
}
