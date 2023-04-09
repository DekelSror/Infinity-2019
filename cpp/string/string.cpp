// RD66 - String - Module
// Dekel Sror
// Review - Ran Doody
// version 1

#include <cstring>  // strncpy, strcmp, strlen
#include <iostream> // ostream operator<<, istream operator>>

#include "string.hpp"

using namespace ilrd;

#if __cplusplus < 201103L
    #define nullptr (0)
#endif

// Ctor
String::String(const char *other)
{
    size_t len = strlen(other) + 1;

    m_cstr = new char[len];

    memcpy(m_cstr, other, len);
}
// CCtor
String::String(const String& other)
{
    size_t len = other.Length() + 1;

    m_cstr = new char[len];

    memcpy(m_cstr, other.m_cstr, len);
}
// Dtor
String::~String()
{
    delete[] m_cstr;

    m_cstr = nullptr;
}

// I/O operator functions
std::ostream& ilrd::operator<<(std::ostream& os, const String& str)
{
    return os << str.ToCString();
}

std::istream& ilrd::operator>>(std::istream& is, String& str)
{
    char *inputBuff = new char[str.s_inputLen + 1];

    is.getline(inputBuff, str.s_inputLen);

    delete[] str.m_cstr;

    str.m_cstr = inputBuff;

    return is;
}

//  copy assignment
String& String::operator=(const String &other)
{
    *this = other.m_cstr;

    return *this;
}

// assignment
String& String::operator=(const char *other)
{
    size_t otherLen = strlen(other) + 1;
    char* buf = new char[otherLen];

    memcpy(buf, other, otherLen);

    delete[] m_cstr;

    m_cstr = buf;

    return *this;
}

String& String::Concat(const String &other)
{
    size_t myLen = Length();
    size_t otherLen = other.Length();

    char* bothCstrings = new char[myLen + otherLen + 1];

    memcpy(bothCstrings, m_cstr, myLen);
    memcpy(bothCstrings + myLen, other.m_cstr, otherLen + 1);


    delete[] m_cstr;

    m_cstr = bothCstrings;

    return *this;
}

// indexing
char& String::operator[](size_t index)
{
    return *(m_cstr + index);
}

const char& String::operator[](size_t index) const
{
    return *(m_cstr + index);
}

size_t String::Length() const
{
    return strlen(m_cstr);
}

const char* String::ToCString() const
{
    return m_cstr;
}

// boolean operator functions
bool ilrd::operator!=(const String &lhs, const String &rhs)
{
    return (0 != strcmp(lhs.ToCString(), rhs.ToCString()));
}

bool ilrd::operator!=(const String &lhs, const char *rhs)
{
    return (0 != strcmp(lhs.ToCString(), rhs));
}
bool ilrd::operator!=(const char *lhs, const String &rhs)
{
    return (0 != strcmp(lhs, rhs.ToCString()));
}


bool ilrd::operator==(const String &lhs, const String &rhs)
{
    return (0 == strcmp(lhs.ToCString(), rhs.ToCString()));
}

bool ilrd::operator==(const String &lhs, const char *rhs)
{
    return (0 == strcmp(lhs.ToCString(), rhs));
}

bool ilrd::operator==(const char *lhs, const String &rhs)
{
    return (0 == strcmp(lhs, rhs.ToCString()));
}

bool ilrd::operator>(const String &lhs, const String &rhs)
{
    return (0 < strcmp(lhs.ToCString(), rhs.ToCString()));
}

bool ilrd::operator>(const String &lhs, const char *rhs)
{
    return (0 < strcmp(lhs.ToCString(), rhs));
}

bool ilrd::operator>(const char *lhs, const String &rhs)
{
    return (0 < strcmp(lhs, rhs.ToCString()));
}

bool ilrd::operator<(const String &lhs, const String &rhs)
{
    return (0 > strcmp(lhs.ToCString(), rhs.ToCString()));
}

bool ilrd::operator<(const String &lhs, const char *rhs)
{
    return (0 > strcmp(lhs.ToCString(), rhs));
}

bool ilrd::operator<(const char *lhs, const String &rhs)
{
    return (0 > strcmp(lhs, rhs.ToCString()));
}
