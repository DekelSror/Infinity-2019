// RD66 - Fraction
// Module
// Dekel Sror
// Review - Shon Weinberg

#include <iostream> // cout
#include <cmath>

#include "fraction.hpp"

size_t Fraction::s_numPoints = 0;

const int Fraction::s_undefined = std::numeric_limits<int>::quiet_NaN();
const float Fraction::s_tolerance = 0.001;

// Ctor
Fraction::Fraction(int numerator, int denominator)
	: m_numerator(numerator),
	  m_denominator(denominator)
{
	++s_numPoints;
}

// Dtor
Fraction::~Fraction()
{
	--s_numPoints;
}


// CCtor
Fraction::Fraction(const Fraction& other)
	: m_numerator(other.m_numerator),
	  m_denominator(other.m_denominator)
{
	++s_numPoints;
}

Fraction::Fraction(float other)
{
	size_t count_denom = 1;
	float original = other;

	while ((other - std::floor(other)) > s_tolerance)
	{
		other += original;
		++count_denom;
	}

	m_numerator = std::floor(other);
	m_denominator = count_denom;
}

Fraction& Fraction::operator=(const Fraction& other)
{
	m_numerator = other.m_numerator;
	m_denominator = other.m_denominator;

	return *this;
}


Fraction Fraction::operator+() const
{
	Fraction fRes(*this);

	return fRes;
}

Fraction Fraction::operator-() const
{
	Fraction fRes(*this);

	fRes.m_numerator *= -1;
	fRes.m_denominator *= -1;

	return fRes;
}

bool Fraction::operator==(const Fraction& other) const
{
	if (0 == m_denominator || 0 == other.m_denominator)
	{
		return false;
	}

	return (m_numerator * other.m_denominator) ==
				(m_denominator * other.m_numerator);
}

bool Fraction::operator==(int other) const
{
	return ((other * m_denominator) == m_numerator);
}

void Fraction::operator+=(int other)
{
	m_numerator += other * m_denominator;
}

void Fraction::operator+=(const Fraction& other)
{
	m_numerator = (m_numerator * other.m_denominator) +
						(other.m_numerator * m_denominator);

	m_denominator *= other.m_denominator;
}


// prefix inc and dec
Fraction& Fraction::operator++ ()
{
	m_numerator += m_denominator;

	return *this;
}

Fraction& Fraction::operator-- ()
{
	m_numerator -= m_denominator;

	return *this;
}

// postfix inc and dec
Fraction& Fraction::operator++ (int none)
{
	Fraction& fRes(*this);

	m_numerator -= m_denominator;

	return fRes;
}

Fraction& Fraction::operator-- (int none)
{
	Fraction& fRes(*this);

	m_numerator -= m_denominator;

	return fRes;
}

void Fraction::Print() const
{
	std::cout << m_numerator << '/' << m_denominator << std::endl;
}

// setters and getters
void Fraction::SetNumerator(int numerator)
{
	m_numerator = numerator;
}
void Fraction::SetDenominator(int denominator)
{
	m_denominator = denominator;
}

int Fraction::GetNumerator() const
{
	return m_numerator;
}

int Fraction::GetDenominator() const
{
	return m_denominator;
}

bool Fraction::IsUndefined() const
{
	return (s_undefined == m_denominator);
}
