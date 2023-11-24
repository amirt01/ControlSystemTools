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
      : Kp(Kp), Ki(Ki), Kd(Kd) {}

  constexpr PID(Tf Kp, Tf Ki, Tf Kd, const std::function<Tf()>& input)
      : Kp(Kp), Ki(Ki), Kd(Kd), Controller<Tf>(input) {}

  constexpr PID(Tf Kp, Tf Ki, Tf Kd, Tf input)
      : Kp(Kp), Ki(Ki), Kd(Kd), Controller<Tf>(input) {}

  //! Control Functions
  constexpr Tf Calculate(Tf dt) override {
    const auto error = this->GetError();

    const auto proportional = Kp * error;

    integralSum += Ki * error * dt;
    integralSum = std::clamp(integralSum, -integralSaturation, integralSaturation);

    const auto derivative = Kd * (error - lastError) / dt;
    lastError = error;

    const auto PIDSum = proportional + integralSum + derivative;
    this->lastOutput = std::clamp(PIDSum, this->minOutput, this->maxOutput);

    return this->lastOutput;
  }

  //! Setters
  constexpr void SetTarget(const Tf newTarget) noexcept override {
    integralSum = {};
    this->target = newTarget;
  }

  constexpr void SetK(const Tf newKp, const Tf newKi, const Tf newKd) noexcept {
    Kp = newKp;
    Ki = newKi;
    Kd = newKd;
  }
  constexpr void SetKp(const Tf newKp) noexcept { Kp = newKp; }
  constexpr void SetKi(const Tf newKi) noexcept { Ki = newKi; }
  constexpr void SetKd(const Tf newKd) noexcept { Kd = newKd; }

  constexpr void SetIntegralSaturation(const Tf newIntegralSaturation) noexcept {
    integralSaturation = newIntegralSaturation;
  }

  //! Getters
  [[nodiscard]] constexpr Tf GetKp() const noexcept { return Kp; }
  [[nodiscard]] constexpr Tf GetKi() const noexcept { return Ki; }
  [[nodiscard]] constexpr Tf GetKd() const noexcept { return Kd; }

  [[nodiscard]] constexpr Tf GetISaturation() const noexcept { return integralSaturation; }

 private:
  Tf integralSaturation{std::numeric_limits<Tf>::max()};

  Tf Kp, Ki, Kd;

  Tf integralSum;

  Tf lastError;
};

#endif //CONTROLSYSTEMTOOLS_LIBS_CONTROL_PID_HPP_
