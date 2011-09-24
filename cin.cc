#include <iostream>

int main(void)
{
	std::string s;
	std::cout << "please input a string: ";
	std::cin >> s;
	std::cout << "a string: " << s << std::endl;

	char c;
	std::cout << "please input a char: ";
	std::cin >> c;
	std::cout << "a char: " << c
		  << std::hex << std::uppercase
		  << " (0x" << int(c) << ") "
		  << std::endl;

	int i;
	std::cout << "please input a integer: ";
	std::cin >> i;
	std::cout << "a integer: " << i << std::endl;

	return 0;
}
