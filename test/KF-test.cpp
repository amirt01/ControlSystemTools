//
// Created by amirt on 11/11/2023.
//

#include <gtest/gtest.h>

#include "KalmanFilter.hpp"

template<std::floating_point Tf>
struct Constructed : testing::Test {
  const Tf epsilon{std::numeric_limits<Tf>::epsilon()};

  constexpr static std::size_t Nx{2};
  constexpr static std::size_t Nz{2};

  Eigen::Matrix<Tf, Nx, Nx> A;  // State Transition Matrix
  Eigen::Matrix<Tf, Nz, Nx> C;  // Observation Matrix

  Eigen::Matrix<Tf, Nx, Nx> Q;  // Process Noise Covariance
  Eigen::Matrix<Tf, Nz, Nz> R;  // Measurement Covariance
  Eigen::Matrix<Tf, Nx, Nz> K;  // Kalman Gain

  Eigen::Matrix<Tf, Nx, Nx> P0;  // Estimate Covariance
  Eigen::Vector<Tf, Nx> x0;     // State Vector

  KalmanFilter<Tf, 2, 2> kf{};
  KalmanFilter<Tf, 2, 2> kf2;
  KalmanFilter<Tf, 2, 2> kf3;

  void SetUp() override {
    A.setZero();
    C.setZero();
    Q.setZero();
    R.setZero();
    K.setZero();
    P0.setZero();
    x0.setZero();

    kf2 = {A, C, Q, R, K};
    kf3 = {A, C, Q, R, K, P0, x0};
  }
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
  EXPECT_NEAR(TestFixture::kf3.GetState()(0, 0), 0, TestFixture::epsilon);
  EXPECT_NEAR(TestFixture::kf3.GetState()(1, 0), 0, TestFixture::epsilon);
}

TYPED_TEST(Constructed, InitializeConstructed) {
  EXPECT_FALSE(TestFixture::kf2.GetInitialized());
  TestFixture::kf2.Initialize(TestFixture::P0, TestFixture::x0);
  EXPECT_TRUE(TestFixture::kf2.GetInitialized());
  EXPECT_NEAR(TestFixture::kf2.GetState()(0, 0), 0, TestFixture::epsilon);
  EXPECT_NEAR(TestFixture::kf2.GetState()(1, 0), 0, TestFixture::epsilon);
}

TYPED_TEST(Constructed, InitializeNonConstructed) {
  EXPECT_FALSE(TestFixture::kf.GetInitialized());
  TestFixture::kf.Initialize(TestFixture::A, TestFixture::C, TestFixture::Q, TestFixture::R, TestFixture::K,
                              TestFixture::P0, TestFixture::x0);
  EXPECT_TRUE(TestFixture::kf.GetInitialized());
  EXPECT_NEAR(TestFixture::kf.GetState()(0, 0), 0, TestFixture::epsilon);
  EXPECT_NEAR(TestFixture::kf.GetState()(1, 0), 0, TestFixture::epsilon);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
