#include "helpers.h"
#include <iostream>
#include <string>

using namespace std;
Helpers::Helpers()
{

}

string Helpers::trim(string &s) {
    const string WHITESPACE = " \n\r\t\f\v";
    size_t start = s.find_first_not_of(WHITESPACE);
    s = s.substr(start);
    size_t end = s.find_last_not_of(WHITESPACE);
    s = s.substr(0, end + 1);
    return s;
}
