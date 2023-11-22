//
// Created by amirt on 11/21/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_MANUALCLOCK_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_MANUALCLOCK_HPP_

#include "Time.hpp"

namespace cmn::tm {

class ManualClock {
 public:
  static void Reset() noexcept { currentTime = {0, 0}; }

  [[nodiscard]] static Time Now() noexcept { return currentTime; }

  static void Advance(const Time& additionalTime) noexcept {
    currentTime += additionalTime;
  }

  static void Advance(const long long seconds, const long long microseconds) noexcept {
    Advance({seconds, microseconds});
  }

 private:
  inline static Time currentTime{};

 public:
  ManualClock() = delete;
  ManualClock(const ManualClock&) = delete;
  ManualClock(ManualClock&&) = delete;
};

}  // namespace cmn::tm

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_MANUALCLOCK_HPP_
