#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// an ordinary class
class Foo {
public:
    void func() {std::cout << m_ << "\n";}
private:
    static int m_;
};

int Foo::m_ = 123;

////////////////////////////////////////////////////////////////////////////////
// a template class
template <typename T>
class Bar {
public:
    void func() {std::cout << m_ << "\n";}
    static T m_;
};

template <typename T>
T Bar<T>::m_;

////////////////////////////////////////////////////////////////////////////////
// test code
int main(int argc, char* argv[]) {
    Foo foo;
    foo.func();

    Bar<int>::m_ = 45;
    Bar<int> bar;
    bar.func();

    Bar<float> bar2;
    Bar<float>::m_ = 3.14;
    bar2.func();

    return 0;
}
