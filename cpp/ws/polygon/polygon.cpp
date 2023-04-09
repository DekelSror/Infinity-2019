#include <iostream> // cout for Polygon::Print
#include <cstring>  // memmove

#include "polygon.hpp"

Polygon::Polygon(size_t numPoints)
: m_numPoints(numPoints)
{
	m_points = new Point[m_numPoints];
}
// CCtor
Polygon::Polygon(const Polygon& other)
: m_numPoints(other.m_numPoints)
{
	m_points = new Point[m_numPoints];

	memmove(m_points, other.m_points, sizeof(Point) * m_numPoints);
}
// assignment
Polygon& Polygon::operator=(const Polygon& other)
{
	delete[] m_points;

	m_numPoints = other.m_numPoints;
	m_points = new Point[m_numPoints];

	memmove(m_points, other.m_points, sizeof(Point) * m_numPoints);

	return *this;
}
// Dtor
Polygon::~Polygon()
{
	delete[] m_points;
}

void Polygon::Add(const Point &p)
{
	Point *oldPoints = m_points;

	m_points = new Point[m_numPoints + 1];

	memmove(m_points, oldPoints, sizeof(Point) * m_numPoints);

	m_points[m_numPoints] = p;

	++m_numPoints;

	delete[] oldPoints;
}

bool Polygon::IsEqual(const Polygon &other) const
{
   if (m_numPoints == other.m_numPoints)
   {
	   return memcmp(m_points, other.m_points, m_numPoints);
   }

   return false;

}

void Polygon::Print() const
{
	for (size_t i = 0; i < m_numPoints; ++i)
	{
		std::cout << '[' << i << "]: " << m_points[i].GetX() << '\n';
	}
}
