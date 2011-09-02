#include <iostream>

/*
 * http://blogs.msdn.com/b/vcblog/archive/2009/02/03/rvalue-references-c-0x-features-in-vc10-part-2.aspx
 *
 * See Also: C++ Annotations §3.3.2 Rvalue References (C++0x)  pp.38

lvalues and rvalues in C++98/03
-------------------------------

- C++03 3.10/1 says: "Every expression is either an lvalue or an rvalue."

- lvalueness versus rvalueness is a property of expressions, not of objects.

- lvalues name objects that persist beyond a single expression. For example,
	obj, *ptr, ptr[index], and ++x are all lvalues.

- Rvalues are temporaries that evaporate at the end of the full-expression in which they live ("at the semicolon"). For example,
	1729, x + y, std::string("meow"), and x++ are all rvalues.

- ++x vs. x++
	Notice the difference between ++x and x++.
	If we have int x = 0; then
	- the expression x is an lvalue, as it names a persistent object.
	- the expression ++x is also an lvalue. It modifies and then names the persistent object.
	- the expression x++ is an rvalue. It copies the original value of the persistent object, modifies the persistent object, and then returns the copy.
	  This copy is a temporary.
	- Both ++x and x++ increment x, but
		- ++x returns the persistent object itself, while
		- x++ returns a temporary copy.
	  That's why ++x is an lvalue, while x++ is an rvalue.

- (++x vs. x++ tells us) Lvalueness versus rvalueness
	- doesn't care about what an expression does,
	- it cares about what an expression names (something persistent or something temporary).


- another way to determine whether an expression is an lvalue:
	to ask:
		"can I take its address?".
	If you can,   it's an lvalue.
	If you can't, it's an rvalue.
  For example,
  	&obj, &*ptr, &ptr[index], and &++x are all valid, while &1729, &(x + y), &std::string("meow"), and &x++ are all invalid.
  Why does this work?
  	The address-of operator requires that its "operand shall be an lvalue" (C++03 5.3.1/2).
  Why does it require that?
  	Taking the address of a persistent object is fine, but taking the address of a temporary would be extremely dangerous, because temporaries evaporate quickly.

- "A function call is an lvalue if and only if the result type is a reference." (C++03 5.2.2/10)
  Therefore,
	given vector<int> v(10, 1729);
  		v[0] is an lvalue because operator[]() returns int& (and &v[0] is valid and useful)
	given string s("foo"); and string t("bar");
		s + t is an rvalue because operator+() returns string (and &(s + t) is invalid).

- Both lvalues and rvalues can be either modifiable (non-const) or non-modifiable (const).  Here are examples:

	string one("cute");
	const string two("fluffy");
	string three() { return "kittens"; }
	const string four() { return "are an essential part of a healthy diet"; }

	one;     // modifiable lvalue
	two;     // const lvalue
	three(); // modifiable rvalue
	four();  // const rvalue

- Type&
	- binds to          modifiable lvalues  (and can be used to observe and mutate them).
	- It can't bind to  const lvalues      , as that would violate const correctness.
	- It can't bind to  modifiable rvalues , as that would be extremely dangerous.
							Accidentally modifying temporaries, only to have the temporaries evaporate along with your modifications,
							would lead to subtle and obnoxious bugs, so C++ rightly prohibits this.
	- it can't bind to  const rvalues      , as that would be doubly bad.  (Careful readers should note that I'm not talking about template argument deduction here.)
- const Type&
	- binds to everything:
			    modifiable lvalues ,
			    const lvalues      ,
			    modifiable rvalues ,
			    const rvalues        (and can be used to observe them).

- a reference bound to an rvalue: lvalue
	A reference is a name, so a reference bound to an rvalue is itself an lvalue (yes, L).
	(As only a const reference can be bound to an rvalue, it will be a const lvalue.)
  Explanation:
	Given the function
		void observe(const string& str)
	inside observe()'s implementation, str is a const lvalue, and its address can be taken and used before observe() returns.
	This is true even though observe() can be called with rvalues, such as three() or four() above.
	observe("purr") can also be called, which constructs a temporary string and binds str to that temporary.
	The return values of three() and four() don't have names, so they're rvalues, but within observe(), str is a name, so it's an lvalue.
	As I said above, "lvalueness versus rvalueness is a property of expressions, not of objects".
	Of course, because str can be bound to a temporary which will evaporate, its address shouldn't be stored anywhere where it could be used after observe() returns.

- real examples of binding an rvalue to a const reference and then taken its address
	Have you ever bound an rvalue to a const reference and then taken its address? Yes, you have!
	This is what happens when you write a copy assignment operator,
		Foo& operator=(const Foo& other)
	with a self-assignment check
		if (this != &other) {
			copy stuff;
		}
		return *this;
	and you copy assign from a temporary, like
		Foo make_foo();
		Foo f;
		f = make_foo();

- modifiable rvalues vs. const rvalues  (what does ``modifiable'' mean?)
	At this point, you might ask, "So what's the difference between modifiable rvalues and const rvalues?
	I can't bind Type& to modifiable rvalues, and I can't assign things (etc.) to modifiable rvalues, so can I really modify them?"
	  ``````````````````` ^^^^^^^^^^                ````````````````````````````` ^^^^^^^^^^                          ^^^^^^
	This is a very good question!
	In C++98/03, the answer is that there's a slight difference: non-const member functions can be called on modifiable rvalues.
	C++ doesn't want you to accidentally modify temporaries, but directly calling a non-const member function on a modifiable rvalue is explicit, so it's allowed.
	In C++0x, the answer changes dramatically, making move semantics possible.

- Congratulations!
	Now you have what I call "lvalue/rvalue vision", the ability to look at an expression and determine whether it's an lvalue or an rvalue.
	Combined with your "const vision", you can precisely reason that given
		void mutate(string& ref)
	and the definitions above,
		- mutate(one) is valid, while
		- mutate(two), mutate(three()), mutate(four()), and mutate("purr") are invalid
	and all of
		- observe(one), observe(two), observe(three()), observe(four()), and observe("purr") are valid.
	If you're a C++98/03 programmer, you already knew which of these calls were valid and which were invalid;
	your "gut feeling", if not your compiler, would have told you that
		mutate(three())
	was bogus. Your new lvalue/rvalue vision tells you precisely why (three() is an rvalue, and modifiable references can't be bound to rvalues).
	Is that useful?
		To language lawyers, yes, but not really to normal programmers.
		After all, you've gotten this far without knowing all of this stuff about lvalues and rvalues.
	But here's the catch:
		compared to C++98/03, C++0x has vastly more powerful lvalue/rvalue vision
		(in particular, the ability to look at an expression, determine whether it's a modifiable/const lvalue/rvalue, and do something about it).
	In order to use C++0x effectively, you need lvalue/rvalue vision too.


the copying problem
-------------------

- C++98/03 is overly fond of copying
	C++98/03 combines insanely powerful abstraction with insanely efficient execution, but it has a problem: it's overly fond of copying.
	pro:
		Things with value semantics behave like ints, so copying a thing doesn't modify the source, and the resulting copies are independent.
	con:
		Value semantics are great, except that they tend to lead to unnecessary copies of heavy objects like strings, vectors, and so forth.
		("Heavy" means "expensive to copy"; a million-element vector is heavy.)
		The Return Value Optimization (RVO) and Named Return Value Optimization (NRVO), where copy constructors are elided in certain situations,
		help to alleviate this problem, but they don't remove all unnecessary copies.

- Case Study
	The most unnecessary copies are those where the source is about to be destroyed.

	Would you photocopy a sheet of paper and then immediately throw away the original, assuming that the original and the photocopy are identical?
	That would be wasteful; you should keep the original and not bother with the photocopy.

	Here's what I call "the killer example", derived from one of the Standardization Committee's examples (in N1377).
	Suppose that you have a bunch of strings, like this:

		string s0("my mother told me that");
		string s1("cute");
		string s2("fluffy");
		string s3("kittens");
		string s4("are an essential part of a healthy diet");

	And that you concatenate them like this:

		string dest = s0 + " " + s1 + " " + s2 + " " + s3 + " " + s4;

	How efficient is this?
		(We're not worrying about this specific example, which executes in microseconds;
		 we're worrying about its generalization, which occurs throughout the entire language.)
		Each call to operator+() returns a temporary string.
		There are 8 calls to operator+() , so there are 8 temporary strings.
		Each one, upon its construction,
			- performs a dynamic memory allocation and
			- copies all of the characters that have been concatenated so far, and later, 
			- upon its destruction, performs a dynamic memory deallocation.
		(If you've heard of the Small String Optimization, which VC performs in order to
		 avoid dynamic memory allocations and deallocations for short strings, it's defeated
		 here by my carefully chosen and sufficiently long s0 , and even if it applied,
		 it couldn't avoid the copying. If you've heard of the Copy-On-Write "optimization",
		 forget about it - it doesn't apply here, and it's a pessimization under multithreading,
		 so Standard Library implementations don't do it anymore.)

		In fact, because every concatenation copies all of the characters that have been concatenated so far,
		this has quadratic complexity in the number of concatenations.

	Yuck! This is extraordinarily wasteful, which is especially embarrassing for C++.

	Why is this happening, and what can we do about it?
		The problem is that
			operator+()
		which takes two const string& or one const string& and one const char *
		(there are other overloads, which we aren't using here),
		can't tell whether it's being fed lvalues versus rvalues, so it always has to create and return a new temporary string.

	Why do lvalues versus rvalues matter?
		When evaluating s0 + " ",
			it's absolutely necessary to create a new temporary string.
			s0 is an lvalue, naming a persistent object, so we can't modify it. (Someone would notice!)
		But when evaluating (s0 + " ") + s1,
			we could simply append s1's contents onto our first temporary string,
			instead of creating a second temporary and throwing the first temporary away.
		This is the key insight behind move semantics: because
			s0 + " " is an rvalue
		an expression referring to a temporary object, no one else in the entire program can observe that temporary object.
		If we could detect that expression as being a
			modifiable rvalue,
		we could then proceed to modify the temporary object arbitrarily, without anyone else noticing.
		operator+() isn't "supposed to" modify its arguments, but if they're modifiable rvalues, who cares?
		In this manner, each call to operator+() can append characters onto a single temporary string.
		This completely eliminates the unnecessary dynamic memory management and unnecessary copying, leaving us with linear complexity.
		Yay!

	operator+() in C++0x
		Technically speaking, in C++0x, each call to operator+() still returns a separate temporary string.
		However, the second temporary string (from evaluating (s0 + " ") + s1 ) is constructed by
			- stealing the memory owned by the first temporary string (from evaluating s0 + " " ) and then
			- appending s1's contents onto that memory (which may trigger an ordinary geometric reallocation).
		"Stealing" consists of pointer twiddling:
			the second temporary
				- copies and then
				- nulls out
			the first temporary's internal pointer.
		When the first temporary is eventually destroyed ("at the semicolon"), its pointer is null, so its destructor does nothing.

	moving, moveable objects, move semantics
		In general, being able to detect modifiable rvalues allows you to engage in "resource pilfering".
		                                 ^^^^^^^^^^^^^^^^^^
		If the objects referred to by modifiable rvalues own any resources (such as memory),
		you can steal their resources instead of copying them, since they're going to evaporate anyways.
		Constructing from or assigning from modifiable rvalues by taking what they own is generically referred to as "moving",
		and moveable objects have "move semantics".

- use lvalue as a modifiable rvalue if it evaporate soon
	This (moving, moveable objects, move semantics) is extremely useful in many places, such as vector reallocation.
	When a vector needs more capacity (e.g. during push_back()) and undergoes reallocation,
	it needs to copy elements from its old memory block to its new memory block.
	These copy constructor calls can be expensive.
	(With a vector<string>, each string needs to be copied, involving dynamic memory allocation.)
	But wait! The elements in the old memory block are about to be destroyed.
	So we can move elements over, instead of copying them.
	In this case,
		- the elements in the old memory block occupy persistent storage, and
		- the expressions used to refer to them, such as old_ptr[index] , are lvalues.
		                                                                      ^^^^^^^
	During reallocation, we want to refer to the elements in the old memory block with modifiable rvalue expressions.
	                                                                                   ^^^^^^^^^^^^^^^^^
	Pretending that they're modifiable rvalues will allow us to move them, eliminating copy constructor calls.
	````````````````````````^^^^^^^^^^^^^^^^^^
	(Saying "I want to pretend that this lvalue is a modifiable rvalue" is equivalent to saying
		- "I know that this is an lvalue, referring to a persistent object, but
		- I don't care what happens to the lvalue after this.
		- I'm going to destroy it, or assign to it, or whatever.
		- So if you can steal resources from it, go ahead."
	)

C++0x's rvalue references
-------------------------

C++0x's rvalue references enable move semantics by giving us the ability to detect modifiable rvalues and steal from them.
Rvalue references also allow us to activate move semantics at will by treating lvalues as modifiable rvalues.
Now, let's see how rvalue references work!

rvalue references: initialization
"""""""""""""""""""""""""""""""""

- rvalue reference: Type&& and const Type&&
	C++0x introduces a new kind of reference, the
		rvalue reference
	with the syntax
		Type&&
	and
		const Type&&
	The current C++0x Working Draft, N2798 8.3.2/2, says:
		"A reference type that is declared using & is called an lvalue reference, and
		 a reference type that is declared using && is called an rvalue reference.
		 Lvalue references and rvalue references are distinct types.
		 Except where explicitly noted, they are semantically equivalent and commonly referred to as references."
	This means that your intuition for C++98/03 references (now known as lvalue references) translates over to rvalue references;
	all you have to learn are the differences between them.

- pronunciation
	Note: I've settled on pronouncing
		Type&   as  "Type ref"     and
		Type&&  as  "Type ref ref".
	They're fully known as
		"lvalue reference to Type"  and
		"rvalue reference to Type", respectively,
	just like how
		"const pointer to int"
	is written as
		int * const
	and can be pronounced as
		"int star const"

- What are the differences?
	Compared to lvalue references, rvalue references behave differently during initialization and overload resolution.
	They differ in
		- what they are willing to bind to (i.e. initialization) and
		- what prefers to bind to them (i.e. overload resolution).

- initialization
	Let's look at initialization first:

		- We've already seen how the modifiable lvalue reference,
			Type& ,
		  is willing to bind to
			modifiable lvalues,
		  but not to anything else (const lvalues, modifiable rvalues, const rvalues).

		- We've already seen how the const lvalue reference,
			const Type& ,
		  is willing to bind to everything.

		- The modifiable rvalue reference,
			Type&& ,
		  is willing to bind to
			modifiable lvalues
		  and
			modifiable rvalues,
		  but not to
			const lvalues
		  and
			const rvalues
		  (which would violate const correctness).

		- The const rvalue reference,
			const Type&& ,
		  is willing to bind to everything.

	These rules may sound arcane, but they're derived from two simple rules:
		- Obey
			const correctness
		  by
		  	preventing
				modifiable references
			from binding to
				const things.
		- Avoid
			accidentally modifying temporaries
		  by
		  	preventing
				modifiable lvalue references
			from binding to
				modifiable rvalues.

- Case Study
	If you like reading compiler errors instead of reading English, here's a demonstration:

		C:\Temp>type initialization.cpp

			#include <string>
			using namespace std;

			string modifiable_rvalue() {
			    return "cute";
			}

			const string const_rvalue() {
			    return "fluffy";
			}

			int main() {
			    string modifiable_lvalue("kittens");
			    const string const_lvalue("hungry hungry zombies");

			    string& a = modifiable_lvalue;          // Line 16
			    string& b = const_lvalue;               // Line 17 - ERROR
			    string& c = modifiable_rvalue();        // Line 18 - ERROR
			    string& d = const_rvalue();             // Line 19 - ERROR

			    const string& e = modifiable_lvalue;    // Line 21
			    const string& f = const_lvalue;         // Line 22
			    const string& g = modifiable_rvalue();  // Line 23
			    const string& h = const_rvalue();       // Line 24

			    string&& i = modifiable_lvalue;         // Line 26
			    string&& j = const_lvalue;              // Line 27 - ERROR
			    string&& k = modifiable_rvalue();       // Line 28
			    string&& l = const_rvalue();            // Line 29 - ERROR

			    const string&& m = modifiable_lvalue;   // Line 31
			    const string&& n = const_lvalue;        // Line 32
			    const string&& o = modifiable_rvalue(); // Line 33
			    const string&& p = const_rvalue();      // Line 34
			}

		C:\Temp>cl /EHsc /nologo /W4 /WX initialization.cpp
			initialization.cpp
			initialization.cpp(17) : error C2440: 'initializing' : cannot convert from 'const std::string' to 'std::string &'
				Conversion loses qualifiers
			initialization.cpp(18) : warning C4239: nonstandard extension used : 'initializing' : conversion from 'std::string' to 'std::string &'
				A non-const reference may only be bound to an lvalue
			initialization.cpp(19) : error C2440: 'initializing' : cannot convert from 'const std::string' to 'std::string &'
				Conversion loses qualifiers
			initialization.cpp(27) : error C2440: 'initializing' : cannot convert from 'const std::string' to 'std::string &&'
				Conversion loses qualifiers
			initialization.cpp(29) : error C2440: 'initializing' : cannot convert from 'const std::string' to 'std::string &&'
				Conversion loses qualifiers

	It's okay for
		modifiable rvalue references
	to bind to
		modifiable rvalues;
	the whole point is that they can be used to modify temporaries.

rvalue references: overload resolution
""""""""""""""""""""""""""""""""""""""

Although lvalue references and rvalue references behave similarly during initialization (only lines 18 and 28 above differ),
they increasingly diverge during overload resolution.

You're already familiar with how functions can be overloaded on modifiable and const lvalue reference parameters.
In C++0x, functions can also be overloaded on modifiable and const rvalue reference parameters.

- Case Study
	Given all four overloads of a unary function, you shouldn't be surprised to discover that each expression prefers to bind to its corresponding reference:

		C:\Temp>type four_overloads.cpp
		#include <iostream>
		#include <ostream>
		#include <string>
		using namespace std;

		void meow(string& s) {
		    cout << "meow(string&): " << s << endl;
		}

		void meow(const string& s) {
		    cout << "meow(const string&): " << s << endl;
		}

		void meow(string&& s) {
		    cout << "meow(string&&): " << s << endl;
		}

		void meow(const string&& s) {
		    cout << "meow(const string&&): " << s << endl;
		}

		string strange() {
		    return "strange()";
		}

		const string charm() {
		    return "charm()";
		}

		int main() {
		    string up("up");
		    const string down("down");

		    meow(up);
		    meow(down);
		    meow(strange());
		    meow(charm());
		}

		C:\Temp>cl /EHsc /nologo /W4 four_overloads.cpp
		four_overloads.cpp

		C:\Temp>four_overloads
		meow(string&): up
		meow(const string&): down
		meow(string&&): strange()
		meow(const string&&): charm()

	In practice, overloading on Type& , const Type& , Type&& , and const Type&& is not very useful.
	A far more interesting overload set is const Type& and Type&& :

		C:\Temp>type two_overloads.cpp

		#include <iostream>
		#include <ostream>
		#include <string>
		using namespace std;

		void purr(const string& s) {
		    cout << "purr(const string&): " << s << endl;
		}

		void purr(string&& s) {
		    cout << "purr(string&&): " << s << endl;
		}

		string strange() {
		    return "strange()";
		}

		const string charm() {
		    return "charm()";
		}

		int main() {
		    string up("up");
		    const string down("down");

		    purr(up);
		    purr(down);
		    purr(strange());
		    purr(charm());
		}

		C:\Temp>cl /EHsc /nologo /W4 two_overloads.cpp
		two_overloads.cpp

		C:\Temp>two_overloads
		purr(const string&): up
		purr(const string&): down
		purr(string&&): strange()
		purr(const string&): charm()
 
How does this work?  Here are the rules:
 
	- The initialization rules have veto power.
	  (By "veto", I mean that candidate functions which would involve forbidden bindings of expressions to references are
	   immediately deemed to be "non-viable" and are removed from further consideration.)
	- lvalues strongly prefer binding to lvalue references, and
	  rvalues strongly prefer binding to rvalue references.
	- Modifiable expressions weakly prefer binding to modifiable references.

Let's walk through the process of applying the rules.

	- For purr(up) ,
	  the initialization rules veto neither purr(const string&) nor purr(string&&) .
		- up is an  lvalue,     so it strongly prefers binding to the  lvalue     reference  purr(const string&) .
		- up is     modifiable, so it weakly   prefers binding to the  modifiable reference  purr(string&&) .
	  The strongly preferred purr(const string&) wins.

	- For purr(down) ,
	  the initialization rules veto purr(string&&) due to const correctness, so purr(const string&) wins by default.

	- For purr(strange()) ,
	  the initialization rules veto neither purr(const string&) nor purr(string&&) .
		- strange() is an rvalue,     so it strongly prefers binding to the  rvalue     reference  purr(string&&) .
		- strange() is    modifiable, so it weakly   prefers binding to the  modifiable reference  purr(string&&) .
	  The doubly preferred purr(string&&) wins.

	- For purr(charm()) ,
	  the initialization rules veto purr(string&&) due to const correctness, so purr(const string&) wins by default.

The important thing to notice is that
	when you overload on const Type& and Type&& ,
		modifiable rvalues
	bind to
		Type&& ,
	while everything else binds to
		const Type& .
	Therefore, this is the overload set for move semantics.

Important note:
	functions returning by value should return Type (like strange()) instead of const Type (like charm()).
	The latter buys you virtually nothing (forbidding non-const member function calls) and prevents the move semantics optimization.

move semantics: the pattern
"""""""""""""""""""""""""""

- Case Study
	Here's a simple class, remote_integer, that stores a pointer to a dynamically allocated int. (This is "remote ownership".)
	Its default constructor, unary constructor, copy constructor, copy assignment operator, and destructor should all look very familiar to you.
	I've additionally given it a move constructor and move assignment operator.
	They're guarded by #ifdef MOVABLE so that I can demonstrate what happens with and without them; real code won't do this.

		C:\Temp>type remote.cpp
		#include <stddef.h>
		#include <iostream>
		#include <ostream>
		using namespace std;

		class remote_integer {
		public:
		    remote_integer() {
			cout << "Default constructor." << endl;

			m_p = NULL;
		    }

		    explicit remote_integer(const int n) {
			cout << "Unary constructor." << endl;

			m_p = new int(n);
		    }

		    remote_integer(const remote_integer& other) {
			cout << "Copy constructor." << endl;

			if (other.m_p) {
			    m_p = new int(*other.m_p);
			} else {
			    m_p = NULL;
			}
		    }

		#ifdef MOVABLE
		    remote_integer(remote_integer&& other) {
			cout << "MOVE CONSTRUCTOR." << endl;

			m_p = other.m_p;
			other.m_p = NULL;
		    }
		#endif // #ifdef MOVABLE

		    remote_integer& operator=(const remote_integer& other) {
			cout << "Copy assignment operator." << endl;

			if (this != &other) {
			    delete m_p;

			    if (other.m_p) {
				m_p = new int(*other.m_p);
			    } else {
				m_p = NULL;
			    }
			}

			return *this;
		    }

		#ifdef MOVABLE
		    remote_integer& operator=(remote_integer&& other) {
			cout << "MOVE ASSIGNMENT OPERATOR." << endl;

			if (this != &other) {
			    delete m_p;

			    m_p = other.m_p;
			    other.m_p = NULL;
			}

			return *this;
		    }
		#endif // #ifdef MOVABLE

		    ~remote_integer() {
			cout << "Destructor." << endl;

			delete m_p;
		    }

		    int get() const {
			return m_p ? *m_p : 0;
		    }

		private:
		    int * m_p;
		};

		remote_integer square(const remote_integer& r) {
		    const int i = r.get();

		    return remote_integer(i * i);
		}

		int main() {
		    remote_integer a(8);

		    cout << a.get() << endl;

		    remote_integer b(10);

		    cout << b.get() << endl;

		    b = square(a);

		    cout << b.get() << endl;
		}

		C:\Temp>cl /EHsc /nologo /W4 remote.cpp
		remote.cpp

		C:\Temp>remote
		Unary constructor.
		8
		Unary constructor.
		10
		Unary constructor.
		Copy assignment operator.
		Destructor.
		64
		Destructor.
		Destructor.

		C:\Temp>cl /EHsc /nologo /W4 /DMOVABLE remote.cpp
		remote.cpp

		C:\Temp>remote
		Unary constructor.
		8
		Unary constructor.
		10
		Unary constructor.
		MOVE ASSIGNMENT OPERATOR.
		Destructor.
		64
		Destructor.
		Destructor.
 
There are several things to notice here.

	- The copy and move constructors are overloaded, and the copy and move assignment operators are overloaded.
	  We've already seen what happens to functions overloaded on const Type& and Type&& .
	  This is what allows
	  	b = square(a);
	  to automatically select the move assignment operator when it's available.

	- Instead of dynamically allocating memory, the move constructor and move assignment operator simply steal it from other .
	  When stealing, we copy other's pointer and then null it out.  When other is destroyed, its destructor will do nothing.

	- Both the copy and move assignment operators need self-assignment checks.
	  It's well-known why copy assignment operators need self-assignment checks.
	  This is because plain old data types like ints can be assigned to themselves harmlessly (e.g. with x = x;),
	  so user-defined data types should also be harmlessly self-assignable.
	  Self-assignment virtually never happens in handwritten code, but it can easily happen inside algorithms like std::sort() .
	  In C++0x, algorithms like std::sort() can move elements around instead of copying them.
	  The same potential for self-assignment exists here.

At this point, you may be wondering how this interacts with automatically generated ("implicitly declared" in Standardese) constructors and assignment operators.

	- Move constructors and move assignment operators are never implicitly declared.
	- The implicit declaration of a default constructor is inhibited by any user-declared constructors, including copy constructors and move constructors.
	- The implicit declaration of a copy constructor is inhibited by a user-declared copy constructor, but not a user-declared move constructor.
	- The implicit declaration of a copy assignment operator is inhibited by a user-declared copy assignment operator, but not a user-declared move assignment operator.

Basically, the automatic generation rules don't interact with move semantics, except that declaring a move constructor,
like declaring any constructor, inhibits the implicitly declared default constructor.

move semantics: moving from lvalues
"""""""""""""""""""""""""""""""""""

- write the move constructors in terms of the move assignment operators

  Now, what if you like to write your copy constructors in terms of your copy assignment operators?

  - WRONG way to write the move constructors in terms of the move assignment operators

	You might attempt to write your move constructors in terms of your move assignment operators.
	This is possible, but you have to be careful.  Here's the wrong way to do it:

		C:\Temp>type unified_wrong.cpp
		#include <stddef.h>
		#include <iostream>
		#include <ostream>
		using namespace std;

		class remote_integer {
		public:
		    remote_integer() {
			cout << "Default constructor." << endl;

			m_p = NULL;
		    }

		    explicit remote_integer(const int n) {
			cout << "Unary constructor." << endl;

			m_p = new int(n);
		    }

		    remote_integer(const remote_integer& other) {
			cout << "Copy constructor." << endl;

			m_p = NULL;
			*this = other;
		    }

		#ifdef MOVABLE
		    remote_integer(remote_integer&& other) {
			cout << "MOVE CONSTRUCTOR." << endl;

			m_p = NULL;
			*this = other; // WRONG
		    }
		#endif // #ifdef MOVABLE

		    remote_integer& operator=(const remote_integer& other) {
			cout << "Copy assignment operator." << endl;

			if (this != &other) {
			    delete m_p;

			    if (other.m_p) {
				m_p = new int(*other.m_p);
			    } else {
				m_p = NULL;
			    }
			}

			return *this;
		    }

		#ifdef MOVABLE
		    remote_integer& operator=(remote_integer&& other) {
			cout << "MOVE ASSIGNMENT OPERATOR." << endl;

			if (this != &other) {
			    delete m_p;

			    m_p = other.m_p;
			    other.m_p = NULL;
			}

			return *this;
		    }
		#endif // #ifdef MOVABLE

		    ~remote_integer() {
			cout << "Destructor." << endl;

			delete m_p;
		    }

		    int get() const {
			return m_p ? *m_p : 0;
		    }

		private:
		    int * m_p;
		};

		remote_integer frumple(const int n) {
		    if (n == 1729) {
			return remote_integer(1729);
		    }

		    remote_integer ret(n * n);

		    return ret;
		}

		int main() {
		    remote_integer x = frumple(5);

		    cout << x.get() << endl;

		    remote_integer y = frumple(1729);

		    cout << y.get() << endl;
		}

		C:\Temp>cl /EHsc /nologo /W4 /O2 unified_wrong.cpp
		unified_wrong.cpp

		C:\Temp>unified_wrong
		Unary constructor.
		Copy constructor.
		Copy assignment operator.
		Destructor.
		25
		Unary constructor.
		1729
		Destructor.
		Destructor.

		C:\Temp>cl /EHsc /nologo /W4 /O2 /DMOVABLE unified_wrong.cpp
		unified_wrong.cpp

		C:\Temp>unified_wrong
		Unary constructor.
		MOVE CONSTRUCTOR.
		Copy assignment operator.
		Destructor.
		25
		Unary constructor.
		1729
		Destructor.
		Destructor.

	(The compiler is performing the RVO here, but not the NRVO.
	 As I mentioned earlier, some copy constructor calls are elided by the RVO and NRVO, but the compiler isn't always able to apply them.
	 Move constructors optimize the remaining cases.)

	The line marked WRONG inside the move constructor is calling the copy assignment operator!
	This compiles and runs, but it defeats the purpose of the move constructor.

	What happened? Remember from C++98/03 that
		- named lvalue references are lvalues (if you say int& r = *p; then r is an lvalue) and
		- unnamed lvalue references are also lvalues (given vector<int> v(10, 1729), calling v[0] returns int& ,
		  an unnamed lvalue reference whose address you can take).
	Rvalue references behave differently:
		- Named rvalue references are lvalues.
		- Unnamed rvalue references are rvalues.
	A named rvalue reference is an lvalue because
		it can be repeatedly mentioned, with multiple operations performed on it.
	If instead it were an rvalue, then
		the first operation performed could steal from it, affecting subsequent operations.
	Stealing is supposed to be unobservable, so this is forbidden.
	On the other hand,
		unnamed rvalue references can't be repeatedly mentioned, so they can preserve their rvalueness.
		``````````````````````````````````````````````````````````````````````````````````````````````
  - write the move constructors in terms of the move assignment operators
	If you're really intent on implementing your move constructors in terms of your move assignment operators,
	you'll need the ability to move from lvalues by treating them as rvalues.
	This is powered by
		std::move()
	from
		C++0x <utility>,
	which will be in VC10 (in fact, it's already in my development build),
	but because it's not in the VC10 CTP, I'll show you how to write it from scratch:

		C:\Temp>type unified_right.cpp
		#include <stddef.h>
		#include <iostream>
		#include <ostream>
		using namespace std;

		template <typename T> struct RemoveReference {
		     typedef T type;
		};

		template <typename T> struct RemoveReference<T&> {
		     typedef T type;
		};

		template <typename T> struct RemoveReference<T&&> {
		     typedef T type;
		};

		template <typename T> typename RemoveReference<T>::type&& Move(T&& t) {
		    return t;
		}

		class remote_integer {
		public:
		    remote_integer() {
			cout << "Default constructor." << endl;

			m_p = NULL;
		    }

		    explicit remote_integer(const int n) {
			cout << "Unary constructor." << endl;

			m_p = new int(n);
		    }

		    remote_integer(const remote_integer& other) {
			cout << "Copy constructor." << endl;

			m_p = NULL;
			*this = other;
		    }

		#ifdef MOVABLE
		    remote_integer(remote_integer&& other) {
			cout << "MOVE CONSTRUCTOR." << endl;

			m_p = NULL;
			*this = Move(other); // RIGHT
		    }
		#endif // #ifdef MOVABLE

		    remote_integer& operator=(const remote_integer& other) {
			cout << "Copy assignment operator." << endl;

			if (this != &other) {
			    delete m_p;

			    if (other.m_p) {
				m_p = new int(*other.m_p);
			    } else {
				m_p = NULL;
			    }
			}

			return *this;
		    }

		#ifdef MOVABLE
		    remote_integer& operator=(remote_integer&& other) {
			cout << "MOVE ASSIGNMENT OPERATOR." << endl;

			if (this != &other) {
			    delete m_p;

			    m_p = other.m_p;
			    other.m_p = NULL;
			}

			return *this;
		    }
		#endif // #ifdef MOVABLE

		    ~remote_integer() {
			cout << "Destructor." << endl;

			delete m_p;
		    }

		    int get() const {
			return m_p ? *m_p : 0;
		    }

		private:
		    int * m_p;
		};

		remote_integer frumple(const int n) {
		    if (n == 1729) {
			return remote_integer(1729);
		    }

		    remote_integer ret(n * n);

		    return ret;
		}

		int main() {
		    remote_integer x = frumple(5);

		    cout << x.get() << endl;

		    remote_integer y = frumple(1729);

		    cout << y.get() << endl;
		}

		C:\Temp>cl /EHsc /nologo /W4 /O2 /DMOVABLE unified_right.cpp
		unified_right.cpp

		C:\Temp>unified_right
		Unary constructor.
		MOVE CONSTRUCTOR.
		MOVE ASSIGNMENT OPERATOR.
		Destructor.
		25
		Unary constructor.
		1729
		Destructor.
		Destructor.

	(I'll refer to std::move() and my Move() interchangeably, since they're implemented identically.)

	How does std::move() work?
		For the moment, I'm going to say that "magic is involved".
		(There's a full explanation below; it's not complicated,
		 but it involves template argument deduction and reference collapsing,
		 which we'll encounter while looking at perfect forwarding.)
		I can skip over the magic with concrete examples.

		Given an lvalue of type string, like up from the overload resolution examples above, std::move(up) calls string&& std::move(string&) .
		This returns an unnamed rvalue reference, which is an rvalue.
		Given an rvalue of type string, like strange() from above, std::move(strange()) calls string&& std::move(string&&) .
		Again, this returns an unnamed rvalue reference, which is an rvalue.

	std::move() is useful in other places than implementing move constructors in terms of move assignment operators.
	Whenever you reach a point where you can say "I have an lvalue here, and its value is going to cease to matter"
	(e.g. because it's going to be destroyed or assigned to), you can write std::move(your lvalue expression) in order to activate move semantics.

move semantics: movable members
"""""""""""""""""""""""""""""""

C++0x's Standard classes (e.g. vector, string, regex) have move constructors and move assignment operators,
and we've seen how to implement them in our own classes that manually manage resources (e.g. remote_integer).
But what about classes containing movable data members (e.g. vector, string, regex, remote_integer)?
The compiler won't automatically generate move constructors and move assignment operators for us.
So, we'll need to write them ourselves.

Fortunately, with std::move() , this is extremely easy:

		C:\Temp>type point.cpp
		#include <stddef.h>
		#include <iostream>
		#include <ostream>
		using namespace std;

		template <typename T> struct RemoveReference {
		     typedef T type;
		};

		template <typename T> struct RemoveReference<T&> {
		     typedef T type;
		};

		template <typename T> struct RemoveReference<T&&> {
		     typedef T type;
		};

		template <typename T> typename RemoveReference<T>::type&& Move(T&& t) {
		    return t;
		}

		class remote_integer {
		public:
		    remote_integer() {
			cout << "Default constructor." << endl;

			m_p = NULL;
		    }

		    explicit remote_integer(const int n) {
			cout << "Unary constructor." << endl;

			m_p = new int(n);
		    }

		    remote_integer(const remote_integer& other) {
			cout << "Copy constructor." << endl;

			if (other.m_p) {
			    m_p = new int(*other.m_p);
			} else {
			    m_p = NULL;
			}
		    }

		    remote_integer(remote_integer&& other) {
			cout << "MOVE CONSTRUCTOR." << endl;

			m_p = other.m_p;
			other.m_p = NULL;
		    }

		    remote_integer& operator=(const remote_integer& other) {
			cout << "Copy assignment operator." << endl;

			if (this != &other) {
			    delete m_p;

			    if (other.m_p) {
				m_p = new int(*other.m_p);
			    } else {
				m_p = NULL;
			    }
			}

			return *this;
		    }

		    remote_integer& operator=(remote_integer&& other) {
			cout << "MOVE ASSIGNMENT OPERATOR." << endl;

			if (this != &other) {
			    delete m_p;

			    m_p = other.m_p;
			    other.m_p = NULL;
			}

			return *this;
		    }

		    ~remote_integer() {
			cout << "Destructor." << endl;

			delete m_p;
		    }

		    int get() const {
			return m_p ? *m_p : 0;
		    }

		private:
		    int * m_p;
		};

		class remote_point {
		public:
		    remote_point(const int x_arg, const int y_arg)
			: m_x(x_arg), m_y(y_arg) { }

		    remote_point(remote_point&& other)
			: m_x(Move(other.m_x)),
			  m_y(Move(other.m_y)) { }

		    remote_point& operator=(remote_point&& other) {
			m_x = Move(other.m_x);
			m_y = Move(other.m_y);
			return *this;
		    }

		    int x() const { return m_x.get(); }
		    int y() const { return m_y.get(); }

		private:
		    remote_integer m_x;
		    remote_integer m_y;
		};

		remote_point five_by_five() {
		    return remote_point(5, 5);
		}

		remote_point taxicab(const int n) {
		    if (n == 0) {
			return remote_point(1, 1728);
		    }

		    remote_point ret(729, 1000);

		    return ret;
		}

		int main() {
		    remote_point p = taxicab(43112609);

		    cout << "(" << p.x() << ", " << p.y() << ")" << endl;

		    p = five_by_five();

		    cout << "(" << p.x() << ", " << p.y() << ")" << endl;
		}

		C:\Temp>cl /EHsc /nologo /W4 /O2 point.cpp
		point.cpp

		C:\Temp>point
		Unary constructor.
		Unary constructor.
		MOVE CONSTRUCTOR.
		MOVE CONSTRUCTOR.
		Destructor.
		Destructor.
		(729, 1000)
		Unary constructor.
		Unary constructor.
		MOVE ASSIGNMENT OPERATOR.
		MOVE ASSIGNMENT OPERATOR.
		Destructor.
		Destructor.
		(5, 5)
		Destructor.
		Destructor.

As you can see, memberwise moves are trivial to write.
Note that remote_point's move assignment operator doesn't need to check for self-assignment because remote_integer already does.
Also note that remote_point's implicitly declared copy constructor, copy assignment operator, and destructor do the right things.

By now, you should be exhaustively familiar with move semantics. (But hopefully not exhausted!)
As a test of your newly acquired incredible powers, solving the original example of the copying problem with operator+()
(applied to remote_integer instead of string) is an exercise left to the reader. 

A final reminder: whenever possible, you should implement move constructors and move assignment operators for your copyable classes,
because the compiler won't do it for you.
Not only will ordinary use of those classes automatically pick up move semantics,
but STL containers and algorithms will also take advantage of move semantics,
replacing expensive copies with cheap moves.

the forwarding problem
----------------------

C++98/03's rules for lvalues, rvalues, references, and templates seemed perfectly fine until programmers tried to write highly generic code.

Suppose you're writing a completely generic function
	outer()
whose purpose in life is to take an arbitrary number of arbitrary arguments and pass them ("forward" them) to an arbitrary function
	inner() .

There are many good examples of this.
The factory function
	make_shared<T>(args)
forwards args to T's constructor and returns
	shared_ptr<T> .
(This can store the T object and its reference count control block in a single dynamic memory allocation,
 achieving efficiency equal to that of intrusive reference counting.)

Wrappers like
	function<Ret (Args)>
forward arguments to their stored functors, and so forth.
In this post, our only interest is outer() forwarding arguments to inner() .
Determining outer()'s return type is a separate matter
(some cases are easy, e.g.
	make_shared<T>(args)
 always returns
	shared_ptr<T>,
 but the C++0x feature decltype is required to solve the fully general case).


*/

