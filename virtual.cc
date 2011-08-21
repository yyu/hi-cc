#include <iostream>

class Animal
{
public:
	Animal(void) { std::cout << "Animal born." << std::endl; }
	virtual ~Animal(void) { std::cout << "Animal dies." << std::endl; }

	virtual void eat(void) { std::cout << "\tAnimal eats." << std::endl; }
	virtual void drink(void) { std::cout << "\tAnimal drinks.\n"; }
	void pee(void) { std::cout << "\tAnimals pee.\n"; }
	void poo(void) { std::cout << "\tAnimals poo.\n"; }
};

class Dog : public Animal
{
public:
	Dog(void) { std::cout << "Dog born." << std::endl; }
	~Dog(void) { std::cout << "Dog dies." << std::endl; }

	virtual void eat(void) { std::cout << "\tDog eats." << std::endl; }
	void drink(void) { std::cout << "\tDog drinks.\n"; }
	virtual void pee(void) { std::cout << "\tDogs pee.\n"; }
	void poo(void) { std::cout << "\tDogs poo.\n"; }
};

class Husky : public Dog
{
	Husky(void) { std::cout << "\t\tHusky born.\n"; }
	~Husky(void) { std::cout << "\t\tHusky dies.\n"; }
};

int main(void)
{
	Animal * a = new Dog;
	a->eat();
	a->drink();
	a->pee();
	a->poo();
	delete a;

	std::cout << "\n";

	Dog * b = new Dog;
	b->eat();
	b->drink();
	b->pee();
	b->poo();
	delete b;

	return 0;
}
