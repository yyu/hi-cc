#include <iostream>

class Animal {
public:
	Animal(void)
	{
		std::cout << "Animal born." << std::endl;
	}

	virtual void eat(void)
	{
		std::cout << "Animal eats." << std::endl;
	}
	
	virtual ~Animal(void)
	{
		std::cout << "Animal dies." << std::endl;
	}
};

class Dog : public Animal
{
public:
	Dog(void)
	{
		std::cout << "Dog born." << std::endl;
	}

	virtual void eat(void)
	{
		std::cout << "Dog eats." << std::endl;
	}

	~Dog(void)
	{
		std::cout << "Dog dies." << std::endl;
	}
};

int main(void)
{
	Animal * a = new Dog;
	a->eat();
	delete a;

	return 0;
}
