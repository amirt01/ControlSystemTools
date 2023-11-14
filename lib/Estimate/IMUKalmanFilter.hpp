//
// Created by amirt on 11/13/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_ESTIMATE_IMUKALMANFILTER_HPP_
#define CONTROLSYSTEMTOOLS_LIB_ESTIMATE_IMUKALMANFILTER_HPP_

#include "KalmanFilter.hpp"

template<std::floating_point Tf>
class IMUKalmanFilter : public KalmanFilter<Tf, 9, 6> {
  static constexpr std::size_t Nx{9};
  static constexpr std::size_t Ny{6};

  template<std::size_t N, std::size_t M = N>
  using Matrix = Eigen::Matrix<Tf, N, M>;

  template<std::size_t N>
  using Vector = Eigen::Vector<Tf, N>;

 private:
};

#endif //CONTROLSYSTEMTOOLS_LIB_ESTIMATE_IMUKALMANFILTER_HPP_
