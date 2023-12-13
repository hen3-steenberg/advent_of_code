#include <iostream>
#include <string>
#include <string_view>
#include "ctre.hpp"

using namespace std::literals;

constexpr size_t get_game_id(std::string const& line) noexcept
{
	return ctre::match<"^\\D*(?<id>\\d*):.*$">(line).get<"id">().to_number<size_t>();
}

size_t GetRequiredPower(std::string const& line)
{
	size_t blue = 0;
	size_t green = 0;
	size_t red = 0;
	for (auto const& dice : ctre::range<"(?<number>\\d*)\\s*(?<color>blue|green|red)">(line))
	{
		std::string_view color = dice.get<"color">().to_view();
		size_t number = dice.get<"number">().to_number<size_t>();
		if ("blue"sv == color && number > blue)
		{
			blue = number;
		}
		else if ("green"sv == color && number > green)
		{
			green = number;
		}
		else if ("red"sv == color && number > red)
		{
			red = number;
		}
	}

	std::cout << get_game_id(line) << " : blue = " << blue << ", green = " << green << ", red = " << red << "\n";

	return blue*green*red;
}

int main()
{



	size_t sum = 0;
	for (std::string line; std::getline(std::cin, line);)
	{
		if (line.empty()) break;

		sum += GetRequiredPower(line);

	}
	std::cout << "sum = " << sum << std::endl;
	return 0;
}