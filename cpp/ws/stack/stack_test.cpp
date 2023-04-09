// RD66 - C++ - stack on singly linked list
// Version 1
// Dekel Sror
// Review: Shon Weinberg - cutest beast ever
#include <iostream>

#include "string.hpp" // string API
#include "stack.hpp" // Stack API

int main()
{

	// char stacks
{
	std::cout << "\n\nchar Test\n\n";
	Stack <char> s1;

	s1.Push('A');
	s1.Push('B');
	s1.Push('C');
	s1.Push('D');

	// copy before popping
	Stack<char> s2(s1);
	Stack<char> s3;
	s3 = s2;

	std::cout << "\ns1 - default Ctor\n\n";
	std::cout << "top: " << s1.Top() << ", size: " << s1.Count() << '\n';
	s1.Pop();
	std::cout << "top: " << s1.Top() << ", size: " << s1.Count() << '\n';
	s1.Pop();
	std::cout << "top: " << s1.Top() << ", size: " << s1.Count() << '\n';
	s1.Pop();
	std::cout << "top: " << s1.Top() << ", size: " << s1.Count() << '\n';
	s1.Pop();

	std::cout << "\ns2 - CCtor\n\n";

	std::cout << "top: " << s2.Top() << ", size: " << s2.Count() << '\n';
	s2.Pop();
	std::cout << "top: " << s2.Top() << ", size: " << s2.Count() << '\n';
	s2.Pop();
	std::cout << "top: " << s2.Top() << ", size: " << s2.Count() << '\n';
	s2.Pop();
	std::cout << "top: " << s2.Top() << ", size: " << s2.Count() << '\n';
	s2.Pop();

	std::cout << "\ns3 - assignment\n\n";
	std::cout << "top: " << s3.Top() << ", size: " << s3.Count() << '\n';
	// s3.Pop();
	std::cout << "top: " << s3.Top() << ", size: " << s3.Count() << '\n';
	// s3.Pop();
	std::cout << "top: " << s3.Top() << ", size: " << s3.Count() << '\n';
	// s3.Pop();
	std::cout << "top: " << s3.Top() << ", size: " << s3.Count() << '\n';
	// s3.Pop();
}

{
	std::cout << "\n\nilrdString Test\n\n";
	Stack<ilrd::String> s1;

	s1.Push("smallak");
	s1.Push("wallak");

	std::cout << "top: " << s1.Top() << ", size: " << s1.Count() << '\n';
	s1.Pop();
	std::cout << "top: " << s1.Top() << ", size: " << s1.Count() << '\n';

}
	return 0;
}
