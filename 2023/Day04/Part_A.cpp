#include <string>
#include <iostream>
#include "Day04.hpp"





int main()
{
	size_t sum = 0;
	for (std::string line; std::getline(std::cin, line);)
	{
		if (line.empty()) break;

		sum += calculate_card_winnings(line);
	}
	std::cout << "sum = " << sum << std::endl;
	return 0;
}