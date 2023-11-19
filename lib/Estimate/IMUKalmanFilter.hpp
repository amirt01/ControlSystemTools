//
// Created by amirt on 11/13/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_ESTIMATE_IMUKALMANFILTER_HPP_
#define CONTROLSYSTEMTOOLS_LIB_ESTIMATE_IMUKALMANFILTER_HPP_

#include <numbers>

#include "KalmanFilter.hpp"

namespace cst {

template<std::floating_point Tf, std::size_t N_DIMS = 3>
class IMUKalmanFilter : KalmanFilter<Tf, N_DIMS * 3, N_DIMS * 2> {
  enum class I {  // Matrix Indices
    POS = 0,
    VEL = POS + N_DIMS,
    ATT = VEL + N_DIMS,
    ACCEL = VEL,
    GYRO = ATT
  };

  template<std::size_t N, std::size_t M = N>
  using Matrix = Eigen::Matrix<Tf, N, M>;

  template<std::size_t N>
  using Vector = Eigen::Vector<Tf, N>;

 public:
  constexpr IMUKalmanFilter() = default;
  constexpr explicit IMUKalmanFilter(const Tf dt) { SetUp(dt); }

  constexpr void SetUp(const Tf dt) noexcept {
    // Link states to themselves and Position to the derivative of Velocity
    this->F.setIdentity();
    this->F.diagonal(I::VEL).segment<N_DIMS>(I::POS).setConstant(dt);
    this->F.block<3, 3>(I::ATT);

    // Link Velocity and Attitude to the derivative of Accelerometer and RateGyro measurements
    this->H.diagonal(I::VEL).setConstant(dt);

    // Set the measurement covariance based on the Accelerometer and Gyroscope hardware
    this->R.diagonal().segment<N_DIMS>(I::ACCEL).setConstant(5);
    this->R.diagonal().segment<N_DIMS>(I::GYRO).setConstant(0.1);
  }

  constexpr void Initialize() noexcept {
    static constexpr Tf initStdDevAtt_perpToGravity{10 * std::numbers::pi_v<Tf> / 180};  //[rad]
    static constexpr Tf initStdDevAtt_aboutGravity{30 * std::numbers::pi_v<Tf> / 180};   //[rad]

    this->P.diagonal().segment<N_DIMS>(I::POS).setConstant(3);
    this->P.diagonal().segment<N_DIMS>(I::VEL).setConstant(3);
    this->P.diagonal().segment<N_DIMS>(I::ATT)
        << std::pow(initStdDevAtt_perpToGravity, 2.f),
        std::pow(initStdDevAtt_perpToGravity, 2.f),
        std::pow(initStdDevAtt_aboutGravity, 2.f);
  }
};

template<std::floating_point Tf, std::size_t N_DIMS = 3>
using IMUKF = IMUKalmanFilter<Tf, N_DIMS>;

}  // namespace cst

#endif //CONTROLSYSTEMTOOLS_LIB_ESTIMATE_IMUKALMANFILTER_HPP_
