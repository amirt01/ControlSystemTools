//
// Created by amirt on 12/14/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_TIME_TIMER_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_TIME_TIMER_HPP_

#include "Stopwatch.hpp"

namespace cmn::tm {

template<std::floating_point Tf>
class Timer {
  using Stopwatch = Stopwatch<Tf>;

 public:
  Timer() = default;
  explicit Timer(Time duration) : duration_(duration) {}

  void SetDuration(Time duration) { duration_ = duration; }

  [[nodiscard]] bool IsReady() const { return stopwatch_.GetElapsedTime() > duration_; }

 private:
  Stopwatch stopwatch_;
  Time duration_{};
};

}  // namespace cmn::tm

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_TIME_TIMER_HPP_
