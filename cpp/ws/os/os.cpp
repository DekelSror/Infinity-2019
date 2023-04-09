#include <iostream>

class X;
// std::ostream& operator<<(std::ostream& os, const X& x);

class X
{
private:
    friend std::ostream& operator<<(std::ostream& os, const X& x);

public:
    X(int a) : m_a(a){}
    int GetValue() const {return m_a;};

private:
    int m_a;
};

int main()
{
    X x1(3);
    X x2(6);
    int i = 78;
    double d = 3.14;
    char c = 'y';

    std::cout
        << " x1: " << x1
        << " x2: " << x2
        << "  " << i << " "<< &i
        << "  " << d << " " << &d
        << "  " << c << " " << &c <<std::endl;

    return 0;
}

std::ostream& operator<<(std::ostream& os, const X& x)
{
    return os << "op<< overload: " << x.m_a;
}
