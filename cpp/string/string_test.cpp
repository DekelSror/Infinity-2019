// RD66 - String - Test file
// Dekel Sror
// Review - Ran Doody
// version 1

#include <iostream>   // cout, cin

#include "string.hpp" // ilrd::String

int main()
{
    std::cout << std::boolalpha;

    ilrd::String s1("abc");
    ilrd::String s2(s1);
    ilrd::String s3("ahlan");

    s3 = s1;

    s1.Concat(s2);

    std::cout << "\nConcat\n\n";
    std::cout << s1 << '\n';

    std::cout << "\nBoolean ops\n\n";
    s1 = "abc";
    std::cout << "==should be true: " << (s1 == s2) << '\n';
    s1 = "abd";
    std::cout << "==should be false: " << (s1 == s2) << '\n';
    std::cout << "!=should be true: " << (s1 != s2) << '\n';
    std::cout << ">should be true: " << (s1 > s2) << '\n';
    std::cout << "<should be false: " << (s1 < s2) << '\n';

    std::cout << "\ninput: enter a string\n\n";
    std::cin >> s3;

    std::cout << "\nindexing\n\n";
    for (size_t i = 0; i < s3.Length(); ++i)
    {
        s3[i] = 'F';
    }

    std::cout << s3 << '\n';

    const ilrd::String s4(s3);

    std::cout << "\nconst indexing\n\n";

    for (size_t i = 0; i < s4.Length(); ++i)
    {
        std::cout << s4[i];
    }

    std::cout << std::noboolalpha <<  std::endl;

    ilrd::String sEmpty;

    std::cout << "empty string is: " << sEmpty << '\n';

    return 0;
}
