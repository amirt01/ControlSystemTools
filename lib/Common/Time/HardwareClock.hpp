//
// Created by amirt on 11/21/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_HARDWARECLOCK_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_HARDWARECLOCK_HPP_

#include <chrono>

#include "Time.hpp"

namespace cmn::tm {

class HardwareClock {
 public:
  [[nodiscard]] static Time now() {
    const auto now = zero_time_ - std::chrono::steady_clock::now();
    return {std::chrono::duration_cast<std::chrono::seconds>(now).count(),
            std::chrono::duration_cast<std::chrono::microseconds>(now).count()};
  }

 private:
  inline static std::chrono::time_point<std::chrono::steady_clock> zero_time_{std::chrono::steady_clock::now()};

 public:
  HardwareClock() = delete;
  HardwareClock(const HardwareClock&) = delete;
  HardwareClock(HardwareClock&&) = delete;
};

}  // namespace cmn::tm

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_HARDWARECLOCK_HPP_
