#include <iostream>
#include <vector>
#include <limits>

#include <cstdio>
#include <cassert>

#define RED      "\033[31m"
#define GREEN    "\033[32m"
#define YELLOW   "\033[33m"
#define BLUE     "\033[34m"
#define MAGENTA  "\033[35m"
#define GRAY     "\033[37m"
#define NOCOLOR  "\033[0m"

template <typename T>
void test(const std::string& t, const std::string& specifier)
{
    std::cout << "\n" << RED << t
              << std::string(80 - t.length(), '-') << NOCOLOR;

    const T INFTY   = std::numeric_limits<T>::infinity();
    const T epsilon = std::numeric_limits<T>::epsilon();
    const T max     = std::numeric_limits<T>::max();
    const T min     = std::numeric_limits<T>::min();

    std::vector< std::pair<std::string, T> > vec;

    vec.push_back(std::make_pair("∞ ("+t+")",   INFTY));
    vec.push_back(std::make_pair("-∞ ("+t+")", -INFTY));
    vec.push_back(std::make_pair("𝜖 ("+t+")",    epsilon));
    vec.push_back(std::make_pair("-𝜖 ("+t+")",  -epsilon));
    vec.push_back(std::make_pair("max ("+t+")",  max));
    vec.push_back(std::make_pair("min ("+t+")",  min));

    std::string fmt = YELLOW"printf"NOCOLOR"      "GREEN + specifier + NOCOLOR"\n";
    for (typename std::vector< std::pair<std::string, T> >::iterator it
             = vec.begin(); it != vec.end(); ++it) {
        std::cout << "\n"BLUE << it->first << ":"NOCOLOR"\n";

        std::cout << YELLOW"std::cout"NOCOLOR"   "GREEN
                  << it->second << NOCOLOR"\n";
        printf(fmt.c_str(), it->second);

        const unsigned char* p =
            reinterpret_cast<const unsigned char*>(&(it->second));
        printf(GRAY"byte index: ");
        int n = sizeof(T);
        for (int i = n - 1; i >= 0; i--)
            printf("%2d ", i);
        printf("\n       HEX: "MAGENTA);
        for (int i = n - 1; i >= 0; i--)
            printf("%02X ", p[i]);
        printf(NOCOLOR"\n");

        printf(GRAY" bit index:|");
        for (int i = n * 8 - 1; i >= 0; i--) {
            printf("%c", i / 10 ? i / 10 + '0' : ' ');
            if (i && i % 4 == 0)
                printf(" ");
        }
        printf("|\n           |");
        for (int i = n * 8 - 1; i >= 0; i--) {
            printf("%d", i % 10);
            if (i && i % 4 == 0)
                printf(" ");
        }
        printf("|\n       BIN: "MAGENTA);
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 7; j >= 4; j--)
                printf("%d", p[i] >> j & 1);
            printf(" ");
            for (int j = 3; j >= 0; j--)
                printf("%d", p[i] >> j & 1);
            printf(" ");
        }
        printf(NOCOLOR"\n");

    }
 
    double inf1 = INFTY;
    double inf2 = INFTY;
    assert(inf1 == inf2);

    assert(max < INFTY);
    assert(min > -INFTY);
    assert(!(max > INFTY));
    assert(!(min < -INFTY));
    assert(!(max >= INFTY));
    assert(!(min <= -INFTY));
}

int main(int argc, char* argv[])
{
    // See:
    //   - http://www.cplusplus.com/reference/std/limits/numeric_limits/
    //   - http://en.wikipedia.org/wiki/Single_precision
    //   - http://en.wikipedia.org/wiki/Double_precision

    {
        // from:
        //     http://msdn.microsoft.com/en-us/library/6hthw3cb%28v=vs.80%29.aspx
        // slightly modified
        std::cout << std::numeric_limits<float>::has_infinity << std::endl;
        std::cout << std::numeric_limits<double>::has_infinity << std::endl;
        std::cout << std::numeric_limits<long double>::has_infinity << std::endl;
        std::cout << std::numeric_limits<int>::has_infinity << std::endl;
        std::cout << std::numeric_limits<long long int>::has_infinity << std::endl;
     
        std::cout << "The representation of infinity for type float is: "
                  << std::numeric_limits<float>::infinity( ) << std::endl;
        std::cout << "The representation of infinity for type double is: "
                  << std::numeric_limits<double>::infinity( ) << std::endl;
        std::cout << "The representation of infinity for type long double is: "
                  << std::numeric_limits<long double>::infinity( ) << std::endl;
    }

    test<float>("float", "%f");
    test<double>("double", "%f");
    test<long double>("long double", "%Lf");

    return 0;
}

