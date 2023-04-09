#ifndef RD66_SURPRISER_HPP
#define RD66_SURPRISER_HPP

#include <fstream>   // ofstream definition, file API
#include <cstdlib>   // rand, srand, system

class Surpriser
{
public:
    // explicit Surpriser();
    // virtual ~Surpriser();
    // Surpriser(const Surpriser&) = default;
    // operator=(const Surpriser&) = default;

    virtual void SurpriseMe() = 0;

    static Surpriser* GetRandomSurprise();
};

// surprises classes
class OutSurprise: public Surpriser
{
public:
    explicit OutSurprise()  {}
    ~OutSurprise() {}

    void SurpriseMe();
};

class SysSurprise: public Surpriser
{
public:
    explicit SysSurprise()  {}
    ~SysSurprise() {}

    void SurpriseMe();
};

class FileSurprise: public Surpriser
{
public:
    explicit FileSurprise()  {}
    ~FileSurprise() {}

    void SurpriseMe();

private:
    std::ofstream m_ofs;
};

#endif // RD66_SURPRISER_HPP
