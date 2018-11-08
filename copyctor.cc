// Copyright (c) 2018 Yuan "Forrest" Yu. All rights reserved.

// this demonstrates copying a class with member whose copy constructor is deleted -- you cannot do it, it doesn't compile
//
// $ g++ -std=c++14 -Wall copyctor.cc 
// copyctor.cc:47:7: error: call to implicitly-deleted copy constructor of 'B'
//     B b2 = b;
//       ^    ~
// copyctor.cc:40:11: note: copy constructor of 'B' is implicitly deleted because field 'a_' has a deleted copy constructor
//         A a_;
//           ^
// copyctor.cc:31:9: note: 'A' has been explicitly marked deleted here
//         A(const A &) = delete;
//         ^
// 1 error generated.

// $ g++ --version
// Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
// Apple LLVM version 9.0.0 (clang-900.0.39.2)
// Target: x86_64-apple-darwin16.7.0
// Thread model: posix
// InstalledDir: /Library/Developer/CommandLineTools/usr/bin

#include <iostream>

class A {
    public:
        A() { std::cout << "A::A()\n"; }
        ~A() { std::cout << "A::~A()\n"; }

        A(const A &) = delete;
        A(A &&) = delete;
};

class B {
    public:
        B() { std::cout << "B::B()\n"; }
        ~B() { std::cout << "B::~B()\n"; }
    private:
        A a_;
};


int main(int argc, char * argv [])
{
    B b;
    B b2 = b;
    return 0;
}
