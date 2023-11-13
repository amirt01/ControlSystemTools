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
      : mSource(input) {}

  explicit constexpr Controller(const Tf input)
      : Controller([input] { return input; }) {}

  constexpr Controller(const std::function<Tf()>& input, const Tf min, const Tf max)
      : mSource(input), mMin(min), mMax(max) {}

  constexpr Controller(const Tf input, const Tf min, const Tf max)
      : Controller([input]{ return input; }, min, max) {}

  virtual //! Control Functions
  constexpr Tf Calculate(Tf dt) = 0;

  //! Getters
  [[nodiscard]] constexpr Tf GetTarget() const noexcept { return mTarget; }
  [[nodiscard]] constexpr Tf GetLastInput() const noexcept { return mLastInput; }
  [[nodiscard]] constexpr virtual Tf GetLastOutput() const noexcept { return mLastOutput; };

  [[nodiscard]] constexpr Tf GetMin() const noexcept { return mMin; }
  [[nodiscard]] constexpr Tf GetMax() const noexcept { return mMax; }

  //! Setters
  constexpr virtual void SetTarget(const Tf newTarget) noexcept { mTarget = newTarget; }
  constexpr void SetSource(const std::function<Tf()>& newInput) noexcept { mSource = newInput; };

  constexpr void SetMinMax(const Tf min, const Tf max) noexcept {
    mMin = min;
    mMax = max;
  }
  constexpr void SetMin(const Tf min) noexcept { mMin = min; }
  constexpr void SetMax(const Tf max) noexcept { mMax = max; }

 protected:
  [[nodiscard]] constexpr Tf GetError() {
    mLastInput = mSource();
    return mTarget - mLastInput;
  }

  Tf mTarget;

  Tf mMin{std::numeric_limits<Tf>::lowest()};
  Tf mMax{std::numeric_limits<Tf>::max()};

  std::function<Tf()> mSource;
  Tf mLastInput;
  Tf mLastOutput;

 public:
  Controller(const Controller&) = default;
  Controller(Controller&&) = default;
  Controller& operator=(const Controller&) = default;
  Controller& operator=(Controller&&) = default;
  virtual ~Controller() = default;
};

#endif //CONTROLSYSTEMTOOLS_LIBS_CONTROL_CONTROLLER_HPP_
