//
// Created by amirt on 11/13/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_ESTIMATE_IMUKALMANFILTER_HPP_
#define CONTROLSYSTEMTOOLS_LIB_ESTIMATE_IMUKALMANFILTER_HPP_

#include "KalmanFilter.hpp"

template<std::floating_point Tf>
class IMUKalmanFilter {
  static constexpr Tf Nx{9};
  static constexpr Tf Nz{6};

 public:


 private:
    KalmanFilter<Tf, Nx, Nz> kf;
};

#endif //CONTROLSYSTEMTOOLS_LIB_ESTIMATE_IMUKALMANFILTER_HPP_
