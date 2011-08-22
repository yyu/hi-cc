#include <iostream>

class Dog
{
public:
	virtual void shout(void) { std::cout << "Dog shouts.\n"; }
	virtual void drink(void) { std::cout << "Dog drinks.\n"; }
};

class Husky : public Dog
{
public:
	void shout(void) { std::cout << "Husky shouts.\n"; }
};

class Jing8 : public Dog
{
public:
	void shout(void) { std::cout << "Jing 8 shouts.\n"; }
	void drink(void) { std::cout << "Jing 8 drinks.\n"; }
	virtual void eat  (void) { std::cout << "Jing 8 eats.\n"; }
};

void test()
{
	Husky h;
	h.shout();		// non-virtual
	(&h)->shout();		// non-virtual

	Dog * pd = &h;

	pd->shout();		// virual
	pd->Dog::shout();	// non-virtual
	((Husky*)pd)->shout();	// virtual

	((Jing8*)pd)->shout();	// virtual
	((Jing8*)pd)->eat();	// non-virtual
	((Jing8*)pd)->drink();	// virtual
}

int main()
{
	test();
	return 0;
}
