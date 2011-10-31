#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
    {  // stringstream::stringstream()
        std::cout << std::string(80, '-') << '\n';
        std::stringstream ss;
        ss << "pi: " << 3.14 << '\n';
        std::string s = ss.str();
        std::cout << s;
    }

    {  // stringstream::stringstream(cosnt std::string&)
        std::cout << std::string(80, '-') << '\n';
        std::string s = "I have a dream!";
        std::stringstream ss(s);
        std::string w;
        while (ss >> w)
            std::cout << w << "\n";
    }

    {  // istringstream::istringstream(cosnt std::string&)
        std::cout << std::string(80, '-') << '\n';
        std::string s = "I have a dream!";
        std::istringstream ss(s);
        std::string w;
        while (ss >> w)
            std::cout << w << "\n";
    }

    {  // Bad: ostringstream::operator<< without calling seekp()
        std::cout << std::string(80, '-') << '\n';

        std::string s = "I have a dream";
        std::ostringstream ss(s);

        std::cout << ss.str() << "\n";
        ss << "x-y-z";
        std::cout << ss.str() << "\n";
    }

    {  // Good: seekp() before calling ostringstream::operator<< 
        std::cout << std::string(80, '-') << '\n';

        std::string s = "I have a dream";
        std::ostringstream ss(s);

        std::cout << ss.tellp() << "\n";
        std::cout << ss.str() << "\n";

        ss.seekp(0, std::ios_base::end);
        std::cout << ss.tellp() << "\n";

        ss << " today!";
        std::cout << ss.str() << "\n";
    }

    {  // use stringstream as ostringstream and as istringstream
        std::cout << std::string(80, '-') << '\n';
        std::string s = "I have a dream";
        std::stringstream ss(s);

        // as ostringstream
        ss.seekp(0, std::ios_base::end);
        ss << " today!";
        std::cout << ss.str() << "\n";

        // as istringstream
        std::string w;
        while (ss >> w)
            std::cout << w << "\n";
    }

    return 0;
}
