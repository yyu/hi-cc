#include <iostream>

using namespace std;

class BadBoy {};
class Foo
{
public:
	Foo() {}
	~Foo() {}
	void bar(void)
	{
		cout << "bar0" << endl;
		throw BadBoy();
		cout << "bar1";
	}
};

int main(int argc, char * argv[])
{
	Foo foo;
	try {
		foo.bar();
	} catch (BadBoy) {
		cout << "bad" << endl;
	}
	return 0;
}
