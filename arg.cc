#include <cstdlib>
#include <iostream>
#include <vector>

int main(int argc, char * argv[])
{
	typedef std::vector<std::string> strvec;
	strvec params(argv, argv + argc);

	for (strvec::const_iterator it = params.begin(); it != params.end(); ++it)
		std::cout << *it << "+";
	std::cout << std::endl;

	for (int i = 1; i < argc; ++i)
		std::cout << params[i] << "#";
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
