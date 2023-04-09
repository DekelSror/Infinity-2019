#include <iostream>

#include <string>
// required stream definitions
#include <sstream>
#include <fstream>

#include "logger.hpp"

int main()
{
    Logger demoLog(Logger::WARNING);

    std::string mCerr("cerr message\n");
    demoLog.Log(Logger::INFO, mCerr);

    std::ostringstream *srcOss = new std::ostringstream;
    demoLog.SetOutput(*srcOss);

    char mOss[] = "ostringstream message\n";
    demoLog.Log(Logger::WARNING, mOss);

    delete srcOss;

    std::ofstream srcOfs("a.log", std::ofstream::app);
    demoLog.SetOutput(srcOfs);

    std::string mOfs("ofstream message\n");
    demoLog.Log(Logger::ERROR, mOfs);

    std::cout << srcOss->str() << std::endl;

    return 0;
}
