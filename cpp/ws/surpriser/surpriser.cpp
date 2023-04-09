#include <iostream>  // cout

#include "surpriser.hpp"

#if __cpluslus < 201103L
    #define nullptr (0)
#endif

static OutSurprise sOut;
static SysSurprise sSys;
static FileSurprise sFile;

static Surpriser* possibilities[3];
static bool initialized(false);

Surpriser* Surpriser::GetRandomSurprise()
{
    if (!initialized)
    {
        Init();

        initialized = true;
    }
    return possibilities[rand() % 3];
}


static void Init()
{
    possibilities[0] = &sOut;
    possibilities[1] = &sSys;
    possibilities[2] = &sFile;

    srand(time(nullptr));
}

void OutSurprise::SurpriseMe()
{
    std::cout << "Surprise1!\n";
}

void SysSurprise::SurpriseMe()
{
    system("echo '\\a'");
}

void FileSurprise::SurpriseMe()
{
    m_ofs.open("nothing_here.txt", std::ofstream::out);
    m_ofs.close();
}
