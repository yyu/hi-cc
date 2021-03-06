#include <iostream>
#include <fstream>
#include <cstdlib>

void rewind(std::ifstream& in)
{
    in.clear();
    in.seekg(0, std::ios_base::beg);
}

int main(int argc, char * argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    std::ifstream ifile(argv[1]);
    if (!ifile) {
        perror("failed to open file");
        return EXIT_FAILURE;
    }

    // read by line
    // http://rosettacode.org/wiki/Read_a_file_line_by_line#C.2B.2B
    std::string line;
    int i = 0;
    // about ``getline()'':
    // - http://en.cppreference.com/w/cpp/string/getline
    // - http://augustcouncil.com/~tgibson/tutorial/iotips.html
    while (std::getline(ifile, line)) {
        printf("%3d : %s\n", ++i, line.c_str());
    }

    // rewind
    rewind(ifile);

    // read by word
    std::string word;
    while (ifile >> word)
        printf(" + %s", word.c_str());
    printf("\n");

    // rewind
    rewind(ifile);

    // read by int
    //ifile.exceptions( std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    int num;
    //while (!ifile.eof()) {
    while (ifile.good()) {
        ifile >> num;
        if (ifile.rdstate() & std::ifstream::failbit) {
            ifile.clear();
            ifile >> word;
            printf("! this is not a number: %s\n", word.c_str());
        } else {
            printf("got %3d\n", num);
        }
    }

    // rewind
    rewind(ifile);

    // read entire file as string
    // http://rosettacode.org/wiki/Read_entire_file#C.2B.2B
    std::istreambuf_iterator<char> ifbegin(ifile);
    std::istreambuf_iterator<char> ifend;
    std::string fileData(ifbegin, ifend);
    printf("\n--------\n%s\n--------\n", fileData.c_str());

    ifile.close();

    return EXIT_SUCCESS;
}
