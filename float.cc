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
void print_float(T f)
{
    printf(GREEN"%Lf"NOCOLOR":\n", static_cast<long double>(f));
    unsigned char* p = (unsigned char*)(&f);

    int n = sizeof(f);

    printf(GRAY"byte index: ");
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

int main(int argc, char* argv[])
{
    // See:
    //   - http://www.cplusplus.com/reference/std/limits/numeric_limits/
    //   - http://en.wikipedia.org/wiki/Single_precision
    //   - http://en.wikipedia.org/wiki/Double_precision
    // Also see:
    //   ~/local/src/mine/C++/limits.cc

    float infty   = std::numeric_limits<float>::infinity();
    float epsilon = std::numeric_limits<float>::epsilon();

    float f;

    printf("0:\n");
    print_float(0.0);
    print_float(-0.0);
    assert(0.0 == -0.0);

    printf("𝜖:\n");
    print_float(epsilon);

    printf("∞:\n");
    print_float(infty);
    print_float(-infty);
    assert( infty + infty ==  infty);
    assert(-infty - infty == -infty);
    assert( infty + 3.14  ==  infty);
    assert( infty - 3.14  ==  infty);

    printf("NaN:\n");
    std::vector<float> NaNs;
    NaNs.push_back(std::numeric_limits<float>::quiet_NaN());
    NaNs.push_back(std::numeric_limits<float>::signaling_NaN());
    NaNs.push_back(  infty  -   infty );
    NaNs.push_back( -infty  +   infty );
    NaNs.push_back(  infty  /   infty );
    NaNs.push_back( -infty  /   infty );
    NaNs.push_back(  infty  / (-infty));
    NaNs.push_back(  infty  *       0 );
    NaNs.push_back( -infty  *       0 );
    NaNs.push_back((-infty) *       0 );
    NaNs.push_back(      0  *   infty );
    NaNs.push_back(      0  * (-infty));
    for (std::vector<float>::iterator it = NaNs.begin(); it != NaNs.end(); ++it) {
        print_float(*it);
        print_float(-*it);
	assert(*it != *it);
    }

    f = 5.625;
    print_float(f);
    print_float(f * f);

    f = 0.125;
    print_float(f);

    f = 1.5625;
    print_float(f);

    f = 25;
    print_float(f);

    f = 2e-45;  // subnormal number
    print_float(f);

    double d = 5.625;
    print_float(d);

    long double ld = 5.625;
    print_float(ld);

#if 0
    float x = 268435453.0;
    for (int i = 0; i < 2; i++)
        print_float(x + i);
#endif

    // 大于 2²⁴ 的整数，单精度捉襟见肘
    float a[] = {
        16777214.0,  // 0xFFFFFE
        16777215.0,  // 0xFFFFFF
        16777216.0,  // 0x1000000, 1.0 * 2²⁴  :)
        16777217.0,  // 0x1000001, 1.000000000000000000000001 * 2²⁴
        16777218.0,  // 0x1000002, 1.00000000000000000000001  * 2²⁴
        16777219.0,  // 0x1000003, 1.000000000000000000000011 * 2²⁴
        16777220.0,  // 0x1000004, 1.00000000000000000000010  * 2²⁴
        16777221.0,  // 0x1000004, 1.000000000000000000000101 * 2²⁴
        16777222.0,  // 0x1000004, 1.00000000000000000000011  * 2²⁴
        16777223.0,  // 0x1000004, 1.000000000000000000000111 * 2²⁴
        16777224.0,  // 0x1000004, 1.00000000000000000000100  * 2²⁴
    };
    for (size_t i = 0; i < sizeof(a) / sizeof(*a); i++)
        print_float(a[i]);

    return 0;
}

