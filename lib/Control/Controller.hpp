//
// Created by amirt on 11/9/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_CONTROL_CONTROLLER_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_CONTROL_CONTROLLER_HPP_

#include <concepts>
#include <functional>

namespace ctr {

template<typename Tx, typename Ty, std::floating_point Tf = double>
class Controller {
 public:
  //! Constructors
  constexpr Controller() = default;

  constexpr Controller(const std::function<Tx()>& input, const Tx min_output, const Tx max_output)
      : source_(input), min_output_(min_output_), max_output_(max_output) {}

  constexpr Controller(const Tx input, const Tx minOutput, const Tx maxOutput)
      : Controller([input]{ return input; }, minOutput, maxOutput) {}

  //! Control Functions
  virtual constexpr Ty Calculate(Tf dt) = 0;

  //! Getters
  [[nodiscard]] constexpr Tx GetTarget() const noexcept { return target_; }
  [[nodiscard]] constexpr Tx GetLastInput() const noexcept { return last_input_; }
  [[nodiscard]] constexpr virtual Ty GetLastOutput() const noexcept { return last_output_; };

  [[nodiscard]] constexpr Tx GetMinOutput() const noexcept { return min_output_; }
  [[nodiscard]] constexpr Tx GetMaxOutput() const noexcept { return max_output_; }

  //! Setters
  constexpr virtual void SetTarget(const Tx new_target) noexcept { target_ = new_target; }
  constexpr void SetSource(const std::function<Tx()>& newInput) noexcept { source_ = newInput; };

  constexpr void SetMinMaxOutput(const Ty newMinOutput, const Ty newMaxOutput) noexcept {
    min_output_ = newMinOutput;
    max_output_ = newMaxOutput;
  }
  constexpr void SetMinOutput(const Ty newMinOutput) noexcept { min_output_ = newMinOutput; }
  constexpr void SetMaxOutput(const Ty newMaxOutput) noexcept { max_output_ = newMaxOutput; }

 protected:
  [[nodiscard]] constexpr Tx GetError() {
    last_input_ = source_();
    return target_ - last_input_;
  }

  Tx target_;

  Tx min_output_;
  Tx max_output_;

  std::function<Tx()> source_;
  Tx last_input_;
  Tx last_output_;

 public:
  Controller(const Controller&) = default;
  Controller(Controller&&) = default;
  Controller& operator=(const Controller&) = default;
  Controller& operator=(Controller&&) = default;
  virtual ~Controller() = default;
};

};

#endif //CONTROLSYSTEMTOOLS_LIBS_CONTROL_CONTROLLER_HPP_
