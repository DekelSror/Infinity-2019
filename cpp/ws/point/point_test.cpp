#include <iostream>
#include <cstdlib>

#include "point.hpp"

int main()
{
	Point pt_1(4, 4);
	pt_1.Print();
	std::cout << "TotalLength: " << TotalLength() << '\n';
	Point pt_2(4, 3);
	pt_2.Print();
	std::cout << "TotalLength: " << TotalLength() << '\n';

	pt_1.AdjustBy(pt_1).AdjustBy(pt_2);

	pt_1.Print();
	pt_2.Print();

	std::cout << "TotalLength: " << TotalLength() << '\n';




	// std::cout << "pt_1 len:" << pt_1.Length() << '\n';
	//
	// pt_2.Print('[', ']');
	// std::cout << "pt_2 len:" << pt_2.Length() << '\n';
	//
	// Point pt_1n2(Add(pt_1, pt_2));
	// pt_1n2.Print('<', '>');
	// std::cout << "pt_1n2 len:" << pt_1n2.Length() << '\n';
	//
	// Point pt_3(7, 2);
	//
	// pt_3.AdjustBy(pt_1);
	//
	// pt_3.Print('(', ')');
	// std::cout << "pt_3 len:" << pt_3.Length() << '\n';
	//
	// pt_3.AdjustBy(pt_1).AdjustBy(100, 100).AdjustBy(pt_2);
	// pt_3.Print(Point::ROUND);
	// std::cout << "pt_3 len:" << pt_3.Length() << '\n';
	//
	// const Point &rp_1 = pt_1;
	//
	// rp_1.Print('<', '>');
	// rp_1.Print(Point::SQUARE);

	return 0;
}
