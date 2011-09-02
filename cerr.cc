// see http://rosettacode.org/wiki/Hello_world/Standard_error#C.2B.2B

#include <iostream>

int main(int argc, char * argv[])
{
	std::cerr << "cerr\n";
	return std::cerr.bad();
}