/*
The zero-argument case solves itself, so what about the one-argument case?  Let's try to write outer() :
*/
template <typename T> void outer(T& t) {
    inner(t);
}
/*
The problem with this outer() is that it can't be called with modifiable rvalues.
If inner() takes const int& , then inner(5) will compile.
But outer(5) won't compile; T will be deduced to be int, and int& won't bind to 5 .

Okay, so let's try this:
*/
template <typename T> void outer(const T& t) {
    inner(t);
}
/*
If inner() takes int& , then this will violate const correctness, so it won't compile.

Now, you can overload outer() on both T& and const T& , which actually works.  Then you can call outer() exactly as if it were inner() .

Unfortunately, this doesn't scale to the multi-argument case.
That would involve overloading on T1& and const T1& , T2& and const T2& , etc. for every argument, producing an exponential number of overloads.
(VC9 SP1's tr1::bind() is desperate enough to do this for the first 5 arguments, involving 63 overloads.
 Otherwise, it would be hard to explain to users why they couldn't call bound functors with rvalues like 1729 without going through this whole explanation.
 Stamping out these overloads requires disgusting preprocessor machinery that you really don't want to know about.)

The forwarding problem is severe and fundamentally unsolvable in C++98/03 (without resorting to that disgusting
preprocessor machinery that significantly slows down compilation and makes code virtually unreadable).
However, rvalue references solve the forwarding problem in an elegant manner.

(I explained the initialization and overload resolution rules before demonstrating the move semantics pattern,
but now I'm going to demonstrate the perfect forwarding pattern before explaining the template argument deduction and reference collapsing rules.
It'll make more sense this way.)

perfect forwarding: the pattern
-------------------------------

Perfect forwarding allows you to write a single function template that takes N arbitrary arguments and forwards them, transparently, to an arbitrary function.
Their modifiable/const lvalue/rvalue nature will be preserved, permitting outer() to be used exactly like inner() , and cooperating with move semantics as a bonus.
(C++0x variadic templates solve the "arbitrary number" part; we'll be considering any given N here.)
This is easy, although it looks like magic at first:
/*
/*
		C:\Temp>type perfect.cpp
*/
//#include <iostream>
//#include <ostream>
//using namespace std;

