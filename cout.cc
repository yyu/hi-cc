#include <iostream>
#include <iterator>

int main(int argc, char * argv[])
{
	std::ostream_iterator<string> oo(std::cout);
	*oo = "Hello, ";
	++oo;
	*oo = "World!\n";
	return 0;
}
