//
// Created by amirt on 11/24/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_CONTROL_STATEFEEDBACK_HPP_
#define CONTROLSYSTEMTOOLS_LIB_CONTROL_STATEFEEDBACK_HPP_

#include <Eigen/Dense>

#include "Controller.hpp"
#include "Model.hpp"

namespace ctr {

template<std::size_t Nx, std::size_t Nu, std::size_t Ny = Nx, std::floating_point Tf = double>
class StateFeedback : public Controller<Eigen::Vector<Tf, Nx>, Tf> {
  typedef Eigen::Vector<Tf, Nx> StateVector;
  typedef Eigen::Vector<Tf, Ny> ControlVector;

 public:
  StateFeedback() = default;

  constexpr StateFeedback(const std::function<StateVector()>& input,
                          const StateVector& minOutput,
                          const StateVector& maxOutput)
      : Controller<StateVector, Tf>(input, minOutput, maxOutput) {}

  ControlVector Calculate(Tf dt) override {
    return std::clamp(-K * this->source(), this->minOutput, this->maxOutput);
  }

 private:
  Eigen::Vector<Tf, Nx> K;
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_CONTROL_STATEFEEDBACK_HPP_
