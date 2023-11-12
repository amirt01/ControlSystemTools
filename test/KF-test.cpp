//
// Created by amirt on 11/11/2023.
//

#include <gtest/gtest.h>

#include "KalmanFilter.hpp"

template<std::floating_point Tf>
class Constructed : public testing::Test {
 private:
  constexpr static std::size_t Nx{2};
  constexpr static std::size_t Nz{2};

  Eigen::Matrix<Tf, Nx, Nx> A;  // State Transition Matrix
  Eigen::Matrix<Tf, Nz, Nx> C;  // Observation Matrix

  Eigen::Matrix<Tf, Nx, Nx> P;  // Estimate Covariance
  Eigen::Matrix<Tf, Nx, Nx> Q;  // Process Noise Covariance
  Eigen::Matrix<Tf, Nz, Nz> R;  // Measurement Covariance
  Eigen::Matrix<Tf, Nx, Nz> K;  // Kalman Gain

  Eigen::Vector<Tf, Nx> x;     // State Vector

 public:
  using T = Tf;

  KalmanFilter<Tf, 3, 3> kf{};
  KalmanFilter<Tf, 2, 2> kf2{A, C, Q, R, K};
  KalmanFilter<Tf, 2, 2> kf3{A, C, Q, R, K, P, x};
};

using FloatingTypes = testing::Types<float, double, long double>;
TYPED_TEST_SUITE(Constructed, FloatingTypes);

TYPED_TEST(Constructed, DefaultUninitialized) {
  EXPECT_FALSE(TestFixture::kf.GetInitialized());
}

TYPED_TEST(Constructed, UninitializedAccess) {
  EXPECT_FALSE(TestFixture::kf.GetInitialized());
  EXPECT_DEBUG_DEATH(TestFixture::kf.Update(), "Cannot Update before KF is initialized!");
  EXPECT_DEBUG_DEATH((void) TestFixture::kf.GetState(), "Cannot access state before KF is initialized!");
}

TYPED_TEST(Constructed, ConstructorUninitialized) {
  EXPECT_FALSE(TestFixture::kf2.GetInitialized());
}

TYPED_TEST(Constructed, ConstructorInitialization) {
  EXPECT_TRUE(TestFixture::kf3.GetInitialized());
}

TYPED_TEST(Constructed, ConstructorInitialState) {
  EXPECT_NEAR(TestFixture::kf3.GetState()(0, 0), 0, std::numeric_limits<typename TestFixture::T>::epsilon());
  EXPECT_NEAR(TestFixture::kf3.GetState()(1, 0), 0, std::numeric_limits<typename TestFixture::T>::epsilon());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
