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
    running_ = true;
    start_time_ = Tc::Now();
  }

  void Stop() {
    running_ = false;
    stop_time_ = Tc::Now();
  }

  [[nodiscard]] Time GetElapsedTime() const {
    return running_ ? Tc::Now() - start_time_ : stop_time_ - start_time_;
  }

  void Reset() noexcept {
    running_ = false;
    start_time_ = stop_time_ = Tc::Now();
  }

  [[nodiscard]] bool GetRunning() const noexcept { return running_; }

  [[nodiscard]] Time GetStartTime() const noexcept { return start_time_; }

  [[nodiscard]] Time GetStopTime() const noexcept { return stop_time_; }

 private:
  bool running_{};

  Time start_time_{};
  Time stop_time_{};
};

using HStopwatch = Stopwatch<HardwareClock>;
using MStopwatch = Stopwatch<ManualClock>;

}  // namespace cmn::tm

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_TIMER_HPP_
