//
// Created by amirt on 11/22/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_STAGEHANDLER_STAGE_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_STAGEHANDLER_STAGE_HPP_

#include <functional>
#include <utility>

#include "Time.hpp"

namespace cmn::sgs {

struct Stage {
  std::function<void()> stage_function;
  tm::Time start_time;
  tm::Time end_time;

  Stage(std::function<void()> stage_function, tm::Time start_time, tm::Time end_time)
      : stage_function(std::move(stage_function)), start_time(start_time), end_time(end_time) {};

  Stage(std::function<void()> stage_function, tm::Time start_time)
      : Stage(std::move(stage_function),
              start_time,
              {std::numeric_limits<long long>::max(),
               std::numeric_limits<long long>::max()}) {};

  explicit Stage(std::function<void()> stage_function)
      : Stage(std::move(stage_function), {}) {};
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_STAGEHANDLER_STAGE_HPP_
