//
// Created by amirt on 11/30/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_CONTROL_MODEL_HPP_
#define CONTROLSYSTEMTOOLS_LIB_CONTROL_MODEL_HPP_

#include <Eigen/Dense>

template<std::size_t Nx, std::size_t Nu, std::size_t Ny = Nx, std::floating_point Tf = double>
struct Model {
  Eigen::Matrix<Tf, Nx, Nx> A;
  Eigen::Matrix<Tf, Nx, Nu> B;
  Eigen::Matrix<Tf, Ny, Nx> C;
  Eigen::Matrix<Tf, Ny, Nu> D;
};

#endif //CONTROLSYSTEMTOOLS_LIB_CONTROL_MODEL_HPP_
