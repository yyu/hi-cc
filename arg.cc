// Copyright (c) 2011 Forrest Y. Yu. All rights reserved.

// no error checked by Google's cpplint.py:
//     $ cpplint.py arg.cc
//     Done processing arg.cc
//     Total errors found: 0

// #include <iostream>  <-- cpplint.py doesn't like streams
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char * argv[]) {
        typedef std::vector<std::string> strvec;
        strvec params(argv, argv + argc);

        for (strvec::const_iterator it = params.begin();
             it != params.end(); ++it) {
                // std::cout << *it << "+";
                printf("%s+", it->c_str());
        }
        // std::cout << std::endl;
        printf("\n");

        for (int i = 1; i < argc; ++i) {
                // std::cout << params[i] << "#";
                printf("%s#", params[i].c_str());
        }
        // std::cout << std::endl;
        printf("\n");

        return EXIT_SUCCESS;
}
