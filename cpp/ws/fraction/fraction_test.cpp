// RD66 - Fraction
// Tests
// Dekel Sror
// Review - Shon Weinberg

#include <iostream> // cout

#include "fraction.hpp"

int main()
{
	Fraction f1(3, 5);

	f1 = f1 + 1;

	f1.Print();

	std::cout << "\n\n" << std::endl;

	Fraction f2(1, 2);
	Fraction f3(3, 4);

	+f2 + -(++f3);
	f2.Print();
	f3.Print();

	(f2++) - +(f3--);
	f2.Print();
	f3.Print();

 	f1 = 4;

	f1.Print();

	f1 = 0.125f;
	f1.Print();

	Fraction r1(1, 2);
	Fraction r2(3);

	r1 - r2;
	r1 - 3;
	// 3 - r1;

	return 0;
}
