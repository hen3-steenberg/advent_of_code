#include <vector>
#include <string>
#include <string_view>
#include <bitset>
#include <iostream>
#include "ctre.hpp"


constexpr const size_t width = 141;

struct part_number
{
	part_number() noexcept
		: number(0), placement() {}

	part_number(size_t num, std::bitset<width> place)
		: number(num), placement(place) {}

	size_t number;
	std::bitset<width> placement;
};

std::bitset<width> set_range(size_t first, size_t last)
{
	std::bitset<width> result;

	size_t _first = (first > 0)? first - 1 : 0;

	for (size_t pos = _first; pos <= last; ++pos)
	{
		result.set(pos);
	}
	return result;
}

std::vector<part_number> get_part_numbers(std::string const& line)
{
	std::vector<part_number> result;
	for (auto const& match : ctre::range<"[0-9]+">(line))
	{
		size_t first = match.begin() - line.begin();
		size_t last = match.get_end_position() - line.begin();

		result.emplace_back(match.to_number<size_t>(), set_range(first, last));
	}
	return result;
}

std::bitset<width> get_component_locations(std::string const& line)
{
	std::bitset<width> result;
	for (auto const & match : ctre::range<"[^\\\\.0-9]">(line))
	{
		size_t position = match.begin() - line.begin();
		result.set(position);
	}
	return result;
}


int main()
{
	size_t sum = 0;
	std::vector<part_number> prev_parts;
	std::bitset<width> prev_components;
	for (std::string line; std::getline(std::cin, line);)
	{
		if (line.empty()) break;

		std::bitset<width> components = get_component_locations(line);
		std::vector<part_number> parts = get_part_numbers(line);


		for (auto const& part : prev_parts)
		{
			if ((part.placement & components).any())
			{
				sum += part.number;
			}
		}

		prev_parts.clear();

		for (auto const& part : parts)
		{
			if ((part.placement & prev_components).any() || (part.placement & components).any())
			{
				sum += part.number;
			}
			else
			{
				prev_parts.push_back(part);
			}
		}

		prev_components = components;

	}
	std::cout << "sum = " << sum << std::endl;
	return 0;
}