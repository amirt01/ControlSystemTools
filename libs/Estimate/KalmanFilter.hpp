//
// Created by amirt on 11/10/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_

#include <concepts>

#include <Eigen/Dense>

template<std::floating_point Tf, std::size_t Nx, std::size_t Ny>
class KalmanFilter {
 public:
  constexpr KalmanFilter() = default;

  constexpr KalmanFilter(Eigen::Matrix<Tf, Nx, Nx> A, Eigen::Matrix<Tf, Ny, Nx> C,
                         Eigen::Matrix<Tf, Nx, Nx> Q, Eigen::Matrix<Tf, Ny, Ny> R)
      : A(std::move(A)), C(std::move(C)),
        Q(std::move(Q)), R(std::move(R)) {}

  constexpr KalmanFilter(const Eigen::Matrix<Tf, Nx, Nx>& A, const Eigen::Matrix<Tf, Ny, Nx>& C,
                         const Eigen::Matrix<Tf, Nx, Nx>& Q, const Eigen::Matrix<Tf, Ny, Ny>& R,
                         const Eigen::Matrix<Tf, Nx, Nx>& P0, const Eigen::Vector<Tf, Nx>& x0)
      : KalmanFilter(A, C, Q, R) { Initialize(P0, x0); }

  constexpr Eigen::Vector<Tf, Nx> Initialize(Eigen::Matrix<Tf, Nx, Nx> newA, Eigen::Matrix<Tf, Ny, Nx> newC,
                                             Eigen::Matrix<Tf, Nx, Nx> newQ, Eigen::Matrix<Tf, Ny, Ny> newR,
                                             Eigen::Matrix<Tf, Nx, Nx> P0, Eigen::Vector<Tf, Nx> x0) {
    using std::swap;
    swap(A, newA);
    swap(C, newC);
    swap(Q, newQ);
    swap(R, newR);
    return Initialize(P0, x0);
  }

  constexpr Eigen::Vector<Tf, Nx> Initialize(const Eigen::Matrix<Tf, Nx, Nx>& P0, const Eigen::Vector<Tf, Nx>& x0) {
    initialized = true;

    // Predictor Covariance Equation
    P = A * P0 * A.transpose() + Q;

    // Predictor Equation
    return x = A * x0;
  }

  Eigen::Vector<Tf, Nx> Update(const Eigen::Vector<Tf, Ny>& y) {
    assert((void("Cannot Update before KF is initialized!"), initialized));

    // Weight Equation
    P = A * P * A.transpose() + Q;  // P_n,n-1
    K = P * C.transpose() * (C * P * C.transpose() + R).inverse();

    // Correction Equation
    static const auto I = Eigen::Matrix<Tf, Nx, Nx>::Identity();
    const auto correction = I - K * C;
    P = correction * P * correction.transpose() + K * R * K.transpose();  // P_n+1,n
    // P = (I - K * C) * P  //! numerically unstable simplification

    // Filtering Equation
    x = A * x;
    return x += K * (y - C * x);
  }

  [[nodiscard]] constexpr auto GetInitialized() noexcept { return initialized; }

  [[nodiscard]] constexpr auto GetState() {
    assert((void("Cannot access state before KF is initialized!"), initialized));
    return x;
  }

 private:
  Eigen::Matrix<Tf, Nx, Nx> A;  // State Transition Matrix
  Eigen::Matrix<Tf, Ny, Nx> C;  // Observation Matrix

  Eigen::Matrix<Tf, Nx, Nx> P;  // Estimate Covariance
  Eigen::Matrix<Tf, Nx, Nx> Q;  // Process Noise Covariance
  Eigen::Matrix<Tf, Ny, Ny> R;  // Measurement Covariance
  Eigen::Matrix<Tf, Nx, Ny> K;  // Kalman Gain

  Eigen::Vector<Tf, Nx> x;     // State Vector

  bool initialized{};
};

#endif //CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
