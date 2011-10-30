#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <cassert>

template <typename T>
class IntFileReader {
public:
        IntFileReader() {}
        ~IntFileReader() {}
        const T& get();
private:
        T c_;

        // disallow copy constructor and assignment operator
        IntFileReader(const IntFileReader&);
        IntFileReader& operator=(const IntFileReader&);
};

template <typename T>
void print_container(const T& l) {
        std::cout << " |";
        std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, "|"));
        std::cout << "\n";
}
#define ____________________ print_container

template <typename T>
const T& IntFileReader<T>::get() {
        const char filename[] = "20-integers-less-than-100.txt";
        if (c_.size() == 0) {
                std::ifstream infile(filename);
                if (!infile.is_open()) {
                        perror("failed to open file");
                        return c_; // return an empty container
                }

                std::string line;
                std::getline(infile, line);
                assert(line[0] == '#');

                int num;
                while (infile >> num)
                        c_.push_back(num);

                infile.close();
        }
        return c_;
}

int main(int argc, char * argv[])
{
        //typedef std::list<int> Container;
        typedef std::vector<int> Container;

        std::cout << "\n======== the list ========\n";
        IntFileReader<Container> ifr;
        const Container& kC = ifr.get();
        ____________________(kC);

        std::cout << "\n======== greater ========\n";
        {
                Container c(kC);
                //c.sort(std::greater<int>());
                std::sort(c.begin(), c.end(), std::greater<int>());
                ____________________(c);
        }

        return EXIT_SUCCESS;
}
