#include <iostream>
#include <bitset>
#include <cstdio>

int main(int argc, char* argv[])
{
    std::cout << "\n======== bitset ========\n";
    {
        int pi = 314159;
        std::cout << std::hex << pi << std::dec << "\n";

        std::bitset<sizeof(int)*8> bs(pi);
        std::cout << bs << "\n";

        std::bitset<sizeof(int)*8> bs1(std::string("01011011101111"));
        std::cout << bs1 << "\n";
    }

    std::cout << "\n======== bitset::to_string ========\n";
    {
        std::bitset<32> bs(314159);
        std::cout << bs.to_string() << "\n";
    }

    std::cout << "\n======== bitset::to_ulong ========\n";
    {
        std::bitset<32> bs(std::string("01011011101111"));
        unsigned long i = bs.to_ulong();
        printf("%s: %ld (%lX)\n", bs.to_string().c_str(), i, i);
    }

    std::cout << "\n======== bitset::any ========\n";
    {
        std::bitset<16> bs0(0);
        std::bitset<16> bs1(2);
        std::cout << bs0.any() << "\n";
        std::cout << bs1.any() << "\n";
    }

    std::cout << "\n======== bitset::none ========\n";
    {
        std::bitset<16> bs0(0);
        std::bitset<16> bs1(2);
        std::cout << bs0.none() << "\n";
        std::cout << bs1.none() << "\n";
    }

    std::cout << "\n======== bitset::count ========\n";
    {
        std::bitset<16> bs0(0);
        std::bitset<16> bs1(314);
        printf("%s: %d bits are set.\n",
               bs0.to_string().c_str(), bs0.count());
        printf("%s: %d bits are set.\n",
               bs1.to_string().c_str(), bs1.count());
    }

    std::cout << "\n======== bitset::flip ========\n";
    {
        std::bitset<16> bs(314);
        std::cout << bs << "\n";
        std::cout << bs.flip() << "\n";
        std::cout << bs.flip(1) << "\n";
    }

    std::cout << "\n======== bitset::operator[] ========\n";
    {
        std::bitset<16> bs(314);
        std::cout << bs << "\n";
        std::cout << "bs[1]: " << bs[1] << "\n";
        bs[1] = 0;
        std::cout << "bs[1]: " << bs[1] << "\n";
        std::cout << bs << "\n";
        std::cout << "bs[100] will NOT raise an exception"
                  << "(although it is not good practice):\n";
        std::cout << "bs[100]: " << bs[100] << "\n";
    }

    std::cout << "\n======== bitset::test ========\n";
    {
        std::cout << "Unlike access operator ([]), this function"
                  << " performs a range check on pos before retrieveing"
                  << " the bit value.\n";
        std::bitset<16> bs(314);
        std::cout << bs << "\n";
        std::cout << "bs.test(1): " << bs.test(1) << "\n";
        std::cout << "bs.test(2): " << bs.test(2) << "\n";
        std::cout << "bs.test(100) will raise an exception.\n";
    }

    std::cout << "\n======== bitset::reset ========\n";
    {
        std::bitset<16> bs(314);
        std::cout << bs << "\n";
        bs.reset(1);
        std::cout << bs << "\n";
        bs.reset();
        std::cout << bs << "\n";
    }

    std::cout << "\n======== bitset::set ========\n";
    {
        std::bitset<16> bs(314);
        std::cout << bs << "\n";
        bs.set(2);
        std::cout << bs << "\n";
        bs.set();
        std::cout << bs << "\n";
        bs.set(2, false);
        std::cout << bs << "\n";
    }

    std::cout << "\n======== bitset::size ========\n";
    {
        std::bitset<16> bs(314);
        std::cout << bs << "\n";
        std::cout << "size: " << bs.size() << "\n";
    }

    return 0;
}
