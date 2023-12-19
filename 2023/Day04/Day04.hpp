#ifndef DAY_04_DEFINITIONS
#define DAY_04_DEFINITIONS 1

#include <string_view>
#include <array>
#include <algorithm>
#include <cassert>

size_t count_card_winnings(std::string_view card);
uint16_t calculate_card_winnings(std::string_view card);

template<size_t N>
struct scratch_cards {
	std::array<std::array<size_t, N + 1>, 2> future_card_counts;

	size_t total;
	bool current_index;

	scratch_cards()
		: future_card_counts(), total(0), current_index(false)
	{}

	void process_next_card(std::string_view card)& {
		size_t winning_amount = count_card_winnings(card);
		assert(winning_amount <= N);
		size_t index = current_index ? 1 : 0;
		size_t next_index = current_index ? 0 : 1;

		std::copy_n(future_card_counts[index].begin() + 1, N, future_card_counts[next_index].begin());
		size_t card_count = future_card_counts[index][0] + 1;
		for (size_t card_index = 0; card_index < winning_amount; ++card_index)
		{
			future_card_counts[next_index][card_index] += card_count;
		}
		total += card_count;
		current_index = !current_index;
	}
};

#endif