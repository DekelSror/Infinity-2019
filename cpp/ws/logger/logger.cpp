#include <iostream>
#include <fstream>

#include "logger.hpp"

// const std::ofstream Logger::s_trash("/dev/null", std::ofstream::out);
static std::ofstream g_trash("/dev/null", std::ofstream::out);
const std::ofstream& Logger::s_trash = g_trash;

Logger::Logger(Severity initialSeverity)
    : m_severity(initialSeverity)
    , m_os(&std::cerr)
{}

void Logger::SetOutput(std::ostream& output)
{
    m_os = &output;
}

void Logger::Log(Severity msgSeverity, const char* msg)
{
    if (msgSeverity >= m_severity)
    {
        *m_os << msg;
     }
}

void Logger::Log(Severity msgSeverity, const std::string& msg)
{
    Log(msgSeverity, msg.c_str());
}

void Logger::SetOutputSeverity(Severity outputSeverity)
{
    m_severity = outputSeverity;
}
