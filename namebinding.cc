#include <iostream>

// See Cracking the Coding Interview, Exercise 13.6 - What is name hiding in C++?

class FirstClass {
public:
    virtual void MethodA (int)      {std::cout << "ONE!!\n";}
    virtual void MethodA (int, int) {std::cout << "TWO!!\n";}
};

// This is a simple class with two methods (or one overloaded method).
// If you want to override the one-parameter version, you can do the following:
class SecondClass : public FirstClass {
public:
    void         MethodA (int)      {std::cout << "THREE!!\n";}

#if 0  // In C++, when you have a class with an overloaded method, and you then extend and override that method, you must override all of the overloaded methods.
    void         MethodA (int, int) {std::cout << "FOUR!!\n";}
#endif

};

int main(int argc, char* argv[])
{
    SecondClass a;
    a.MethodA (1);

    a.MethodA (1, 1);  // error: no matching function for call to ‘SecondClass::MethodA(int, int)’

    return 0;
}

