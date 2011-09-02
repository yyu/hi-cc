#include <iostream>
#include <vector>

int main(int argc, char * argv[])
{
	std::vector<int> a(8, 1);

	// a[i]
	for (unsigned int i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << std::endl;

	// iterator
	for (std::vector<int>::const_iterator it = a.begin(); it != a.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	return 0;
}
