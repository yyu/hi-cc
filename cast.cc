// Compiler:
//     $ g++ --version
//     g++ (Ubuntu/Linaro 4.5.2-8ubuntu4) 4.5.2
//     Copyright (C) 2010 Free Software Foundation, Inc.
//     This is free software; see the source for copying conditions.  There is NO
//     warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

// How to Build:
//     $ g++ -g -Wall -o foo cast.cc && ./foo

#include <iostream>

void func01(const char * x)  {std::cout << x << std::endl;}
void func02(char x)          {std::cout << x << std::endl;}
void func03(double x)        {std::cout << x << std::endl;}
void func04(unsigned char x) {std::cout << x << std::endl;}

int main(int argc, char * argv[])
{
	// const_cast
	// const char * => char *
	{
		char s[]        = "hello world";
		const char cs[] = "bye world";

		func01(s);

		const char * p = NULL;
		p = s;                                 // OK (no casting needed)
		p = const_cast<const char *>(s);       // OK
		p = static_cast<const char *>(s);      // OK (because func01(s) succeeds)
		// p = dynamic_cast<const char *>(s);  // compiling error: cannot dynamic_cast ‘s’ (of type ‘char [12]’) to type ‘const char*’ (target is not pointer or reference to class)
		p = reinterpret_cast<const char *>(s); // OK

		char * q = NULL;
		q = const_cast<char*>(cs);          // GOOD
		// q = static_cast<char*>(cs);      // compiling error: invalid static_cast from type ‘const char [10]’ to type ‘char*’
		// q = dynamic_cast<char*>(cs);     // compiling error: cannot dynamic_cast ‘cs’ (of type ‘const char [10]’) to type ‘char*’ (target is not pointer or reference to class)
		// q = reinterpret_cast<char*>(cs); // compiling error: reinterpret_cast from type ‘const char*’ to type ‘char*’ casts away qualifiers

		std::cout << "s:"  << s  << ", " << "cs:" << cs << ", " << "p:"  << std::string(p ? p : "NULL")  << ", " << "q:"  << q << std::endl;
	}

	// static_cast
	// int   => char
	// float => double
	// char  => unsigned char
	{
		typedef unsigned char BYTE;

		char ch = 'Z';
		int i = 65;
		float f = 2.5;
		double dbl;

		func02(i);
		func03(f);
		func04(ch);

		// ch  = const_cast<char>(i);       // compiling error: invalid use of const_cast with type ‘char’, which is not a pointer, reference, nor a pointer-to-data-member type
		ch  = static_cast<char>(i);         // GOOD (because func02(i) succeeds)
		// ch  = dynamic_cast<char>(i);     // compiling error: cannot dynamic_cast ‘i’ (of type ‘int’) to type ‘char’ (target is not pointer or reference)
		// ch  = reinterpret_cast<char>(i); // compiling error: invalid cast from type ‘int’ to type ‘char’

		// dbl = const_cast<char>(f);       // compiling error: invalid use of const_cast with type ‘char’, which is not a pointer, reference, nor a pointer-to-data-member type
		dbl = static_cast<double>(f);       // GOOD (because func03(f) succeeds)
		// dbl = dynamic_cast<char>(f);     // compiling error: cannot dynamic_cast ‘f’ (of type ‘float’) to type ‘char’ (target is not pointer or reference)
		// dbl = reinterpret_cast<char>(f); // compiling error: invalid cast from type ‘float’ to type ‘char’

		// i   = const_cast<BYTE>(ch);      // compiling error: invalid use of const_cast with type ‘BYTE’, which is not a pointer, reference, nor a pointer-to-data-member type
		i   = static_cast<BYTE>(ch);        // GOOD (because func04(ch) succeeds)
		// i   = dynamic_cast<BYTE>(ch);    // compiling error: cannot dynamic_cast ‘ch’ (of type ‘char’) to type ‘BYTE’ (target is not pointer or reference)
		// i   = reinterpret_cast<BYTE>(ch);// compiling error: invalid cast from type ‘char’ to type ‘BYTE’

		std::cout << "i:"   << i   << ", " << "ch:"  << ch  << ", " << "f:"   << f   << ", " << "dbl:" << dbl << ", " << std::endl;
	}

	// reinterpret_cast
	// int* => int
	// int => int*
	// char* => int*
	// void* => int*
	// One_class* => Unrelated_class*
	{
		// --------------------
		// int* <=> int
		int i = 3;
		int * p = &i;

		unsigned int j = 0;
		// j = const_cast<unsigned int>(p);    // compiling error: invalid use of const_cast with type ‘int’, which is not a pointer, reference, nor a pointer-to-data-member type
		// j = static_cast<unsigned int>(p);   // compiling error: invalid static_cast from type ‘int*’ to type ‘int’
		// j = dynamic_cast<unsigned int>(p);  // compiling error: cannot dynamic_cast ‘p’ (of type ‘int*’) to type ‘int’ (target is not pointer or reference)
		j = reinterpret_cast<unsigned int>(p); // GOOD

		// p = const_cast<int*>(j);    // compiling error: invalid const_cast from type ‘unsigned int’ to type ‘int*’
		// p = static_cast<int*>(j);   // compiling error: invalid static_cast from type ‘unsigned int’ to type ‘int*’
		// p = dynamic_cast<int*>(j);  // compiling error: cannot dynamic_cast ‘j’ (of type ‘unsigned int’) to type ‘int*’ (target is not pointer or reference to class)
		p = reinterpret_cast<int*>(j); // GOOD

		double d;
		// d = const_cast<unsigned int>(p);    // compiling error: invalid use of const_cast with type ‘unsigned int’, which is not a pointer, reference, nor a pointer-to-data-member type
		// d = static_cast<unsigned int>(p);   // compiling error: invalid static_cast from type ‘int*’ to type ‘unsigned int’
		// d = dynamic_cast<unsigned int>(p);  // compiling error: cannot dynamic_cast ‘p’ (of type ‘int*’) to type ‘unsigned int’ (target is not pointer or reference)
		d = reinterpret_cast<unsigned int>(p); // OK but NO GOOD

		std::cout << "i:" << i << ", "
			  << "p:" << p << ", "
			  << std::hex << "j:" << j << ", "
			  << std::dec
			  << std::endl;

		// --------------------
		// char* => int*
		char s[] = "hello world";
		// p = const_cast<int*>(s);    // compiling error: invalid const_cast from type ‘char*’ to type ‘int*’
		// p = static_cast<int*>(s);   // compiling error: invalid static_cast from type ‘char [12]’ to type ‘int*’
		// p = dynamic_cast<int*>(s);  // compiling error: cannot dynamic_cast ‘s’ (of type ‘char [12]’) to type ‘int*’ (target is not pointer or reference to class)
		p = reinterpret_cast<int*>(s); // compiling 

		// --------------------
		// void* => int*
		void * q = &i;
		// p = const_cast<int*>(q);    // compiling error: invalid const_cast from type ‘void*’ to type ‘int*’
		p = static_cast<int*>(q);      // OK
		// p = dynamic_cast<int*>(q);  // compiling error: cannot dynamic_cast ‘q’ (of type ‘void*’) to type ‘int*’ (target is not pointer or reference to class)
		p = reinterpret_cast<int*>(q); // OK

		// --------------------
		// One_class* => Unrelated_class*
		class X {};
		class Y {};
		X * x = new X;
		Y * y = NULL;
		// y = const_cast<Y*>(x);    // compiling error: invalid const_cast from type ‘X*’ to type ‘Y*’
		// y = static_cast<Y*>(x);   // compiling error: invalid static_cast from type ‘X*’ to type ‘Y*’
		// y = dynamic_cast<Y*>(x);  // compiling error: cannot dynamic_cast ‘x’ (of type ‘class X*’) to type ‘class Y*’ (source type is not polymorphic)
		y = reinterpret_cast<Y*>(x); // OK
		delete x;
	}

	////////////////////////////////////////////////////

	// Derived => Base
	{
		class B {};
		class D : public B {};

		D * d = new D;
		B * b = NULL;
		// b = const_cast<B*>(d);    // compiling error: invalid const_cast from type ‘D*’ to type ‘B*’
		b = static_cast<B*>(d);      // OK
		b = dynamic_cast<B*>(d);     // OK
		b = reinterpret_cast<B*>(d); // OK
		delete d;
	}

	// Base => Derived
	{
		class B {};
		class D : public B {};

		B * b = new B;
		D * d = NULL;
		// d = const_cast<D*>(b);    // compiling error: invalid const_cast from type ‘B*’ to type ‘D*’
		d = static_cast<D*>(b);      // OK
		// d = dynamic_cast<D*>(b);  // compiling cannot dynamic_cast ‘b’ (of type ‘class B*’) to type ‘class D*’ (source type is not polymorphic)
		d = reinterpret_cast<D*>(b); // OK
		delete b;
	}

	// Base => Derived (with RTTI)
	{
		class B {
		public:
			// Since RTTI is included in the virtual method table there should be at least one virtual function.
			virtual void test(void) {};
		};
		class D : public B {
		public:
			void MethodSpecificToD(void) {std::cout << "inside D" << std::endl;};
		};

		B * b = new D;
		D * d = NULL;
		// d = const_cast<D*>(b);    // compiling error: invalid const_cast from type ‘B*’ to type ‘D*’
		d = static_cast<D*>(b);      // OK
		d = dynamic_cast<D*>(b);     // OK
		if (d != NULL)
			d->MethodSpecificToD();
		else
			std::cerr << "dynamic_cast error" << std::endl;
		d = reinterpret_cast<D*>(b); // OK
		delete b;
	}


	std::cout << std::endl;

	return 0;
}
