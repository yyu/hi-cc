#include <iostream>
#include <fstream>

int main(int argc, char * argv[])
{
    if (argc != 2) {
        std::cerr << argv[0] << " filename\n";
        return 1;
    }

    std::ofstream ofile(argv[1], std::ios::app);
    if (ofile.is_open())
        ofile << "foo bar baz" << std::endl;
    else
        std::cerr << "Failed to open file.\n";

    std::cout << "Done.\n";

    return 0;
}
