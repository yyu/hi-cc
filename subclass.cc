#include <iostream>

namespace A {
class Base {
public:
    Base() { std::cout << "A::Base::constructor\n"; }
    virtual ~Base() { std::cout << "A::Base::destructor\n"; }
private:
    int i_;
};

class Sub : public Base {
public:
    Sub() { // Base class constructors are automatically called if they have no argument
        std::cout << "A::Sub::constructor\n";
    }
    ~Sub() { std::cout << "A::Sub::destructor\n"; }
};
} // end of name space A

namespace B {
class Base {
public:
    Base(int i) : i_(i) { std::cout << "B::Base::constructor\n"; }
    virtual ~Base() { std::cout << "B::Base::destructor\n"; }
private:
    int i_;
};

class Sub : public Base{
public:
    Sub(int i, int j)
        : Base(i + j), // If you want to call a superclass constructor with an argument, you must use the subclass's constructor initialization list.
          j_(j)
    {
        std::cout << "B::Sub::constructor\n";
    }
    ~Sub() { std::cout << "B::Sub::destructor\n"; }
private:
    int j_;
};
} // end of name space B

namespace C {
class Base {
public:
    Base() { std::cout << "C::Base::constructor\n"; }
    virtual ~Base() { std::cout << "C::Base::destructor\n"; }
    virtual void foo() { std::cout << "C::Base::foo\n"; }
protected:
    virtual void bar() { std::cout << "C::Base::bar\n"; }
};

class Sub : public Base{
public:
    Sub() { std::cout << "C::Sub::constructor\n"; }
    ~Sub() { std::cout << "C::Sub::destructor\n"; }
    void foo() {
        std::cout << "C::Sub::foo\n";
        Base::bar();
        bar();
    }
private:
    void bar() { std::cout << "C::Sub::bar\n"; }
};
} // end of name space C

int main(int argc, char* arv[])
{
    {
        A::Base * p = new A::Sub;
        delete p;
    }

    {
        B::Base * p = new B::Sub(2, 3);
        delete p;
    }

    {
        C::Base * p = new C::Sub;
        p->foo();
        delete p;
    }

    return 0;
}
