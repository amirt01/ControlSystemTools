//
// Created by amirt on 11/21/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_CLOCK_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_CLOCK_HPP_

#include <ostream>
#include <cstdint>
#include <compare>
#include <cassert>

namespace cmn::tm {

struct Time {
  long long seconds, microseconds;

  constexpr double AsSeconds() const { return seconds + microseconds * 1e-6; }

  constexpr auto operator<=>(const Time&) const = default;

  [[nodiscard]] constexpr Time operator+(const Time& rhs) const noexcept {
    return {seconds + rhs.seconds, microseconds + rhs.microseconds};
  }

  constexpr Time& operator+=(const Time& rhs) noexcept {
    return *this = *this + rhs;
  }

  [[nodiscard]] constexpr Time operator-(const Time& rhs) const {
    assert(*this >= rhs);
    return {seconds - rhs.seconds, microseconds - rhs.microseconds};
  }

  constexpr Time& operator-=(const Time& rhs) noexcept {
    return *this = *this - rhs;
  }
};

std::ostream& operator<<(std::ostream& os, const Time& time) {
  return os << time.seconds << "s, " << time.microseconds << "us";
}

} // namespace cmn::tm

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_CLOCK_HPP_
