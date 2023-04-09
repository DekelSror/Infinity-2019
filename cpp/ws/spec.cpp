#include <iostream>
#include <string>

class Base
{
public:
    Base(int a = 9) : m_a(a) { std::cout << "B:Ctor" << std::endl; }
    ~Base() { std::cout << "B:Dtor" << std::endl; }
     void Print1() const { std::cout << "B:Print1" << std::endl; }
     void Print2() const { std::cout << "B:Print2" << std::endl; }
     void Print3() const { std::cout << "B:Print3" << std::endl; }

    int m_a;
};

class Derived: public Base
{
public:
    Derived(int b = 6) : m_b(b) { std::cout << "Derived:Ctor" << std::endl;}
    ~Derived() { std::cout << "Derived:Dtor" << std::endl;}
    virtual void Print1() const;
    void Print2() const { std::cout << "Derived:Print2" << std::endl;}

private:
    int m_b;
};

void Derived::Print1() const
{
    std::cout << "D:Print1, " << '\n';
    Base::Print1();
    std::cout << "end D:Print1\n";
}

int main()
{
    std::cout <<"\n b1: \n\n";

    Base* b1 = new Base;

    b1->Print1();
    b1->Print2();
    b1->Print3();

    std::cout <<"\n b2: \n\n";

    std::cout << '\n';
    Base* b2 = new Derived;

    b2->Print1();
    b2->Print2();
    b2->Print3();

    std::cout << '\n';
    std::cout << "\n d: \n\n";
    Derived* d = static_cast<Derived*>(b2);
    // Derived* d = new Derived;


    d->Print1();
    d->Print2();
    // d->Print3();
    b2->Print2();
    std::cout << '\n';

    std::cout << " \n extra \n\n";

    std::cout << "sizeof Base: " << sizeof(Base) << '\n';
    std::cout << "sizeof Derived: " << sizeof(Derived) << '\n';

    delete b1;
    delete b2;

    return 0;
}
