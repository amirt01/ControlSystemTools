//
// Created by amirt on 11/10/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_

#include <concepts>

#include <Eigen/Dense>

template<std::floating_point Tf, std::size_t Nx, std::size_t Ny>
class KalmanFilter {
  template<std::size_t N, std::size_t M = N>
  using Matrix = Eigen::Matrix<Tf, N, M>;

  template<std::size_t N>
  using Vector = Eigen::Vector<Tf, N>;

 public:
  constexpr KalmanFilter() = default;

  constexpr KalmanFilter(Matrix<Nx> F, Matrix<Ny, Nx> H, Matrix<Nx> Q, Matrix<Ny> R)
      : F(std::move(F)), H(std::move(H)), Q(std::move(Q)), R(std::move(R)) {}

  constexpr KalmanFilter(const Matrix<Nx>& F, const Matrix<Ny, Nx>& H, const Matrix<Nx>& Q,
                         const Matrix<Ny>& R, const Matrix<Nx>& P0, const Vector<Nx>& x0)
      : KalmanFilter(F, H, Q, R) { Initialize(P0, x0); }

  constexpr void SetUp(Matrix<Nx> newF, Matrix<Ny, Nx> newH, Matrix<Nx> newQ, Matrix<Ny> newR) {
    using std::swap;
    swap(F, newF);
    swap(H, newH);
    swap(Q, newQ);
    swap(R, newR);
  }

  constexpr Vector<Nx> Initialize(const Matrix<Nx>& P0, const Vector<Nx>& x0) {
    initialized = true;

    // Predictor Covariance Equation
    P = F * P0 * F.transpose() + Q;

    // Predictor Equation
    return x = F * x0;
  }

  constexpr Vector<Nx> Initialize(const Matrix<Nx>& newF, const Matrix<Ny, Nx>& newH, const Matrix<Nx>& newQ,
                                  const Matrix<Ny>& newR, const Matrix<Nx>& P0, const Vector<Nx>& x0) {
    SetUp(newF, newH, newQ, newR);
    return Initialize(P0, x0);
  }

  Vector<Nx> Update(const Vector<Ny>& y) {
    assert((void("Cannot Update before KF is initialized!"), initialized));

    // Weight Equation
    P = F * P * F.transpose() + Q;  // P_n,n-1
    K = P * H.transpose() * (H * P * H.transpose() + R).inverse();

    // Correction Equation
    static const auto I = Matrix<Nx>::Identity();
    const auto correction = I - K * H;
    P = correction * P * correction.transpose() + K * R * K.transpose();  // P_n+1,n
    // P = (I - K * C) * P  //! numerically unstable simplification

    // Filtering Equation
    x = F * x;
    return x += K * (y - H * x);
  }

  [[nodiscard]] constexpr bool GetInitialized() noexcept { return initialized; }

  [[nodiscard]] constexpr Vector<Nx> GetState() {
    assert((void("Cannot access state before KF is initialized!"), initialized));
    return x;
  }

 private:
  Matrix<Nx> F;      // State Transition Matrix
  Matrix<Ny, Nx> H;      // Observation Matrix

  Matrix<Nx> P;      // Estimate Covariance
  Matrix<Nx> Q;      // Process Noise Covariance
  Matrix<Ny> R;  // Measurement Covariance
  Matrix<Nx, Ny> K;      // Kalman Gain

  Vector<Nx> x;          // State Vector

  bool initialized{};
};

#endif //CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
