#include <string>
#include <iostream>
#include "Day04.hpp"

int main()
{
	scratch_cards<10> card_counter;
	for (std::string line; std::getline(std::cin, line);)
	{
		if (line.empty()) break;
		card_counter.process_next_card(line);
		
	}
	std::cout << "sum = " << card_counter.total << std::endl;
	return 0;
}