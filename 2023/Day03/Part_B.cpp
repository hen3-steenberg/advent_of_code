#include <vector>
#include <string>
#include <string_view>
#include <bitset>
#include <iostream>
#include <algorithm>
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

	size_t _first = (first > 0) ? first - 1 : 0;

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

size_t mult_gear_parts(std::vector<part_number> const& parts, size_t pos)
{
	size_t sum = 1;
	for (auto const& part : parts)
	{
		if (part.placement.test(pos))
		{
			sum *= part.number;
		}
	}
	return sum;
}




int main()
{
	std::vector<part_number> prev_parts;
	std::vector<part_number> curr_parts;
	std::vector<part_number> next_parts;
	std::string current_line = "";
	size_t sum = 0;
	for (std::string next_line; std::getline(std::cin, next_line);)
	{
		

		prev_parts = curr_parts;
		curr_parts = next_parts;
		next_parts = get_part_numbers(next_line);
		for (auto const& match : ctre::range<"\\*">(current_line))
		{
			size_t component_position = match.begin() - current_line.begin();
			size_t part_count = 0;
			auto is_adjecent = [component_position](part_number const& part)
				{
					return part.placement.test(component_position);
				};
			part_count += std::ranges::count_if(prev_parts, is_adjecent);
			part_count += std::ranges::count_if(curr_parts, is_adjecent);
			part_count += std::ranges::count_if(next_parts, is_adjecent);

			if (part_count == 2)
			{
				size_t gear_ratio = 1;
				gear_ratio *= mult_gear_parts(prev_parts, component_position);
				gear_ratio *= mult_gear_parts(curr_parts, component_position);
				gear_ratio *= mult_gear_parts(next_parts, component_position);
				sum += gear_ratio;
			}
		}
		current_line = next_line;
		if (next_line.empty()) break;
	}
	std::cout << "sum = " << sum << std::endl;
	return 0;
}