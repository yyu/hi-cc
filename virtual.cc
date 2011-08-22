#include <iostream>
#include <typeinfo>

class Animal
{
public:
	Animal(void) { std::cout << "Animal born." << std::endl; }
	virtual ~Animal(void) { std::cout << "Animal dies." << std::endl; }

	void eat000(void) { std::cout << "Animal eats 000." << std::endl; }
	void eat001(void) { std::cout << "Animal eats 001." << std::endl; }
	void eat010(void) { std::cout << "Animal eats 010." << std::endl; }
	void eat011(void) { std::cout << "Animal eats 011." << std::endl; }
	virtual void eat100(void) { std::cout << "Animal eats 100." << std::endl; }
	virtual void eat101(void) { std::cout << "Animal eats 101." << std::endl; }
	virtual void eat110(void) { std::cout << "Animal eats 110." << std::endl; }
	virtual void eat111(void) { std::cout << "Animal eats 111." << std::endl; }
};

class Dog : public Animal
{
public:
	Dog(void) { std::cout << "\tDog born." << std::endl; }
	~Dog(void) { std::cout << "\tDog dies." << std::endl; }

	void eat000(void) { std::cout << "\tDog eats 000." << std::endl; }
	void eat001(void) { std::cout << "\tDog eats 001." << std::endl; }
	virtual void eat010(void) { std::cout << "\tDog eats 010." << std::endl; }
	virtual void eat011(void) { std::cout << "\tDog eats 011." << std::endl; }
	void eat100(void) { std::cout << "\tDog eats 100." << std::endl; }
	void eat101(void) { std::cout << "\tDog eats 101." << std::endl; }
	virtual void eat110(void) { std::cout << "\tDog eats 110." << std::endl; }
	virtual void eat111(void) { std::cout << "\tDog eats 111." << std::endl; }
};

class Husky : public Dog
{
public:
	Husky(void) { std::cout << "\t\tHusky born.\n"; }
	~Husky(void) { std::cout << "\t\tHusky dies.\n"; }

	void eat000(void) { std::cout << "\t\tHusky eats 000." << std::endl; }
	virtual void eat001(void) { std::cout << "\t\tHusky eats 001." << std::endl; }
	void eat010(void) { std::cout << "\t\tHusky eats 010." << std::endl; }
	virtual void eat011(void) { std::cout << "\t\tHusky eats 011." << std::endl; }
	void eat100(void) { std::cout << "\t\tHusky eats 100." << std::endl; }
	virtual void eat101(void) { std::cout << "\t\tHusky eats 101." << std::endl; }
	void eat110(void) { std::cout << "\t\tHusky eats 110." << std::endl; }
	virtual void eat111(void) { std::cout << "\t\tHusky eats 111." << std::endl; }
};

template <class TP, class TC>
void test(void)
{
	TP * p = new TC;

	std::cout << "------------------------------ <"
		  << typeid(TP).name() << ", "
		  << typeid(TC).name() << ">\n";

	p->eat000();
	p->eat001();
	p->eat010();
	p->eat011();
	p->eat100();
	p->eat101();
	p->eat110();
	p->eat111();

	delete p;

	std::cout << std::endl;
}

int main(void)
{
	test<Animal, Husky>();
	test<Animal, Dog>();
	test<Dog, Husky>();
	test<Husky, Husky>();

	return 0;
}
