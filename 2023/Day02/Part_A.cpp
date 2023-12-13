#include <iostream>
#include <string>
#include <string_view>
#include "ctre.hpp"

using namespace std::literals;

constexpr size_t get_game_id(std::string const& line) noexcept
{
	return ctre::match<"^\\D*(?<id>\\d*):.*$">(line).get<"id">().to_number<size_t>();
}

constexpr bool IsPossibleGame(std::string const& line)
{
	for (auto const & dice : ctre::range<"(?<number>\\d*)\\s*(?<color>blue|green|red)">(line))
	{
		std::string_view color = dice.get<"color">().to_view();
		int number = dice.get<"number">().to_number();
		if ("blue"sv == color && number > 14)
		{
			std::cout << " ~ blue\t: " << number << "\n";
			return false;
		}
		else if ("green"sv == color && number > 13)
		{
			std::cout << " ~ green\t: " << number << "\n";
			return false;
		}
		else if ("red"sv == color && number > 12)
		{
			std::cout << " ~ red\t\t: " << number << "\n";
			return false;
		}
	}
	return true;
}

int main()
{

	

	size_t sum = 0;
	for (std::string line; std::getline(std::cin, line);)
	{
		if (line.empty()) break;
		size_t id = get_game_id(line);
		std::cout << id << std::endl;
		if (IsPossibleGame(line))
		{
			sum += id;
		}
		
	}
	std::cout << "sum = " << sum << std::endl;
	return 0;
}