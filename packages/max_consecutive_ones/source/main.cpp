#include <fmt/core.h>
#include <fmt/format.h>

#include <algorithm>
#include <vector>

static constexpr bool is_one(int i) { return i == 1; }

static constexpr bool is_not_one(int i) { return !is_one(i); }

[[nodiscard]] std::ptrdiff_t max_consecutive_ones(const std::vector<int>& numbers) {
  auto begin = numbers.begin();
  const auto end = numbers.end();
  begin = std::find_if(begin, end, is_one);
  if (begin == end) {
    return 0;
  }

  std::ptrdiff_t result = 0;
  for (;;) {
    const auto previous = begin++;
    begin = std::find_if(begin, end, is_not_one);

    const auto difference = begin - previous;
    if (difference > result) {
      result = difference;
    }

    if (begin == end) {
      break;
    }

    begin = std::find_if(++begin, end, is_one);
    if (begin == end) {
      break;
    }
  }

  return result;
}

int main() {
  const std::vector numbers{1, 1, 0, 1, 1, 1};
  const auto max_consecutive = max_consecutive_ones(numbers);

  fmt::print("[{}]\n", fmt::join(numbers, ", "));
  fmt::print("Max number of consecutive ones: {}\n", max_consecutive);
}
