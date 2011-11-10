// Build and Run:
//     $ g++ -Wall -std=c++0x -o foo unordered_map.cc
//     $ ./foo
// Ref:
//     http://en.wikipedia.org/wiki/Unordered_map_%28C%2B%2B%29

#include <iostream>
#include <unordered_map>
 
int main()
{
    std::unordered_map<std::string, int> months;
    months["january"] = 31;
    months["february"] = 28;
    months["march"] = 31;
    months["april"] = 30;
    months["may"] = 31;
    months["june"] = 30;
    months["july"] = 31;
    months["august"] = 31;
    months["september"] = 30;
    months["october"] = 31;
    months["november"] = 30;
    months["december"] = 31;
    std::cout << "september -> " << months["september"] << std::endl;
    std::cout << "april     -> " << months["april"] << std::endl;
    std::cout << "december  -> " << months["december"] << std::endl;
    std::cout << "february  -> " << months["february"] << std::endl;
    return 0;
}
