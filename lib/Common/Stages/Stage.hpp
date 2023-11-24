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
  std::function<void()> stageFunction;
  tm::Time startTime;
  tm::Time endTime;

  Stage(std::function<void()> stageFunction, tm::Time startTime, tm::Time endTime)
      : stageFunction(std::move(stageFunction)), startTime(startTime), endTime(endTime) {};

  Stage(std::function<void()> stageFunction, tm::Time startTime)
      : Stage(std::move(stageFunction),
              startTime,
              {std::numeric_limits<long long>::max(),
               std::numeric_limits<long long>::max()}) {};

  explicit Stage(std::function<void()> stageFunction)
      : Stage(std::move(stageFunction), {}) {};
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_STAGEHANDLER_STAGE_HPP_
