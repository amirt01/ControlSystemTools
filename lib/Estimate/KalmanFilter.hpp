//
// Created by amirt on 11/10/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_

#include <concepts>

#include <Eigen/Dense>

namespace cst {

template<std::floating_point Tf, std::size_t Nx, size_t Nz = Nx>
class KalmanFilter {
  static_assert(Nx != 0, "You must have at least one state!");
  static_assert(Nx >= Nz, "The number of states must be >= the number of inputs!");

  template<std::size_t N, std::size_t M = N>
  using Matrix = Eigen::Matrix<Tf, N, M>;

  template<std::size_t N>
  using Vector = Eigen::Vector<Tf, N>;

  // Predictor Covariance Equation
  [[nodiscard]] Matrix<Nx> CovarianceExtrapolation(const Matrix<Nx>& Pn) noexcept {
    return F * Pn * F.transpose() + Q;
  }

  // Predictor Equation
  [[nodiscard]] Vector<Nx> StateExtrapolation(const Vector<Nx>& xn) noexcept {
    return F * xn;
  }

 public:
  constexpr KalmanFilter() = default;

  constexpr KalmanFilter(Matrix<Nx> F, Matrix<Nz, Nx> H, Matrix<Nx> Q, Matrix<Nz> R)
      : F(std::move(F)), H(std::move(H)), Q(std::move(Q)), R(std::move(R)), setUp(true) {}

  constexpr KalmanFilter(const Matrix<Nx>& F, const Matrix<Nz, Nx>& H, const Matrix<Nx>& Q,
                         const Matrix<Nz>& R, const Matrix<Nx>& P0, const Vector<Nx>& x0)
      : KalmanFilter(F, H, Q, R) { static_cast<void>(Initialize(P0, x0)); }

  constexpr void SetUp(Matrix<Nx> newF, Matrix<Nz, Nx> newH, Matrix<Nx> newQ, Matrix<Nz> newR) noexcept {
    using std::swap;
    swap(F, newF);
    swap(H, newH);
    swap(Q, newQ);
    swap(R, newR);
    initialized = false;
    setUp = true;
  }

  constexpr void Initialize(const Matrix<Nx>& P0, const Vector<Nx>& x0) {
    assert((void("Cannot Initialize before KF is set up!"), setUp));

    P = P0;
    x = x0;
    initialized = true;
  }

  constexpr void Initialize(const Matrix<Nx>& newF, const Matrix<Nz, Nx>& newH, const Matrix<Nx>& newQ,
                            const Matrix<Nz>& newR, const Matrix<Nx>& P0, const Vector<Nx>& x0) {
    SetUp(newF, newH, newQ, newR);
    Initialize(P0, x0);
  }

  Vector<Nx> TimeUpdate() {
    assert((void("Cannot Update before KF is set up!"), setUp));
    assert((void("Cannot Update before KF is initialized!"), initialized));

    x = StateExtrapolation(x);
    P = CovarianceExtrapolation(P);

    return x;
  }

  Vector<Nx> MeasurementUpdate(const Vector<Nz>& z) {
    assert((void("Cannot Update before KF is set up!"), setUp));
    assert((void("Cannot Update before KF is initialized!"), initialized));

    // Weight Equation
    K = P * H.transpose() * (H * P * H.transpose() + R).inverse();

    // Correction Equation
    static const auto I = Matrix<Nx>::Identity();
    P = (I - K * H) * P * (I - K * H).transpose() + K * R * K.transpose();
    // P = (I - K * H) * P  //! numerically unstable simplification

    // Filtering Equation
    return x += K * (z - H * x);
  }

  [[nodiscard]] constexpr bool IsInitialized() noexcept { return initialized; }
  [[nodiscard]] constexpr bool IsSetUp() noexcept { return setUp; }

  [[nodiscard]] constexpr Vector<Nx> GetEstimate() {
    assert((void("Cannot access state estimate before KF is set up!"), setUp));
    assert((void("Cannot access state estimate before KF is initialized!"), initialized));
    return x;
  }

 protected:
  Matrix<Nx> F;      // State Transition Matrix
  Matrix<Nz, Nx> H;  // Observation Matrix

  Matrix<Nx> P;      // Estimate Covariance
  Matrix<Nx> Q;      // Process Noise Covariance
  Matrix<Nz> R;      // Measurement Covariance
  Matrix<Nx, Nz> K;  // Kalman Gain

  Vector<Nx> x;      // State Vector

  bool setUp{};
  bool initialized{};
};

template<std::floating_point Tf, std::size_t Nx, size_t Nz = Nx>
using KF = KalmanFilter<Tf, Nx, Nz>;

}  // namespace cst

#endif //CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
