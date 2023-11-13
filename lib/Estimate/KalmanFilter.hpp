//
// Created by amirt on 11/10/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
#define CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_

#include <concepts>

#include <Eigen/Dense>

template<class DerivedMatrix, class DerivedDiagonal>
auto operator+(const Eigen::MatrixBase<DerivedMatrix>& lhs, Eigen::DiagonalBase<DerivedDiagonal>& rhs);

template<std::floating_point Tf, std::size_t Nx, std::size_t Ny>
class KalmanFilter {
  template<std::size_t N, std::size_t M>
  using Matrix = Eigen::Matrix<Tf, N, M>;

  template<std::size_t N>
  using DiagonalMatrix = Eigen::DiagonalMatrix<Tf, N>;

  template<std::size_t N>
  using Vector = Eigen::Vector<Tf, N>;

 public:
  constexpr KalmanFilter() = default;

  constexpr KalmanFilter(Matrix<Nx, Nx> F, Matrix<Ny, Nx> H, Matrix<Nx, Nx> Q, DiagonalMatrix<Ny> R)
      : F(std::move(F)), H(std::move(H)), Q(std::move(Q)), R(std::move(R)) {}

  constexpr KalmanFilter(const Matrix<Nx, Nx>& F, const Matrix<Ny, Nx>& H, const Matrix<Nx, Nx>& Q,
                         const DiagonalMatrix<Ny>& R, const Matrix<Nx, Nx>& P0, const Vector<Nx>& x0)
      : KalmanFilter(F, H, Q, R) { Initialize(P0, x0); }

  constexpr Vector<Nx> Initialize(Matrix<Nx, Nx> newF, Matrix<Ny, Nx> newH, Matrix<Nx, Nx> newQ,
                                  DiagonalMatrix<Ny> newR, Matrix<Nx, Nx> P0, Vector<Nx> x0) {
    using std::swap;
    swap(F, newF);
    swap(H, newH);
    swap(Q, newQ);
    swap(R, newR);
    return Initialize(P0, x0);
  }

  constexpr Vector<Nx> Initialize(const Matrix<Nx, Nx>& P0, const Vector<Nx>& x0) {
    initialized = true;

    // Predictor Covariance Equation
    P = F * P0 * F.transpose() + Q;

    // Predictor Equation
    return x = F * x0;
  }

  Vector<Nx> Update(const Vector<Ny>& y) {
    assert((void("Cannot Update before KF is initialized!"), initialized));

    // Weight Equation
    P = F * P * F.transpose() + Q;  // P_n,n-1
    K = P * H.transpose() * (H * P * H.transpose() + R).inverse();

    // Correction Equation
    static const auto I = Matrix<Nx, Nx>::Identity();
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
  Matrix<Nx, Nx> F;      // State Transition Matrix
  Matrix<Ny, Nx> H;      // Observation Matrix

  Matrix<Nx, Nx> P;      // Estimate Covariance
  Matrix<Nx, Nx> Q;      // Process Noise Covariance
  DiagonalMatrix<Ny> R;  // Measurement Covariance
  Matrix<Nx, Ny> K;      // Kalman Gain

  Vector<Nx> x;          // State Vector

  bool initialized{};
};

template<class DerivedMatrix, class DerivedDiagonal>
auto operator+(const Eigen::MatrixBase<DerivedMatrix>& lhs, Eigen::DiagonalBase<DerivedDiagonal>& rhs) {
  static_assert(DerivedMatrix::RowsAtCompileTime == DerivedDiagonal::RowsAtCompileTime,
                "Diagonal addition requires same number of rows!");
  static_assert(DerivedMatrix::ColsAtCompileTime == DerivedDiagonal::ColsAtCompileTime,
                "Diagonal addition requires same number of cols!");

  Eigen::Matrix<typename DerivedMatrix::Scalar,
                DerivedMatrix::RowsAtCompileTime,
                DerivedMatrix::ColsAtCompileTime> ret = lhs;
  std::ranges::transform(lhs.diagonal(), rhs.diagonal(), ret.diagonal().begin(), std::plus{});
  return ret;
}

#endif //CONTROLSYSTEMTOOLS_LIBS_ESTIMATE_KALMANFILTER_HPP_
