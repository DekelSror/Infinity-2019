#include <ctime>     // time

#include "surpriser.hpp" // Surpriser API


int main()
{
    Surpriser* s1 = Surpriser::GetRandomSurprise();

    s1->SurpriseMe();
    s1->SurpriseMe();

    Surpriser* s2 = Surpriser::GetRandomSurprise();

    s2->SurpriseMe();
    s2->SurpriseMe();

    Surpriser* s3 = Surpriser::GetRandomSurprise();

    s3->SurpriseMe();
    s3->SurpriseMe();

    return 0;
}
