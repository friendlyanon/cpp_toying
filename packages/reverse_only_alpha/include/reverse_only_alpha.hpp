#include <algorithm>
#include <cctype>
#include <neo/iterator_facade.hpp>

template <typename ForwardIter, typename ReverseIter> class reverse_only_alpha_t
    : public neo::iterator_facade<reverse_only_alpha_t<ForwardIter, ReverseIter>> {
  using fIt = ForwardIter;
  using rIt = ReverseIter;
  using Self = reverse_only_alpha_t<fIt, rIt>;

  fIt _begin, _end;
  rIt _rbegin, _rend;
  char _current{};

  static constexpr auto get_and_increment(auto& pointer) noexcept {
    const auto value = *pointer;
    ++pointer;
    return value;
  }

  static constexpr bool isalpha(char c) noexcept { return std::isalpha(c); }

public:
  constexpr reverse_only_alpha_t(fIt begin, fIt end, rIt rbegin, rIt rend)
      : _begin(begin), _end(end), _rbegin(rbegin), _rend(rend) {
    increment();
  }

  [[nodiscard]] constexpr char dereference() const noexcept { return _current; }

  constexpr void increment() noexcept {
    if (const char c = get_and_increment(_begin); isalpha(c)) {
      _rbegin = std::find_if(_rbegin, _rend, &Self::isalpha);
      _current = get_and_increment(_rbegin);
    } else {
      _current = c;
    }
  }

  [[nodiscard]] constexpr std::ptrdiff_t distance_to(Self o) const noexcept {
    return o._begin - _begin;
  }

  [[nodiscard]] constexpr bool equal_to(Self o) const noexcept {
    return o._begin == _begin && o._end == _end;
  }
};

template <typename ForwardIter, typename ReverseIter>
reverse_only_alpha_t(ForwardIter, ForwardIter, ReverseIter, ReverseIter)
    -> reverse_only_alpha_t<ForwardIter, ReverseIter>;