template <typename T>
struct Identity {
	typedef T type;
};

template <typename T>
T&& Forward(typename Identity<T>::type&& t) {
	return t;
}

void inner(int&, int&) {
	cout << "inner(int&, int&)" << endl;
}

void inner(int&, const int&) {
	cout << "inner(int&, const int&)" << endl;
}

void inner(const int&, int&) {
	cout << "inner(const int&, int&)" << endl;
}

void inner(const int&, const int&) {
	cout << "inner(const int&, const int&)" << endl;
}

template <typename T1, typename T2>
void outer(T1&& t1, T2&& t2) {
	inner(Forward<T1>(t1), Forward<T2>(t2));
}

int main_30() {
	int a = 1;
	const int b = 2;

	cout << "Directly calling inner()." << endl;

	inner(a, a);
	inner(b, b);
	inner(3, 3);

	inner(a, b);
	inner(b, a);

	inner(a, 3);
	inner(3, a);

	inner(b, 3);
	inner(3, b);

	cout << endl << "Calling outer()." << endl;

	outer(a, a);
	outer(b, b);
	outer(3, 3);

	outer(a, b);
	outer(b, a);

	outer(a, 3);
	outer(3, a);

	outer(b, 3);
	outer(3, b);
}
/*
C:\Temp>cl /EHsc /nologo /W4 perfect.cpp
perfect.cpp

C:\Temp>perfect
Directly calling inner().
inner(int&, int&)
inner(const int&, const int&)
inner(const int&, const int&)
inner(int&, const int&)
inner(const int&, int&)
inner(int&, const int&)
inner(const int&, int&)
inner(const int&, const int&)
inner(const int&, const int&)

Calling outer().
inner(int&, int&)
inner(const int&, const int&)
inner(const int&, const int&)
inner(int&, const int&)
inner(const int&, int&)
inner(int&, const int&)
inner(const int&, int&)
inner(const int&, const int&)
inner(const int&, const int&)
*/
/*
Two lines!  Perfect forwarding takes two lines!  That's neat.

This demonstrates that outer() forwards t1 and t2 to inner() transparently; inner() observes lvalueness/rvalueness and constness as if it had been directly called.

Like std::move(), std::identity and std::forward() are defined by C++0x <utility> (and will be in VC10, but aren't in the CTP); I'm demonstrating how they're implemented.
(Again, I'll refer to std::identity and my Identity, and std::forward() and my Forward(), interchangeably, since they're implemented identically.)

Now, let's figure out how the magic works.  It's powered by template argument deduction and reference collapsing.

rvalue references: template argument deduction and reference collapsing

Rvalue references and templates interact in a special way.  This demonstrates what happens:
*/
/*
		C:\Temp>type collapse.cpp
*/
#include <iostream>
#include <ostream>
#include <string>
using namespace std;
template <typename T> struct Name;

