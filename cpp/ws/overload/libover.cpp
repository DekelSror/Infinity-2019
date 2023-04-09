#include <iostream>

void Foo()
{
	std::cout << "I Am Foo++\n";
}

void Foo(int n)
{
	std::cout << "I Am Foo++" << n << '\n';
}


int main()
{
	Foo(1.1);

	return 0;
}
