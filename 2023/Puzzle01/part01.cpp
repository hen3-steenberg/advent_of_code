#include <iostream>
#include <string>
#include <algorithm>


constexpr bool IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

int main()
{
	size_t sum = 0;
	char number[4] = "00\n";
	std::cout << "   00\n";
	for (std::string line; std::getline(std::cin, line);)
	{
		if (line.empty()) break;
		auto First = std::find_if(line.cbegin(), line.cend(), IsDigit);
		number[0] = (First != line.cend()) ? *First : '0';
		sum += 10 * (number[0] - '0');

		auto Last = std::find_if(line.rbegin(), line.rend(), IsDigit);
		number[1] = (Last != line.rend()) ? *Last : '0';
		sum += number[1] - '0';
		std::cout << " + " << number;
	}
	std::cout << " = " << sum << std::endl;
	return 0;
}