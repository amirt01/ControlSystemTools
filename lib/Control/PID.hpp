//
// Created by amirt on 11/9/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_CONTROL_PID_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_CONTROL_PID_HPP_

#include <algorithm>

#include "Controller.hpp"

namespace ctr {

template<std::floating_point Tf = double>
class PID : public Controller<Tf, Tf, Tf> {
 public:
  //! Constructors
  constexpr PID() = default;

  constexpr PID(Tf Kp, Tf Ki, Tf Kd)
      : Kp(Kp), Ki(Ki), Kd(Kd) {}

  constexpr PID(Tf Kp, Tf Ki, Tf Kd, const std::function<Tf()>& input)
      : Kp(Kp), Ki(Ki), Kd(Kd), Controller<Tf, Tf, Tf>(input) {}

  constexpr PID(Tf Kp, Tf Ki, Tf Kd, Tf input)
      : Kp(Kp), Ki(Ki), Kd(Kd), Controller<Tf, Tf, Tf>(input) {}

  //! Control Functions
  constexpr Tf Calculate(Tf dt) override {
    const auto error = this->GetError();

    const auto proportional = Kp * error;
    integral_sum_ = std::clamp(integral_sum_ + Ki * error * dt, -integral_saturation_, integral_saturation_);
    const auto derivative = Kd * (error - last_error_) / dt;

    last_error_ = error;
    return this->lastOutput = std::clamp(proportional + integral_sum_ + derivative, this->minOutput, this->maxOutput);
  }

  //! Setters
  constexpr void SetTarget(const Tf newTarget) noexcept override {
    integral_sum_ = {};
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

  constexpr void SetIntegralSaturation(const Tf integral_saturation) noexcept {
    integral_saturation_ = integral_saturation;
  }

  //! Getters
  [[nodiscard]] constexpr Tf GetKp() const noexcept { return Kp; }
  [[nodiscard]] constexpr Tf GetKi() const noexcept { return Ki; }
  [[nodiscard]] constexpr Tf GetKd() const noexcept { return Kd; }

  [[nodiscard]] constexpr Tf GetISaturation() const noexcept { return integral_saturation_; }

 private:
  Tf integral_saturation_{std::numeric_limits<Tf>::max()};

  Tf Kp, Ki, Kd;

  Tf integral_sum_;

  Tf last_error_;
};

}

#endif //CONTROLSYSTEMTOOLS_LIBS_CONTROL_PID_HPP_