template <> struct Name<string> {
	static const char * get() {
		return "string";
	}
};

template <> struct Name<const string> {
	static const char * get() {
		return "const string";
	}
};

template <> struct Name<string&> {
	static const char * get() {
		return "string&";
	}
};

template <> struct Name<const string&> {
	static const char * get() {
		return "const string&";
	}
};

template <> struct Name<string&&> {
	static const char * get() {
		return "string&&";
	}
};

template <> struct Name<const string&&> {
	static const char * get() {
		return "const string&&";
	}
};

template <typename T> void quark(T&& t) {
	cout << "t: " << t << endl;
	cout << "T: " << Name<T>::get() << endl;
	cout << "T&&: " << Name<T&&>::get() << endl;
	cout << endl;
}

string strange() {
	return "strange()";
}

const string charm() {
	return "charm()";
}

int main() {
	string up("up");
	const string down("down");

	quark(up);
	quark(down);
	quark(strange());
	quark(charm());
}

/* 
C:\Temp>cl /EHsc /nologo /W4 collapse.cpp
collapse.cpp

C:\Temp>collapse
t: up
T: string&
T&&: string&

t: down
T: const string&
T&&: const string&

t: strange()
T: string
T&&: string&&

t: charm()
T: const string
T&&: const string&&
*/
/*
The explicit specializations of Name allow us to print out types.

When we call quark(up), template argument deduction is performed.
quark() is a function template with a template parameter T, but we haven't provided an explicit template argument (which would look like quark<X>(up)).
Instead, a template argument can be deduced by comparing the function parameter type T&& with the function argument type (an lvalue of type string).

C++0x transforms both the function parameter type and the function argument type before matching them together.

First, it transforms the function argument type.
A special rule is activated (N2798 14.8.2.1 [temp.deduct.call]/3):
	when the function parameter type is of the form T&& where T is a template parameter,
	and the function argument is an lvalue of type A,
	the type A& is used for template argument deduction.
	(This special rule doesn't apply to function parameter types of the form T& or const T& ,
	 which behave as they did in C++98/03, nor does it apply to const T&& .)
In the case of quark(up), this means that we transform string into string& .
 
Then, it transforms the function parameter type.
Both C++98/03 and C++0x discard references (C++0x discards both lvalue references and rvalue references).
In all four cases, this means that we transform T&& into T .
 
Therefore, we deduce T to be the transformed function argument type.
That's why quark(up) prints "T: string&" and quark(down) prints "T: const string&"; up and down are lvalues, so they activate the special rule.
strange() and charm() are rvalues, so they use the ordinary rules, which is why quark(strange()) prints "T: string" and quark(charm()) prints "T: const string".
 
Substitution is performed after template argument deduction.
Each occurrence of the template parameter T is replaced by the deduced template argument.
In quark(strange()), T is string, so T&& is string&& .
Similarly, in quark(charm()), T is const string, so T&& is const string&& .
However, quark(up) and quark(down) activate another special rule.
 
In quark(up) , T is string& .
Substituting that into T&& produces string& && .
References to references are collapsed in C++0x, and the reference collapsing rule is that "lvalue references are infectious".
X& & , X& && , and X&& & collapse to X& .
Only X&& && collapses to X&& .
So, string& && collapses to string& .
In templates, things that look like rvalue references aren't necessarily so.
quark(up) instantiates quark<string&>().
Within this instantiation, T&& is string& .
We've observed this with Name<T&&>::get().
Similarly, when quark(down) instantiates quark<const string&>(), T&& is const string& .
In C++98/03, you're probably used to constness hiding inside template parameters
(a function template taking T& can be called with a const Foo object; what looks like T& will be const Foo&).
In C++0x, lvalueness can hide inside template parameters.
 
Okay, so what do these two special rules buy us?
Within quark(), the type T&& has the same lvalueness/rvalueness and constness as quark()'s function argument.
This is how rvalue references preserve lvalueness/rvalueness and constness for perfect forwarding.
 
perfect forwarding: how std::forward() and std::identity work
-------------------------------------------------------------
 
Let's look at outer() again:
*/
template <typename T1, typename T2> void outer(T1&& t1, T2&& t2) {
    inner(Forward<T1>(t1), Forward<T2>(t2));
}
/*
Now we understand why outer() takes T1&& and T2&& .
These types preserve information about outer()'s arguments.
But why does it call Forward<T1>() and Forward<T2>() ?
Recall that both named lvalue references and named rvalue references are lvalues.
If outer() called inner(t1, t2), then inner() would always observe t1 and t2 as being lvalues, breaking perfect forwarding.
 
Fortunately, unnamed lvalue references are lvalues, and unnamed rvalue references are rvalues.
So, in order to forward t1 and t2 to inner(), we need to pass them through helper functions that preserve their types but remove their names.
This is what std::forward() does:
*/
template <typename T> struct Identity {
    typedef T type;
};
 
