#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char * argv[])
{
	ostream_iterator<string> oo(cout);
	*oo = "Hello, ";
	++oo;
	*oo = "World!\n";
	return 0;
}
