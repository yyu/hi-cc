#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
        {
                std::string::size_type n = 8;
                std::cout << std::string(n, '=') << '\n';
        }

        std::string hello = "Hello, World!";
        //            index: 0123456789ABC

        // string s(src, pos)
        // string s(src, pos, len)
        {
                std::string s(hello);

                std::string s1(s, 7);
                std::cout << s1 << '\n';

                std::string s2(s, 7, 5);
                std::cout << s2 << '\n';

                std::string s3(s, 7, 100);
                std::cout << s3 << '\n';
        }

        // s.insert(pos, n, c)
        {
                std::string s(hello);
                s.insert(12, 3, '.');
                std::cout << s << '\n';
        }

        // s.insert(pos, s2)
        {
                std::string s(hello);
                std::string s2("my ");
                s.insert(7, s2);
                std::cout << s << '\n';
        }

        // s.insert(pos, cp)
        {
                std::string s(hello);
                s.insert(7, "my ");
                std::cout << s << '\n';
        }

        // s.insert(pop, s2, pos2, len)
        {
                std::string s(hello);
                std::string s2("shit fucking damn");
                s.insert(7, s2, 5, 8);
                std::cout << s << '\n';
        }

        // s.insert(pos, cp, len)
        {
                std::string s(hello);
                const char cp[] = "fucking damn";
                s.insert(7, cp, 8);
                std::cout << s << '\n';
        }

        // s.substr(pos)
        {
                std::string s(hello);
                std::string s2 = s.substr(7);
                std::cout << s2 << '\n';
        }

        // s.substr(pos, n)
        {
                std::string s(hello);
                std::string s2 = s.substr(7, 5);
                std::cout << s2 << '\n';
        }

        // s.append(s2)
        {
                std::string s(hello);
                std::string s2("...");
                s.append(s2);
                std::cout << s << '\n';
        }

        // find all the numbers in a string
        {
                std::string s("r2d3");
                std::string numerics("0123456789");
                std::string::size_type pos = 0;
                while ((pos = s.find_first_of(numerics, pos)) != std::string::npos) {
                        std::cout << s << "[" << pos << "] : " << s[pos] << '\n';
                        ++pos;
                }
        }

        return 0;
}
