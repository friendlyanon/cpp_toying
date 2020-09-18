#pragma once

#include <cctype>

namespace anon::detail {

  static constexpr auto get_and_increment(auto& pointer) noexcept {
    const auto value = *pointer;
    ++pointer;
    return value;
  }

  static inline bool isalpha(char c) noexcept { return std::isalpha(c); }

}  // namespace anon::detail
