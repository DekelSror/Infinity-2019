#ifndef ILRD_RD66_POLYGON_HPP
#define ILRD_RD66_POLYGON_HPP

#include <cstddef> // size_t

#include "point.hpp" // Point and point API

struct Polygon
{
	explicit Polygon(size_t numPoints = 0); // default Ctor
	explicit Polygon(const Polygon& other);	// CCtor
	~Polygon(); // Dtor
	Polygon& operator=(const Polygon& other);

	void Add(const Point& p);
	bool IsEqual(const Polygon& other) const;
	void Print() const;

	size_t m_numPoints;
	Point *m_points;
};

#endif // ILRD_RD66_POLYGON_HPP
