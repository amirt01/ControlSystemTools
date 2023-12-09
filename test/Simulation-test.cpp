//
// Created by amirt on 12/7/2023.
//

#include <gtest/gtest.h>

#include "RigidBody.hpp"

using namespace sim;

TEST(Basic, ResultantForce) {
  RigidBody<> fb{};
  EXPECT_EQ(fb.GetResultantForce(), Eigen::Vector3<double>(0, 0, 0));
  Forcer<> f1({1, 0, 0}); fb.ApplyForce(f1);
  EXPECT_EQ(fb.GetResultantForce(), Eigen::Vector3<double>(1, 0, 0));
  Forcer<> f2({0, 1, 0}); fb.ApplyForce(f2);
  EXPECT_EQ(fb.GetResultantForce(), Eigen::Vector3<double>(1, 1, 0));
  Forcer<> f3({0, 0, 1}); fb.ApplyForce(f3);
  EXPECT_EQ(fb.GetResultantForce(), Eigen::Vector3<double>(1, 1, 1));
}

TEST(Basic, ResultantTorque) {
  RigidBody<> fb{};
  EXPECT_EQ(fb.GetResultantTorque(), Eigen::Vector3<double>(0, 0, 0));
  Forcer<> f1({1, 0, 0}); Eigen::Vector3<double> p1({0, 1, 0}); fb.ApplyForce(f1, p1);
  EXPECT_EQ(fb.GetResultantTorque(), Eigen::Vector3<double>(0, 0, -1));
  Forcer<> f2({0, 0, 1}); Eigen::Vector3<double> p2({0, 1, 0}); fb.ApplyForce(f2, p2);
  EXPECT_EQ(fb.GetResultantTorque(), Eigen::Vector3<double>(1, 0, -1));
  Forcer<> f3({0, 1, 0}); Eigen::Vector3<double> p3({1, 0, 0}); fb.ApplyForce(f3, p3);
  EXPECT_EQ(fb.GetResultantTorque(), Eigen::Vector3<double>(1, 0, 0));
}

TEST(Basic, Update) {
  RigidBody<> fb{};
  fb.Update({0, 100});
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
