#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <cassert>

namespace learning{
class IntFileReader {
public:
        IntFileReader() {}
        ~IntFileReader() {}
        const std::list<int>& get();
private:
        std::list<int> l_;

        // disallow copy constructor and assignment operator
        IntFileReader(const IntFileReader&);
        IntFileReader& operator=(const IntFileReader&);
};

void print_list(const std::list<int>& l) {
        std::cout << " |";
        std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, "|"));
        std::cout << "\n";
}

const std::list<int>& IntFileReader::get() {
        const char filename[] = "20-integers-less-than-100.txt";
        if (l_.size() == 0) {
                std::ifstream infile(filename);
                if (!infile.is_open()) {
                        perror("failed to open file");
                        return l_; // return an empty list
                }

                std::string line;
                std::getline(infile, line);
                assert(line[0] == '#');

                int num;
                while (infile >> num)
                        l_.push_back(num);

                infile.close();
        }
        return l_;
}

template <typename T, int N>
class nearby : public std::binary_function<T, T, bool> {
public:
        bool operator()(const T& x, const T& y) {
                int xi = static_cast<int>(x);
                int yi = static_cast<int>(y);
                return (std::abs(xi - yi) < N);
        }
};
}

#define ____________________ learning::print_list

int main(int argc, char * argv[])
{
        std::cout << "\n======== the list ========\n";
        learning::IntFileReader ifr;
        const std::list<int>& kL = ifr.get();
        ____________________(kL);

        std::cout << "\n======== C c(c2); ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
        }

        std::cout << "\n======== C c(b, e); ========\n";
        {
                std::list<int> l(kL.begin(), kL.end());
                ____________________(l);
        }

        std::cout << "\n======== C<T> c; ========\n";
        {
                std::list<int> l;
                l.assign(kL.begin(), kL.end());
                ____________________(l);
        }

        std::cout << "\n======== C c(n, t); ========\n";
        {
                std::list<int>::size_type n = 8;
                int init_val = 100;
                std::list<int> l(n, init_val);
                ____________________(l);
        }

        std::cout << "\n======== C c(n); ========\n";
        {
                std::list<int>::size_type n = 8;
                std::list<int> l(n);
                ____________________(l);
        }

        std::cout << "\n======== resize() ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                l.resize(30);
                ____________________(l);
                l.resize(35, 500);
                ____________________(l);
        }

        std::cout << "\n======== front(), back() ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                std::cout << "l.front(): " << l.front() << std::endl;
                std::cout << "l.back(): " << l.back() << std::endl;
        }

        std::cout << "\n======== push_front(), push_back(), pop_front(), pop_back() ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                l.push_front(200);
                ____________________(l);
                l.push_back(300);
                ____________________(l);
                l.pop_front();
                ____________________(l);
                l.pop_back();
                ____________________(l);
        }

        std::cout << "\n======== insert() ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                std::list<int>::iterator it = std::find(l.begin(), l.end(), 7);
                it = l.insert(++++++++++it, 200); // it += 5
                std::cout << *it << std::endl;
                ____________________(l);
                l.erase(++it, l.end());
                ____________________(l);
        }

        std::cout << "\n======== sort() ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                l.sort();
                ____________________(l);
        }

        std::cout << "\n======== splice() ========\n";
        {
                std::list<int> l0(kL);
                std::list<int> l1(kL);
                ____________________(l0);
                ____________________(l1);
                std::list<int>::iterator it = std::find(l1.begin(), l1.end(), 7);
                l0.splice(++++l0.begin(), l1, it);
                ____________________(l0);
                ____________________(l1);
                it = std::find(l1.begin(), l1.end(), 37);
                l0.splice(l0.begin(), l1, it, l1.end());
                ____________________(l0);
                ____________________(l1);
        }

        std::cout << "\n======== remove() ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                l.remove(15);
                ____________________(l);
        }

        std::cout << "\n======== remove_if() ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                l.remove_if(std::bind2nd(std::less_equal<int>(), 50));
                ____________________(l);
        }

        std::cout << "\n======== unique() ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                l.sort();
                ____________________(l);
                l.unique();
                ____________________(l);
        }

        std::cout << "\n======== unique(binary_pred) ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                // l.unique(std::greater<int>());
                // ____________________(l);

                // l = kL;
                // ____________________(l);
                // l.unique(std::less<int>());
                // ____________________(l);

                // l = kL;
                // ____________________(l);
                l.unique(std::not_equal_to<int>());
                ____________________(l);

                l = kL;
                l.push_back(21);
                l.push_back(30);
                l.push_back(21);
                l.push_back(10);
                l.push_back(80);
                ____________________(l);
                l.unique(learning::nearby<int, 10>());
                ____________________(l);
        }

        std::cout << "\n======== reverse() ========\n";
        {
                std::list<int> l(kL);
                ____________________(l);
                l.reverse();
                ____________________(l);
        }

        std::cout << "\n======== swap() ========\n";
        {
                std::list<int> l0(kL);
                std::list<int> l1(kL);
                ____________________(l0);
                ____________________(l1);
                l1.sort();
                ____________________(l0);
                ____________________(l1);
                l0.swap(l1);
                ____________________(l0);
                ____________________(l1);
        }

        return EXIT_SUCCESS;
}
