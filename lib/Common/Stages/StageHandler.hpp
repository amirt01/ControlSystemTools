//
// Created by amirt on 11/23/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_STAGEHANDLER_STAGEHANDLER_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_STAGEHANDLER_STAGEHANDLER_HPP_

#include <queue>
#include <ranges>
#include <algorithm>
#include <iterator>

#include "Stage.hpp"

namespace cmn::sgs {

class StageHandler {
 public:
  StageHandler() = default;

  StageHandler(const std::initializer_list<Stage>& stages, const tm::Time& startTime = {})
      : stages(stages), startTime(startTime) {
    // Validate that none of the stages overlap
    if (!stages.end()) {
      for (auto stageItr = stages.begin(); std::next(stageItr) != stages.end(); stageItr++) {
        assert((void("A stage's start time and the previous stage's end time cannot overlap"),
            stageItr->endTime >= std::next(stageItr)->startTime));
      }
    }
  }

  void AddStage(const Stage& newStage) {
    assert((void("New stage's start time and the last stage's end time cannot overlap"),
        !stages.empty() ? newStage.startTime >= stages.back().endTime : true));
    stages.push_back(newStage);
  }

  void Update(const tm::Time& time) {
    // Correct time based on startTime
    const tm::Time runningTime{time - startTime};

    // Check if we reached the last stage
    auto IndexIsInactive = [this, &runningTime] {
      return index == stages.size() || runningTime < stages[index].startTime;
    };

    if (IndexIsInactive()) {
      return;
    }

    // Find the next active stage, if we aren't there already
    while (runningTime >= stages[index].endTime) {
      index++;
      if (IndexIsInactive()) {
        return;
      }
    }

    // Update the currently active stage
    stages[index].stageFunction();
  }

  void Reset() { index = 0; }

  void SetStartTime(const tm::Time& newStartTime) { startTime = newStartTime; }

 private:
  std::vector<Stage> stages;
  std::size_t index{};
  tm::Time startTime{};
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_STAGEHANDLER_STAGEHANDLER_HPP_
