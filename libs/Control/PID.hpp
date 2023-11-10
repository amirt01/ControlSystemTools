//
// Created by amirt on 11/9/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_CONTROL_PID_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_CONTROL_PID_HPP_

#include <algorithm>

#include "Controller.hpp"

template<std::floating_point Tf = double>
class PID : public Controller<Tf> {
 public:
  //! Constructors
  constexpr PID() = default;

  constexpr PID(Tf Kp, Tf Ki, Tf Kd)
      : mKp(Kp), mKi(Ki), mKd(Kd) {}

  constexpr PID(Tf Kp, Tf Ki, Tf Kd, std::reference_wrapper<Tf> input)
      : mKp(Kp), mKi(Ki), mKd(Kd), Controller<Tf>(input) {}

  constexpr PID(Tf Kp, Tf Ki, Tf Kd, Tf input)
      : mKp(Kp), mKi(Ki), mKd(Kd), Controller<Tf>(input) {}

  //! Control Functions
  constexpr Tf Calculate(Tf dt) override {
    const auto error = this->GetError();

    const auto proportional = mKp * error;

    mIntegralSum += mKi * error * dt;
    mIntegralSum = std::clamp(mIntegralSum, -mIntegralSaturation, mIntegralSaturation);

    const auto derivative = mKd * (error - mLastError) / dt;
    mLastError = error;

    this->mLastOutput = proportional + mIntegralSum + derivative;

    return this->mLastOutput;
  }

  //! Setters
  constexpr void SetTarget(const Tf target) noexcept override {
    mIntegralSum = {};
    Controller<Tf>::SetTarget(target);
  }

  constexpr void SetK(const Tf Kp, const Tf Ki, const Tf Kd) noexcept {
    mKp = Kp;
    mKi = Ki;
    mKd = Kd;
  }
  constexpr void SetKp(const Tf Kp) noexcept { mKp = Kp; }
  constexpr void SetKi(const Tf Ki) noexcept { mKi = Ki; }
  constexpr void SetKd(const Tf Kd) noexcept { mKd = Kd; }

  constexpr void SetIntegralSaturation(const Tf integralSaturation) noexcept {
    mIntegralSaturation = integralSaturation;
  }

  //! Getters
  [[nodiscard]] constexpr Tf GetKp() const noexcept { return mKp; }
  [[nodiscard]] constexpr Tf GetKi() const noexcept { return mKi; }
  [[nodiscard]] constexpr Tf GetKd() const noexcept { return mKd; }

  [[nodiscard]] constexpr Tf GetISaturation() const noexcept { return mIntegralSaturation; }

 private:
  Tf mIntegralSaturation{std::numeric_limits<Tf>::max()};

  Tf mKp, mKi, mKd;

  Tf mIntegralSum;

  Tf mLastError;
};

#endif //CONTROLSYSTEMTOOLS_LIBS_CONTROL_PID_HPP_
