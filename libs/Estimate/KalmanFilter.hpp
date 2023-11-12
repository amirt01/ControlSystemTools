//
// Created by amirt on 11/10/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_

#include <concepts>

#include <Eigen/Dense>

template<std::floating_point Tf, std::size_t Nx, std::size_t Nz>
class KalmanFilter {
 public:
  constexpr KalmanFilter() = default;

  constexpr KalmanFilter(Eigen::Matrix<Tf, Nx, Nx> A, Eigen::Matrix<Tf, Nz, Nx> C,
                         Eigen::Matrix<Tf, Nx, Nx> Q, Eigen::Matrix<Tf, Nz, Nz> R, Eigen::Matrix<Tf, Nx, Nz> K)
      : A(std::move(A)), C(std::move(C)),
        Q(std::move(Q)), R(std::move(R)), K(std::move(K)) {}

  constexpr KalmanFilter(const Eigen::Matrix<Tf, Nx, Nx>& A, const Eigen::Matrix<Tf, Nz, Nx>& C,
                         const Eigen::Matrix<Tf, Nx, Nx>& Q, const Eigen::Matrix<Tf, Nz, Nz>& R,
                         const Eigen::Matrix<Tf, Nx, Nz>& K,
                         const Eigen::Matrix<Tf, Nx, Nx>& P0, const Eigen::Vector<Tf, Nx>& x0)
      : KalmanFilter(A, C, Q, R, K) { Initialize(P0, x0); }

  constexpr Eigen::Vector<Tf, Nx> Initialize(const Eigen::Matrix<Tf, Nx, Nx>& P0, const Eigen::Vector<Tf, Nx>& x0) {
    initialized = true;

    // Predictor Covariance Equation
    P = A * P0 * A.transpose() + Q;

    // Predictor Equation
    return x = A * x0;
  }

  Eigen::Vector<Tf, Nx> Update() {
    assert((void("Cannot Update before KF is initialized!"), initialized));

    // Weight Equation
    K = P * C.transpose() * (C * P * C.transpose() + R).inverse();

    // Correction Equation
    const static auto I = Eigen::Matrix<Tf, Nx, Nx>::Identity();
    const auto correction = I - K * C;
    P = correction * P * correction.transpose() + K * R * K.transpose();

    // Measurement Equation
    const auto z = C * x;

    // Filtering Equation
    return x += K * (z - C * x);
  }

  [[nodiscard]] constexpr auto GetInitialized() noexcept { return initialized; }

  [[nodiscard]] constexpr auto GetState() {
    assert((void("Cannot access state before KF is initialized!"), initialized));
    return x;
  }

 private:
  Eigen::Matrix<Tf, Nx, Nx> A;  // State Transition Matrix
  Eigen::Matrix<Tf, Nz, Nx> C;  // Observation Matrix

  Eigen::Matrix<Tf, Nx, Nx> P;  // Estimate Covariance
  Eigen::Matrix<Tf, Nx, Nx> Q;  // Process Noise Covariance
  Eigen::Matrix<Tf, Nz, Nz> R;  // Measurement Covariance
  Eigen::Matrix<Tf, Nx, Nz> K;  // Kalman Gain

  Eigen::Vector<Tf, Nx> x;     // State Vector

  bool initialized{};
};

#endif //CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
