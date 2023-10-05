//
// Created by amirt on 10/5/2023.
//

#include <gtest/gtest.h>

#include "Vector.hpp"

struct Double : public testing::Test { Vector<double, 5> c1 = {1, 2, 3, 4, 5}, c2{5, 4, 3, 2, 1}; };

TEST(Construction, ArrayInitialization) {
  double a[3] = {3, 2, 1};
  Vector<double, 3> c1(a);
  Vector<double, 3> c2{3, 2, 1};
  EXPECT_EQ(c1, c2);
}

TEST_F(Double, DotProduct) { EXPECT_EQ(c1.Dot(c2), 35); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
