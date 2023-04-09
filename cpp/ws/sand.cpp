#include <iostream>

template <typename T>
void Foo(T t)
{
	std::cout << t << "Generic\n";
}

template <>
void Foo(int t)
{
	std::cout << t << "Special\n";
}

int main()
{
	Foo(5);
	Foo<int>(20);

	return 0;
}
