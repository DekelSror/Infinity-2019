#ifndef RD66_LOGGER_HPP
#define RD66_LOGGER_HPP

#include <iosfwd> // ostream decleration

// class LTest;

class Logger
{
public:
    enum Severity { DEBUG, INFO, WARNING, ERROR };

    explicit Logger(Severity initialSeverity = WARNING);

    void Log(Severity msgSeverity, const char* msg);
    void Log(Severity msgSeverity, const std::string& msg);

    void SetOutputSeverity(Severity outputSeverity);
    void SetOutput(std::ostream& output);

#ifndef NDEBUG
    friend class LTest;
#endif

private:
    enum { NOLOG, LOG, NUM_HANDLE_STATES };

    std::ostream* m_os;
    const static std::ofstream& s_trash;
    Severity m_severity;
};


#endif // RD66_LOGGER_HPP
