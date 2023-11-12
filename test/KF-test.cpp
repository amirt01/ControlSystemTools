//
// Created by amirt on 11/11/2023.
//

#include <gtest/gtest.h>

#include "KalmanFilter.hpp"

template<std::floating_point Tf>
class Constructed : public testing::Test {
 public:
  KalmanFilter<Tf, 3, 3> kf{};
};

using FloatingTypes = testing::Types<float, double, long double>;
TYPED_TEST_SUITE(Constructed, FloatingTypes);

TYPED_TEST(Constructed, DefaultUninitialized) {
  EXPECT_FALSE(TestFixture::kf.GetInitialized());
}

TYPED_TEST(Constructed, UninitializedAccess) {
  EXPECT_DEBUG_DEATH(TestFixture::kf.Update(), "Cannot Update before KF is initialized!");
  EXPECT_DEBUG_DEATH((void) TestFixture::kf.GetState(), "Cannot access state before KF is initialized!");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
