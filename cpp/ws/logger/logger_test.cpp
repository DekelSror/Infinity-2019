#include <iostream>

#include <string>
#include <cstring>
// required stream definitions
#include <sstream>
#include <fstream>

#include "logger.hpp"

class LTest
{
public:
    explicit LTest(Logger& logger);
    ~LTest() {}

    std::size_t GetFailures() const;

    void PostFail();
    void TestLog(Logger::Severity severity, const char* msg, bool shouldLog);
    void TestLog(Logger::Severity severity, const std::string& msg, bool shouldLog);

    Logger& m_logger;
    std::ostringstream m_cmpStream;
    std::size_t m_failures;
private:
};

LTest::LTest(Logger& logger)
    : m_logger(logger)
    , m_failures(0)
{}

void LTest::PostFail()
{
    ++m_failures;
}

std::size_t LTest::GetFailures() const
{
    return m_failures;
}

void LTest::TestLog(Logger::Severity severity, const char* msg, bool shouldLog)
{
    m_cmpStream << "";

    m_logger.m_os->rdbuf(m_cmpStream.rdbuf());

    m_logger.Log(severity, msg);

    std::cout << "logger has:" << m_cmpStream.rdbuf() << "\n\n";

    if (shouldLog)
    {
        if (0 != memcmp(m_cmpStream.rdbuf(),msg, strlen(msg)))
        {
            PostFail();
        }
    }
}

void LTest::TestLog(Logger::Severity severity, const std::string& msg, bool shouldLog)
{
    TestLog(severity, msg.c_str(), shouldLog);
}

int main()
{
    Logger testLog(Logger::WARNING);
    LTest test(testLog);

    // default log stream
    const std::string mCerr("Default Stream Message\n");
    test.TestLog(Logger::DEBUG, mCerr, false);

    // log to stringstream
    std::ostringstream *srcOss = new std::ostringstream;
    testLog.SetOutput(*srcOss);
    test.TestLog(Logger::WARNING, "User Stream Message", true);
    delete srcOss;

    // log to file
    std::ofstream srcOfs("a.log", std::ofstream::app);
    testLog.SetOutput(srcOfs);
    const std::string mOfs("LogFile Message\n");
    test.TestLog(Logger::ERROR, mOfs, true);

    std::cout << "failures: " << test.GetFailures() << "\n\n";

    return 0;
}
