#pragma once

#include <algorithm>
#include <neo/iterator_facade.hpp>

#include "reverse_only_alpha_utils.hpp"

namespace anon {

  template <typename ForwardIter, typename ReverseIter> class reverse_only_alpha_t
      : public neo::iterator_facade<reverse_only_alpha_t<ForwardIter, ReverseIter>> {
    using fIt = ForwardIter;
    using rIt = ReverseIter;

    fIt _begin, _end;
    rIt _rbegin, _rend;
    char _current{};

  public:
    constexpr reverse_only_alpha_t(fIt begin, fIt end, rIt rbegin, rIt rend)
        : _begin(begin), _end(end), _rbegin(rbegin), _rend(rend) {
      increment();
    }

    [[nodiscard]] constexpr char dereference() const noexcept { return _current; }

    constexpr void increment() {
      if (const char c = detail::get_and_increment(_begin); detail::isalpha(c)) {
        _rbegin = std::find_if(_rbegin, _rend, &detail::isalpha);
        _current = detail::get_and_increment(_rbegin);
      } else {
        _current = c;
      }
    }

    [[nodiscard]] constexpr std::ptrdiff_t distance_to(self_type o) const noexcept {
      return o._begin - _begin;
    }

    [[nodiscard]] constexpr bool equal_to(self_type o) const noexcept {
      return o._begin == _begin && o._end == _end;
    }
  };

  template <typename ForwardIter, typename ReverseIter>
  reverse_only_alpha_t(ForwardIter, ForwardIter, ReverseIter, ReverseIter)
      -> reverse_only_alpha_t<ForwardIter, ReverseIter>;

}  // namespace anon
