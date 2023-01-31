#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <iostream>

using namespace std;

string humanize(const string& s)
{
    string res;
    string::const_iterator it = s.begin();
    while (it != s.end())
    {
        char c = *it++;
        if (c == '\\' && it != s.end())
        {
            switch (*it++) {
                case '\\': c = '\\'; break;
                case 'n': c = '\n'; break;
                case 't': c = '\t'; break;
                // all other escapes
                default: 
                    // invalid escape sequence - skip it. alternatively you can copy it as is, throw an exception...
                    continue;
            }     
        }
        res += c;
    }
    return res;
}

#endif