template <typename T> T&& Forward(typename Identity<T>::type&& t) {
    return t;
}
/* 
When we call Forward<T1>(t1), Identity doesn't modify T1 (we'll soon see what it's doing).
So Forward<T1>() takes T1&& and returns T1&& .
This leaves t1's type unchanged (whatever it is; we've seen that it can be string& , const string& , string&& , or const string&&) but removes its name.
inner() will observe Forward<T1>(t1) as having the same type, lvalueness/rvalueness, and constness as whatever was passed as outer()'s first argument.
That's how perfect forwarding works!
 
You might wonder what would happen if you accidentally wrote Forward<T1&&>(t1) .
(This mistake is slightly tempting, since outer() takes T1&& t1 .)
Fortunately, nothing bad would happen.
Forward<T1&&>() would take and return T1&& && .
This collapses to T1&& .
Therefore, Forward<T1>(t1) and Forward<T1&&>(t1) are identical, but the former is shorter, so it should be preferred.
 
What is Identity doing?  Why wouldn't this work:
*/
template <typename T> T&& Forward(T&& t) { // BROKEN
    return t;
}
/*
If Forward() were written like that, it could be called without explicit template arguments.
Template argument deduction would kick in, and we've seen what happens to T&& - it becomes an lvalue reference when its function argument is an lvalue.
And the whole problem that we're trying to solve with Forward() is that
	within outer(), the named t1 and t2 are lvalues even when their types T1&& and T2&& are rvalue references.
With the BROKEN implementation, Forward<T1>(t1) would still work, but Forward(t1) would compile (so tempting!) and do the wrong thing, acting just like plain t1 .
That would be a continual source of pain, so Identity is used to disable template argument deduction.
Experienced template programmers should be familiar with this, as it works identically in C++98/03 and C++0x:
	the double colon in typename Identity<T>::type is a sheet of lead, and template argument deduction can't see through to the left of it.
(Explaining that is another story.)
 
 
move semantics: how std::move() works
-------------------------------------
 
Now that we've learned the special rules for template argument deduction and reference collapsing, let's look at std::move() again:
*/
template <typename T> struct RemoveReference {
     typedef T type;
};
 
