//
// Created by amirt on 11/21/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_TIMER_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_TIMER_HPP_

#include <concepts>
#include <ctime>

#include "HardwareClock.hpp"
#include "ManualClock.hpp"

namespace cmn::tm {

template <class Tc>
class Stopwatch {
 public:
  void Start() {
    running = true;
    start_time = Tc::Now();
  }

  void Stop() {
    running = false;
    stop_time = Tc::Now();
  }

  [[nodiscard]] Time GetElapsedTime() const {
    return running ? Tc::Now() : stop_time - start_time;
  }

  void Reset() noexcept {
    running = false;
    start_time = stop_time = Tc::Now();
  }

  [[nodiscard]] bool GetRunning() const noexcept { return running; }

  [[nodiscard]] Time GetStartTime() const noexcept { return start_time; }

  [[nodiscard]] Time GetStopTime() const noexcept { return stop_time; }

 private:
  bool running{};

  Time start_time{};
  Time stop_time{};
};

using HStopwatch = Stopwatch<HardwareClock>;
using MStopwatch = Stopwatch<ManualClock>;

}  // namespace cmn::tm

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_TIMER_HPP_
