#include <fmt/core.h>

#include <string>

#include "reverse_only_alpha.hpp"

[[nodiscard]] std::string reverse_only_alpha(const std::string& string) {
  if (string.length() < 2) {
    return {string};
  }

  // This is pretty ugly...
#define iter reverse_only_alpha_t
#define args(type) string.type(), string.end(), string.r##type(), string.rend()
  auto begin_it = iter(args(begin));
  const auto end_it = iter(args(end));
#undef args
#undef iter

  return {begin_it, end_it};
}

int main() {
  const std::string string = "lol-lmao";
  const std::string reversed_alpha = reverse_only_alpha(string);

  fmt::print("Before: {}\n", string);
  fmt::print("After: {}\n", reversed_alpha);
}
