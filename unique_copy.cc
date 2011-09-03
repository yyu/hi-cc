#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

#include <cstdlib>

int main(int argc, char * argv[])
{
	const int nums[] = {1, 3, 1, 3, 2, 5};
	int nums_len = sizeof(nums) / sizeof(nums[0]);

	std::ostream_iterator<int> out_it(std::cout, "|");

	std::vector<int> v(nums, nums + nums_len);

	std::cout << "Input : ";
	std::copy(v.begin(), v.end(), out_it);
	std::cout << std::endl;

	std::sort(v.begin(), v.end());
	std::cout << "Sorted: ";
	std::copy(v.begin(), v.end(), out_it);
	std::cout << std::endl;

	std::cout << "Output: ";
	std::unique_copy(v.begin(), v.end(), out_it);
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
