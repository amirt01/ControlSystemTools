//
// Created by amirt on 11/9/2023.
//

#include <gtest/gtest.h>

#include "PID.hpp"

template<std::floating_point Tf>
class Constructed : public testing::Test {
 public:
  PID<> pid{};
  PID<> pidVals{1, 2, 3};

};

using FloatingTypes = testing::Types<float, double, long double>;
TYPED_TEST_SUITE(Constructed, FloatingTypes);

TYPED_TEST(Constructed, DefaultConstruct) {
  ASSERT_EQ(TestFixture::pid.GetKp(), 0);
  ASSERT_EQ(TestFixture::pid.GetKi(), 0);
  ASSERT_EQ(TestFixture::pid.GetKd(), 0);
}

TYPED_TEST(Constructed, ValueConstruct) {
  ASSERT_EQ(TestFixture::pidVals.GetKp(), 1);
  ASSERT_EQ(TestFixture::pidVals.GetKi(), 2);
  ASSERT_EQ(TestFixture::pidVals.GetKd(), 3);
}

TYPED_TEST(Constructed, ValueSet) {
  TestFixture::pid.SetK(1, 2, 3);
  ASSERT_EQ(TestFixture::pid.GetKp(), 1);
  ASSERT_EQ(TestFixture::pid.GetKi(), 2);
  ASSERT_EQ(TestFixture::pid.GetKd(), 3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
