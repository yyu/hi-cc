#include <iostream>
#include <bitset>
#include <cstdio>

int main(int argc, char* argv[])
{
    int x = 314159;

    const int intlength = sizeof(int) * 8;

    for (int i = 0; i < 20; i++) {
        int y = x >> i;
        std::string str = std::bitset<intlength>(y).to_string();
        if (i == 0)
            printf("%10d       : %15d (%s)\n", x, y, str.c_str());
        else
            printf("%10d >> %2d : %15d (%s)\n", x, i, y, str.c_str());
    }
    printf("\n");

    for (int i = 0; i < 20; i++) {
        int y = x << i;
        std::string str = std::bitset<intlength>(y).to_string();
        if (i == 0)
            printf("%10d       : %15d (%s)\n", x, y, str.c_str());
        else
            printf("%10d << %2d : %15d (%s)\n", x, i, y, str.c_str());
    }
    printf("\n");

    x = -x;
    for (int i = 0; i < 20; i++) {
        int y = x >> i;
        std::string str = std::bitset<intlength>(y).to_string();
        if (i == 0)
            printf("%10d       : %15d (%s)\n", x, y, str.c_str());
        else
            printf("%10d >> %2d : %15d (%s)\n", x, i, y, str.c_str());
    }
    printf("\n");

    for (int i = 0; i < 20; i++) {
        int y = x << i;
        std::string str = std::bitset<intlength>(y).to_string();
        if (i == 0)
            printf("%10d       : %15d (%s)\n", x, y, str.c_str());
        else
            printf("%10d << %2d : %15d (%s)\n", x, i, y, str.c_str());
    }

    return 0;
}
