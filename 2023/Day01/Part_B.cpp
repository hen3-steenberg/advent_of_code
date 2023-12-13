#include <iostream>
#include <string>
#include <algorithm>
#include <string_view>

using namespace std::literals;

constexpr bool IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

constexpr char translate_first_digit(std::string_view str)
{
	if (IsDigit(str.back())) return str.back();
	else if (str.ends_with("zero"sv)) return '0';
	else if (str.ends_with("one"sv)) return '1';
	else if (str.ends_with("two"sv)) return '2';
	else if (str.ends_with("three"sv)) return '3';
	else if (str.ends_with("four"sv)) return '4';
	else if (str.ends_with("five"sv)) return '5';
	else if (str.ends_with("six"sv)) return '6';
	else if (str.ends_with("seven"sv)) return '7';
	else if (str.ends_with("eight"sv)) return '8';
	else if (str.ends_with("nine"sv)) return '9';
	else return 0;
}

constexpr char get_first_digit(std::string_view str)
{
	for (size_t count = 1; count <= str.size(); ++count)
	{
		char digit = translate_first_digit(str.substr(0, count));
		if (IsDigit(digit)) return digit;
	}
	return '0';
}

constexpr char translate_last_digit(std::string_view str)
{
	if (IsDigit(str.front())) return str.front();
	else if (str.starts_with("zero"sv)) return '0';
	else if (str.starts_with("one"sv)) return '1';
	else if (str.starts_with("two"sv)) return '2';
	else if (str.starts_with("three"sv)) return '3';
	else if (str.starts_with("four"sv)) return '4';
	else if (str.starts_with("five"sv)) return '5';
	else if (str.starts_with("six"sv)) return '6';
	else if (str.starts_with("seven"sv)) return '7';
	else if (str.starts_with("eight"sv)) return '8';
	else if (str.starts_with("nine"sv)) return '9';
	else return 0;
}

constexpr char get_last_digit(std::string_view str)
{
	for (size_t count = str.size(); count > 0; --count)
	{
		char digit = translate_last_digit(str.substr(count - 1));
		if (IsDigit(digit)) return digit;
	}
	return '0';
}

int main()
{
	size_t sum = 0;
	char number[4] = "00\n";
	std::cout << "   00\n";
	for (std::string line; std::getline(std::cin, line);)
	{
		if (line.empty()) break;
		number[0] = get_first_digit(line);
		sum += 10 * (number[0] - '0');

		number[1] = get_last_digit(line);
		sum += number[1] - '0';
		std::cout << " + " << number;
	}
	std::cout << " = " << sum << std::endl;
	return 0;
}