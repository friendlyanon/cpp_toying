#include <fmt/core.h>

#include <string>

#include "reverse_only_alpha.hpp"

[[nodiscard]] std::string reverse_only_alpha(const std::string& string) {
  if (string.length() < 2) {
    return {string};
  }

  // This is pretty ugly...
  auto begin_it
      = reverse_only_alpha_t(string.begin(), string.end(), string.rbegin(), string.rend());
  const auto end_it
      = reverse_only_alpha_t(string.end(), string.end(), string.rend(), string.rend());

  return {begin_it, end_it};
}

int main() {
  const std::string string = "lol-lmao";
  const std::string reversed_alpha = reverse_only_alpha(string);

  fmt::print("Before: {}\n", string);
  fmt::print("After: {}\n", reversed_alpha);
}
