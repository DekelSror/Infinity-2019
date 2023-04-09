#include <iostream>

#include "polygon.hpp"

static const size_t test_size(1000);

int main()
{
	Point* points = new Point[test_size];
	Polygon shape;

	for(size_t i = 0; i < test_size; ++i)
	{
		shape.Add(points[i]);
	}

	Polygon notEqual;

	std::cout << std::boolalpha;
	std::cout << "IsEqual should be false: " << shape.IsEqual(notEqual) << '\n';

	Polygon equalShape;

	for(size_t i = 0; i < test_size; ++i)
	{
		equalShape.Add(points[i]);
	}

	std::cout << "IsEqual should be true: " << shape.IsEqual(equalShape) << '\n';

	Polygon pCopy(shape);
	std::cout << "IsEqual should be true: " << shape.IsEqual(pCopy) << '\n';

	Polygon pAssign;
	pAssign = equalShape;
	std::cout << "IsEqual should be true: " << pAssign.IsEqual(pCopy) << '\n';

	std::cout << std::noboolalpha;

	delete[] points;

	return 0;
}
