//
// Created by amirt on 11/10/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_CONTROL_LQR_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_CONTROL_LQR_HPP_

#include <Eigen/Dense>

#include "Controller.hpp"

template<std::floating_point Tf, std::size_t N>
class LQR : public Controller<Tf> {
 public:
  LQR() = default;

  LQR(Tf A, Tf B, Tf Q, Tf R) {

  }

 private:
  Eigen::Matrix<Tf, N, N> X;
  Eigen::Matrix<Tf, N, 1> K;
};

#endif //CONTROLSYSTEMTOOLS_LIBS_CONTROL_LQR_HPP_
