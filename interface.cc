#include <iostream>

#define Interface class

Interface Runnable
{
public:
	virtual ~Runnable() {}
	virtual void run() = 0;
};

class Animal
{
public:
	Animal(void)
	{
		std::cout << "Animal born." << std::endl;
	}

	virtual ~Animal(void)
	{
		std::cout << "Animal dies." << std::endl;
	}
};

class Dog : public Animal, public Runnable
{
public:
	Dog(void)
	{
		std::cout << "Dog born." << std::endl;
	}

	virtual void run(void)
	{
		std::cout << "Dog runs." << std::endl;
	}

	~Dog(void)
	{
		std::cout << "Dog dies." << std::endl;
	}
};

int main(void)
{
	Runnable * x = new Dog;
	x->run();

	delete x;

	return 0;
}
