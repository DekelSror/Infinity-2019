#ifndef ILRD_RD66_FRACTION_HPP
#define ILRD_RD66_FRACTION_HPP

#include <limits>

class Fraction
{
public:
	Fraction(int numerator = 0, int denominator = 1);
	~Fraction();

	Fraction(const Fraction& other);
	Fraction(float other);

	Fraction& operator=(const Fraction& other);

	void operator+=(const Fraction& other);
	void operator+=(int other);
	bool operator==(const Fraction& other) const;
	bool operator==(int other) const;

	inline Fraction operator+ (const Fraction& other) const;
	inline Fraction operator- (const Fraction& other) const;
	Fraction operator+() const;
	Fraction operator-() const;

	Fraction& operator++ ();
	Fraction& operator-- ();
	Fraction& operator++ (int none);
	Fraction& operator-- (int none);

	bool IsUndefined() const;
	void Print() const;

	void SetNumerator(int numerator);
	void SetDenominator(int denominator);

	int GetNumerator() const;
	int GetDenominator() const;

private:
	int m_numerator;
	int m_denominator;
	const static int s_undefined;
	static size_t s_numPoints;
	const static float s_tolerance;
};

inline Fraction Fraction::operator+(const Fraction& other) const
{
	Fraction res((m_numerator * other.m_denominator) +
					(m_denominator * other.m_numerator),
					(m_denominator * other.m_denominator));

	return res;
}

inline Fraction Fraction::operator-(const Fraction& other) const
{
	Fraction res((m_numerator * other.m_denominator) -
					(m_denominator * other.m_numerator),
					(m_denominator * other.m_denominator));

	return res;
}


#endif //ILRD_RD66_FRACTION_HPP
