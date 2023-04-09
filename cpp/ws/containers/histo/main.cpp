#include <iostream>     // cout, cin, endl
#include <string>       // string API
#include <vector>       // vecotr API
#include <map>          // map API
// #include <algorithm>     for_each, find

using std::map;
using std::vector;
using std::pair;
// using std::for_each;
using std::string;
using std::size_t;
using std::cin;
using std::cout;
using std::endl;

const string termLine = ".";
static void PrintOut(const vector<string>& vec, const map<string, size_t>& map);

int main()
{
    string buffer;
    vector<string> histoVec;
    map<string, size_t> lookupMap;

    while (termLine != buffer)
    {
        getline(cin, buffer);

        map<string, size_t>::iterator foundIter = lookupMap.find(buffer);

        if (foundIter != lookupMap.end())
        {
            ++lookupMap[buffer];
        }
        else
        {
            lookupMap[buffer] = 1; //pair<string, size_t>(buffer, 1));
            histoVec.push_back(buffer);
        }
    }

    // remove termLine for output
    histoVec.pop_back();
    lookupMap.erase(termLine);

    PrintOut(histoVec, lookupMap);

    return 0;
}

static void PrintOut(const vector<string>& vec, const map<string, size_t>& map)
{
    for (vector<string>::const_iterator iter = vec.begin();
         iter != vec.end();
         ++iter)
    {
        cout << map.find(*iter)->second << " x " << *iter << '\n';
    }
}
