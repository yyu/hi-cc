#include <iostream>

/*

$ g++ -DWILL_NOT_COMPILE function.cc && ./a.out
function.cc:44:47: error: call to non-static member function without an object argument
    std::cout << " Foo::meth " << (long)(Foo::meth) << "." << std::endl;
                                         ~~~~~^~~~
function.cc:47:35: error: C-style cast from 'int (Foo::*)(int)' to 'long' is not allowed
    std::cout << "&Foo::meth " << (long)&Foo::meth << "." << std::endl;
                                  ^~~~~~~~~~~~~~~~
function.cc:50:40: error: reference to non-static member function must be called
    std::cout << " foo.meth " << (long)(foo.meth) << "." << std::endl;
                                       ^~~~~~~~~~
function.cc:53:41: error: cannot create a non-constant pointer to member function
    std::cout << "&foo.meth " << (long)(&foo.meth) << "." << std::endl;
                                        ^~~~~~~~~
4 errors generated.

 */

//#define WILL_NOT_COMPILE

int func(int x)
{
    return x + 1;
}

class Foo
{
public:
    int meth(int x) { return x + 10; }
};

int main(int argc, char * argv[])
{
    std::cout << " func " << (long)func << "." << std::endl;
    std::cout << "&func " << (long)(&func) << "." << std::endl;

    Foo foo;

#ifdef WILL_NOT_COMPILE
    // error: call to non-static member function without an object argument
    std::cout << " Foo::meth " << (long)(Foo::meth) << "." << std::endl;

    // error: C-style cast from 'int (Foo::*)(int)' to 'long' is not allowed
    std::cout << "&Foo::meth " << (long)&Foo::meth << "." << std::endl;

    // error: reference to non-static member function must be called
    std::cout << " foo.meth " << (long)(foo.meth) << "." << std::endl;

    // error: cannot create a non-constant pointer to member function
    std::cout << "&foo.meth " << (long)(&foo.meth) << "." << std::endl;
#endif

    return EXIT_SUCCESS;
}