template <typename T> struct RemoveReference<T&> {
     typedef T type;
};
 
template <typename T> struct RemoveReference<T&&> {
     typedef T type;
};
 
template <typename T> typename RemoveReference<T>::type&& Move(T&& t) {
    return t;
}
/*
The RemoveReference machinery exactly replicates std::remove_reference from C++0x <type_traits>.
For example, RemoveReference<string>::type , RemoveReference<string&>::type , and RemoveReference<string&&>::type are all string .
 
Similarly, the Move() machinery exactly replicates std::move() from C++0x <utility>.
 
	- When called with an lvalue of type string, T is deduced to be string& , so
	  Move() takes string& (after collapsing) and returns string&& (after RemoveReference).
 
	- When called with an lvalue of type const string, T is deduced to be const string& , so
	  Move() takes const string& (after collapsing) and returns const string&& (after RemoveReference).
 
	- When called with an rvalue of type string, T is deduced to be string , so
	  Move() takes string&& and returns string&& .
 
	- When called with an rvalue of type const string, T is deduced to be const string ,
	  so Move() takes const string&& and returns const string&& .
 
This is how Move() preserves the type and constness of its argument, but converts lvalues into rvalues.
 
the past
--------
 
To learn more about rvalue references, you can read their proposal papers.
Note that things have changed since these proposals were written;
rvalue references have been integrated into the C++0x Working Paper, where they're continuing to receive wording tweaks.
Some parts of the proposals are incorrect, outdated, or discussing alternatives that weren't adopted.
Still, they're very informative.
 
N1377, N1385, and N1690 are the main proposal papers.
N2118 contains the final revision of the proposed wording before it was integrated into the Working Paper.
N1784, N1821, N2377, and N2439 trace the evolution of "Extending Move Semantics To *this", which has been integrated into C++0x but not yet implemented in VC10.
 
the future
----------
 
N2812
	"A Safety Problem With Rvalue References (and what to do about it)"
proposes a change to the initialization rules, forbidding rvalue references from binding to lvalues.
It turns out that this won't affect the move semantics and perfect forwarding patterns,
so it won't invalidate the new techniques that you just learned (but it will change how std::move() and std::forward() are implemented).
 
Stephan T. Lavavej
Visual C++ Libraries Developer

*/

int main(int argc, char * argv[])
{
	return 0;
}
