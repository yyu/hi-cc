#include <iostream>
#include <vector>
#include <map>
#include <cassert>

template <typename T, typename U>
void print_mm(std::multimap<T, U>& mm)
{
        typedef typename std::multimap<T, U>::iterator MMIt;
        for (MMIt it = mm.begin(); it != mm.end(); ++it) {
                std::cout << "\t" << it->first << " => " << it->second << "\n";
        }
        //std::cout << "\n";
}
#define ______________________________ print_mm

int main(int argc, char* argv[])
{
        typedef std::pair<std::string, std::string> StrStrPair;
        typedef std::multimap<std::string, std::string> StrStrMMap;

        std::vector<StrStrPair> init_pairs;
        init_pairs.push_back(std::make_pair("Yu Yuan", "Forrest"));
        init_pairs.push_back(std::make_pair("Yu Yuan", "YY"));
        init_pairs.push_back(std::make_pair("Yu Yuan", "YYu"));
        init_pairs.push_back(std::make_pair("Huang Danhong", "Orange"));
        init_pairs.push_back(std::make_pair("Huang Danhong", "DHHuang"));
        init_pairs.push_back(std::make_pair("Tom Hanks", "TH"));
        init_pairs.push_back(std::make_pair("Tom Hanks", "Hanks"));

        StrStrMMap mm;
        
        for (std::vector<StrStrPair>::iterator it = init_pairs.begin(); it != init_pairs.end(); ++it) {
                StrStrMMap::iterator mapit = mm.insert(*it);
                assert(mapit != mm.end());
                std::cout << "inserted: " << mapit->first << ", " << mapit->second << "\n";
        }
        std::cout << "\n";
        ______________________________(mm);

        std::string todel("Tom Hanks");
        std::cout << "\nlet's erase " << todel << ":\n";
        mm.erase(todel);
        ______________________________(mm);

        std::string tosearch("Yu Yuan");
        std::cout << "\nlet's find " << tosearch << ":\n";

        std::cout << "[Method 1]" << "\n";
        StrStrMMap::size_type element_count = mm.count(tosearch);
        StrStrMMap::iterator it = mm.find(tosearch);
        for (StrStrMMap::size_type i = 0; i < element_count; ++i, ++it) {
                assert(it->first == tosearch);
                std::cout << "\t" << tosearch << " : " << it->second << "\n";
        }

        std::cout << "[Method 2]" << "\n";
        StrStrMMap::iterator itb = mm.lower_bound(tosearch);
        StrStrMMap::iterator ite = mm.upper_bound(tosearch);
        for (StrStrMMap::iterator it = itb; it != ite; ++it) {
                assert(it->first == tosearch);
                std::cout << "\t" << tosearch << " : " << it->second << "\n";
        }

        assert(mm.lower_bound("nonexist") == mm.upper_bound("nonexist"));

        std::cout << "[Method 3]" << "\n";
        std::pair<StrStrMMap::iterator, StrStrMMap::iterator> its = mm.equal_range(tosearch);
        for (; its.first != its.second; ++its.first) {
                assert(its.first->first == tosearch);
                std::cout << "\t" << tosearch << " : " << its.first->second << "\n";
        }

        return 0;
}
