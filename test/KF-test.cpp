//
// Created by amirt on 11/11/2023.
//

#include <gtest/gtest.h>

#include "KalmanFilter.hpp"

using namespace ctr;

template<std::floating_point Tf>
struct Constructed : testing::Test {
  const Tf epsilon{std::numeric_limits<Tf>::epsilon()};
  using TestingType = Tf;

  constexpr static std::size_t Nx{3};
  constexpr static std::size_t Nz{1};
  Tf dt = 1.0 / 30; // Time step

  Eigen::Matrix<Tf, Nx, Nx> F;  // State Transition Matrix
  Eigen::Matrix<Tf, Nz, Nx> H;  // Observation Matrix

  Eigen::Matrix<Tf, Nx, Nx> Q;  // Process Noise Covariance
  Eigen::Matrix<Tf, Nz, Nz> R;  // Measurement Covariance

  Eigen::Matrix<Tf, Nx, Nx> P0;  // Estimate Covariance
  Eigen::Vector<Tf, Nx> x0;     // State Vector

  KF<Nx, Nz, Tf> kf;
  KF<Nx, Nz, Tf> kf2;
  KF<Nx, Nz, Tf> kf3;
  KF<Nx, Nz, Tf> kf4;

  void SetUp() override {
    F.setZero();
    H.setZero();
    Q.setZero();
    R.setZero();
    P0.setZero();
    x0.setZero();

    kf2 = {F, H, Q, R};
    kf3 = {F, H, Q, R, P0, x0};

    // Discrete LTI projectile motion, measuring position only
    F << 1, dt, 0, 0, 1, dt, 0, 0, 1;
    H << 1, 0, 0;

    // Reasonable covariance matrices
    Q << .05, .05, .0,
        .05, .05, .0,
        .0, .0, .0;
    R = Eigen::DiagonalMatrix<Tf, Nz>{5};
    P0 << .1, .1, .1,
        .1, 10000, 10,
        .1, 10, 100;

    kf4.Initialize(F, H, Q, R, P0, {1, 2, -9.81});
  }
};

using FloatingTypes = testing::Types<float, double, long double>;
TYPED_TEST_SUITE(Constructed, FloatingTypes);

TYPED_TEST(Constructed, DefaultUninitialized) {
  EXPECT_FALSE(TestFixture::kf.IsInitialized());
}

TYPED_TEST(Constructed, UnSetUpAccess) {
  EXPECT_FALSE(TestFixture::kf.IsSetUp());
  EXPECT_DEBUG_DEATH(TestFixture::kf.MeasurementUpdate(Eigen::Vector<typename TestFixture::TestingType,
                                                                     TestFixture::Nz>{}),
                     "Cannot Update before KF is set up!");
  EXPECT_DEBUG_DEATH((void) TestFixture::kf.GetEstimate(), "Cannot access state estimate before KF is set up!");
}

TYPED_TEST(Constructed, UninitializedAccess) {
  EXPECT_FALSE(TestFixture::kf2.IsInitialized());
  EXPECT_DEBUG_DEATH(TestFixture::kf2.MeasurementUpdate(Eigen::Vector<typename TestFixture::TestingType,
                                                                      TestFixture::Nz>{}),
                     "Cannot Update before KF is initialized!");
  EXPECT_DEBUG_DEATH((void) TestFixture::kf2.GetEstimate(), "Cannot access state estimate before KF is initialized!");
}

TYPED_TEST(Constructed, ConstructorUninitialized) {
  EXPECT_FALSE(TestFixture::kf2.IsInitialized());
}

TYPED_TEST(Constructed, ConstructorInitialization) {
  EXPECT_TRUE(TestFixture::kf3.IsInitialized());
}

TYPED_TEST(Constructed, ConstructorInitialState) {
  EXPECT_NEAR(TestFixture::kf3.GetEstimate()(0, 0), 0, TestFixture::epsilon);
  EXPECT_NEAR(TestFixture::kf3.GetEstimate()(1, 0), 0, TestFixture::epsilon);
}

TYPED_TEST(Constructed, InitializeConstructed) {
  EXPECT_FALSE(TestFixture::kf2.IsInitialized());
  TestFixture::kf2.Initialize(TestFixture::P0, TestFixture::x0);
  EXPECT_TRUE(TestFixture::kf2.IsInitialized());
  EXPECT_NEAR(TestFixture::kf2.GetEstimate()(0, 0), 0, TestFixture::epsilon);
  EXPECT_NEAR(TestFixture::kf2.GetEstimate()(1, 0), 0, TestFixture::epsilon);
}

TYPED_TEST(Constructed, InitializeNonConstructed) {
  EXPECT_FALSE(TestFixture::kf.IsInitialized());
  TestFixture::kf.Initialize(TestFixture::F, TestFixture::H, TestFixture::Q, TestFixture::R,
                             TestFixture::P0, TestFixture::x0);
  EXPECT_TRUE(TestFixture::kf.IsInitialized());
  EXPECT_NEAR(TestFixture::kf.GetEstimate()(0, 0), 0, TestFixture::epsilon);
  EXPECT_NEAR(TestFixture::kf.GetEstimate()(1, 0), 0, TestFixture::epsilon);
}

TYPED_TEST(Constructed, Demo) {
  // List of noisy position measurements (y)
  const std::vector<typename TestFixture::TestingType> measurements = {
      1.04202710058, 1.10726790452, 1.2913511148, 1.48485250951, 1.72825901034,
      1.74216489744, 2.11672039768, 2.14529225112, 2.16029641405, 2.21269371128,
      0, 2.6682215744, 0, 2.76034056782, 2.88131780617,
      2.88373786518, 2.9448468727, 0, 3.0006601946, 3.12920591669,
      2.858361783, 2.83808170354, 2.68975330958, 2.66533185589, 2.81613499531,
      2.81003612051, 0, 2.69789264832, 2.4342229249, 2.23464791825,
      2.30278776224, 2.02069770395, 1.94393985809, 1.82498398739, 1.52526230354,
      1.86967808173, 1.18073207847, 1.10729605087, 0.916168349913, 0.678547664519,
      0.562381751596, 0.355468474885, -0.155607486619, -0.287198661013, -0.602973173813
  };

  for (const auto measurement : measurements) {
    TestFixture::kf4.TimeUpdate();
    std::cout << ((measurement == 0) ? " " : std::to_string(measurement)) << '\t'
              << ((measurement == 0) ? TestFixture::kf4.GetEstimate() :
    TestFixture::kf4.MeasurementUpdate(Eigen::Vector<typename TestFixture::TestingType, TestFixture::Nz>{
        measurement}).transpose()).x()
        << '\n';
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
