#include <string>
#include <vector>
#include <iostream>
#include "ctre.hpp"
#include "Day04.hpp"

std::vector<uint8_t> get_winning_numbers(std::string_view card)
{
	std::vector<uint8_t> result;

	size_t start = card.find(':', 0) + 1;
	size_t stop = card.find('|', start);

	for (auto const& match : ctre::range<"[0-9]+">(card.substr(start, stop - start)))
	{
		result.push_back(match.to_number<uint8_t>());
	}
	std::ranges::sort(result);
	return result;
}

uint16_t calculate_card_winnings(std::string_view card)
{
	std::string_view card_number_str = card.substr(0, card.find(':'));

	std::vector winning_numbers = get_winning_numbers(card);

	uint16_t result = 0;
	for (auto const& match : ctre::range<"[0-9]+">(card.substr(card.find('|') + 1)))
	{
		if (std::ranges::binary_search(winning_numbers, match.to_number<uint8_t>()))
		{
			if (result) result *= 2;
			else result = 1;
		}
	}

	std::cout << card_number_str << " = " << result << " points\n";

	return result;
}

size_t count_card_winnings(std::string_view card)
{
	std::string_view card_number_str = card.substr(0, card.find(':'));

	std::vector winning_numbers = get_winning_numbers(card);

	size_t result = 0;
	for (auto const& match : ctre::range<"[0-9]+">(card.substr(card.find('|') + 1)))
	{
		if (std::ranges::binary_search(winning_numbers, match.to_number<uint8_t>()))
		{
			result++;
		}
	}

	std::cout << card_number_str << " = " << result << " points\n";

	return result;
}