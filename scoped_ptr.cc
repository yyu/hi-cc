// Copyright (c) 2011 Forrest Y. Yu. All rights reserved.
#include <iostream>
#include <boost/scoped_ptr.hpp>

class A {
public:
        A()  {std::cout << "A::A()\n";}
        ~A() {std::cout << "A::~A()\n";}

        void foo(void) {std::cout << "A::foo()\n";}
private:
        boost::scoped_ptr<int> p_;
};

class B {
public:
        B() : pa_(new A)  {std::cout << "B::B()\n";}
        ~B() {std::cout << "B::~B()\n";}

        void foo(void);
private:
        // this is pliable to have memory leak:
        //     A* pa_;
        // so let's use scoped_ptr
        boost::scoped_ptr<A> pa_;
};

void B::foo(void) {
        std::cout << "B::foo()::begin\n";
        pa_->foo();
        std::cout << "B::foo()::end\n";
}

int main(int argc, char * argv [])
{
        B b;
        b.foo();
        return 0;
}
