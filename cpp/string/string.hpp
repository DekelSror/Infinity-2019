// RD66 - String - Header
// Dekel Sror
// Review - Ran Doody
// version 1

#ifndef ILRD_RD66_STRING_HPP
#define ILRD_RD66_STRING_HPP

#include <iosfwd>  // istream, ostream

namespace ilrd
{
class String
{
public:
    String(const char *other = "");                            //ctor s1(string)
    String(const String &other);                               //cctor s1(s2)
    ~String();                                                 //dtor
    String &operator=(const String &other);// s1 = s2;
    String &operator=(const char *other);// s3 ="goodbye";

    char &operator[](size_t index);                            // s1[i];
    const char &operator[](size_t index) const;                // const s1[i];

    friend std::istream& operator>>(std::istream& is, String& str); //cin >> s1;

    String &Concat(const String &other);                  //s1.Concat(s2)

    size_t Length() const;                                //s1.Length()

    const char *ToCString() const;                        //puts(s1.ToCString())

private:
    char *m_cstr;
    const static size_t s_inputLen = 1024;
};

bool operator==(const String &lhs, const String &rhs);     //if (s1 == s2)
bool operator==(const String &lhs, const char *rhs);       //if  (s1 == "hello")
bool operator==(const char *lhs, const String &rhs);       //if ("hello" == s1)

bool operator!=(const String &lhs, const String &rhs);
bool operator!=(const String &lhs, const char *rhs);
bool operator!=(const char *lhs, const String &rhs);

bool operator>(const String &lhs, const String &rhs);
bool operator>(const String &lhs, const char *rhs);
bool operator>(const char *lhs, const String &rhs);

bool operator<(const String &lhs, const String &rhs);
bool operator<(const String &lhs, const char *rhs);
bool operator<(const char *lhs, const String &rhs);

std::ostream& operator<<(std::ostream& os, const String& str); //cout << s1;
std::istream& operator>>(std::istream& is, String& str);
} //namespace ilrd

#endif //ILRD_RD66_STRING_HPP
