#include <iostream>
#include <cmath>

#include "point.hpp"

double g_totaLength(0.0);

Point::Point(int x, int y)
: m_x(x), m_y(y)
{
	m_length = Length();
	g_totaLength += m_length;
}

Point &Point::AdjustBy(const Point& other)
{
	m_x += other.m_x;
	m_y += other.m_y;

	Point axis;

	if (!other.IsEqual(axis))
	{
		g_totaLength -= m_length;
		m_length = Length();
		g_totaLength += m_length;
	}

	return *this;
}

Point &Point::AdjustBy(int dx, int dy)
{
	m_x += dx;
	m_y += dy;

	if ((dx != 0) || (dy != 0))
	{
		g_totaLength -= m_length;
		m_length = Length();
		g_totaLength += m_length;
	}

	return *this;
}

double Point::Length() const
{
	m_length = sqrt(m_x*m_x + m_y*m_y);

	return m_length;
}

void Point::Print(char opener, char closer) const
{
	std::cout << opener << m_x << ',' << m_y << closer << "\n";
	return;
}

void Point::Print(ParenthesesType parens) const
{
	switch (parens)
	{
		case ROUND:
			Print('(', ')');
			break;
		case SQUARE:
			Print('[', ']');
			break;
		case ANGULAR:
			Print('<', '>');
			break;
		case CURLY:
			Print('{', '}');
			break;
	}
}

Point Add(const Point &p1, const Point &p2)
{
	Point p_ret(p1.GetX() + p2.GetX(), p1.GetY() + p2.GetY());

	return p_ret;
}

bool Point::IsEqual(const Point &other) const
{
	return ((m_x == other.GetX()) && (m_y == other.GetY()));
}

double TotalLength()
{
	return g_totaLength;
}


int Point::GetX() const
{
	return m_x;
}

int Point::GetY() const
{
	return m_y;
}
