// Copyright (c) 2018 Yuan "Forrest" Yu. All rights reserved.

// this demonstrates std::string can be modified via c_str() if we show no respect
//
// $ g++ -std=c++14 -Wall string_cstr.cc
// $ ./a.out
// hello
// Hello

// $ g++ --version
// Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
// Apple LLVM version 9.0.0 (clang-900.0.39.2)
// Target: x86_64-apple-darwin16.7.0
// Thread model: posix
// InstalledDir: /Library/Developer/CommandLineTools/usr/bin

#include <iostream>

int main()
{
        std::string stds = "hello";
        std::cout << stds << std::endl;
        char * p = (char*)stds.c_str();
        p[0] = 'H';
        std::cout << stds << std::endl;
}
