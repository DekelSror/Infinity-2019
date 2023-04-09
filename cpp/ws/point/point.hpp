#ifndef ILRD_RD66_POINT_HPP
#define ILRD_RD66_POINT_HPP

struct Point;

Point Add(const Point &p1, const Point &p2);
double TotalLength();

struct Point
{
	enum ParenthesesType { ROUND, SQUARE, CURLY, ANGULAR };

	explicit Point(int x = 0, int y = 0);

	Point &AdjustBy(const Point &other);
	Point &AdjustBy(int dx, int dy);

	double Length() const;

	void Print(char opener, char closer) const;
	void Print(ParenthesesType parens=ROUND) const;

	bool IsEqual(const Point &other) const;

	int GetX() const;
	int GetY() const;

private:
	int m_x;
	int m_y;
	mutable double m_length;
};

#endif //ILRD_RD66_POINT_HPP
