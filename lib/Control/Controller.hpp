//
// Created by amirt on 11/9/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_CONTROL_CONTROLLER_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_CONTROL_CONTROLLER_HPP_

#include <concepts>
#include <functional>

template<std::floating_point Tf = double>
class Controller {
 public:
  //! Constructors
  constexpr Controller() = default;

  explicit constexpr Controller(const std::function<Tf()>& input)
      : source(input) {}

  explicit constexpr Controller(const Tf input)
      : Controller([input] { return input; }) {}

  constexpr Controller(const std::function<Tf()>& input, const Tf minOutput, const Tf maxOutput)
      : source(input), minOutput(minOutput), maxOutput(maxOutput) {}

  constexpr Controller(const Tf input, const Tf minOutput, const Tf maxOutput)
      : Controller([input]{ return input; }, minOutput, maxOutput) {}

  virtual //! Control Functions
  constexpr Tf Calculate(Tf dt) = 0;

  //! Getters
  [[nodiscard]] constexpr Tf GetTarget() const noexcept { return target; }
  [[nodiscard]] constexpr Tf GetLastInput() const noexcept { return lastInput; }
  [[nodiscard]] constexpr virtual Tf GetLastOutput() const noexcept { return lastOutput; };

  [[nodiscard]] constexpr Tf GetMinOutput() const noexcept { return minOutput; }
  [[nodiscard]] constexpr Tf GetMaxOutput() const noexcept { return maxOutput; }

  //! Setters
  constexpr virtual void SetTarget(const Tf newTarget) noexcept { target = newTarget; }
  constexpr void SetSource(const std::function<Tf()>& newInput) noexcept { source = newInput; };

  constexpr void SetMinMaxOutput(const Tf newMinOutput, const Tf newMaxOutput) noexcept {
    minOutput = newMinOutput;
    maxOutput = newMaxOutput;
  }
  constexpr void SetMinOutput(const Tf newMinOutput) noexcept { minOutput = newMinOutput; }
  constexpr void SetMaxOutput(const Tf newMaxOutput) noexcept { maxOutput = newMaxOutput; }

 protected:
  [[nodiscard]] constexpr Tf GetError() {
    lastInput = source();
    return target - lastInput;
  }

  Tf target;

  Tf minOutput{std::numeric_limits<Tf>::lowest()};
  Tf maxOutput{std::numeric_limits<Tf>::max()};

  std::function<Tf()> source;
  Tf lastInput;
  Tf lastOutput;

 public:
  Controller(const Controller&) = default;
  Controller(Controller&&) = default;
  Controller& operator=(const Controller&) = default;
  Controller& operator=(Controller&&) = default;
  virtual ~Controller() = default;
};

#endif //CONTROLSYSTEMTOOLS_LIBS_CONTROL_CONTROLLER_HPP_
