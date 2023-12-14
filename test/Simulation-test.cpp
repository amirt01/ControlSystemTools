//
// Created by amirt on 12/7/2023.
//

#include <gtest/gtest.h>

#include "RigidBody.hpp"
#include "Stopwatch.hpp"

using namespace sim;

TEST(TypeWrapper, Default) {
  TypeWrapper<int> i;

  i = TypeWrapper<int>(3);
  std::cout << int(i);
}

TEST(Basic, ResultantForce) {
  RigidBody<double, false> fb{};
  EXPECT_EQ(fb.GetResultantForce(), Eigen::Vector3<double>(0, 0, 0));
  fb.ApplyForce({1, 0, 0});
  EXPECT_EQ(fb.GetResultantForce(), Eigen::Vector3<double>(1, 0, 0));
  fb.ApplyForce({0, 1, 0});
  EXPECT_EQ(fb.GetResultantForce(), Eigen::Vector3<double>(1, 1, 0));
  fb.ApplyForce({0, 0, 1});
  EXPECT_EQ(fb.GetResultantForce(), Eigen::Vector3<double>(1, 1, 1));
}

TEST(Basic, ResultantTorque) {
  RigidBody<> fb{};
  EXPECT_EQ(fb.GetResultantTorque(), Eigen::Vector3<double>(0, 0, 0));
  fb.ApplyForce({1, 0, 0}, {0, 1, 0});
  EXPECT_EQ(fb.GetResultantTorque(), Eigen::Vector3<double>(0, 0, -1));
  fb.ApplyForce({0, 0, 1}, {0, 1, 0});
  EXPECT_EQ(fb.GetResultantTorque(), Eigen::Vector3<double>(1, 0, -1));
  fb.ApplyForce({0, 1, 0}, {1, 0, 0});
  EXPECT_EQ(fb.GetResultantTorque(), Eigen::Vector3<double>(1, 0, 0));
  fb.ApplyForce({0, 1, 0}, {1, 0, 0});
  fb.RemoveForce({0, 1, 0}, {1, 0, 0});
  EXPECT_EQ(fb.GetResultantTorque(), Eigen::Vector3<double>(1, 0, -1));
}

TEST(Basic, Update) {
  RigidBody<> fb{};
  fb.Update({0, 100});
}

TEST(Time, ResultantTorque) {
  RigidBody<> rb{};

  for (double i = 0; i < 1000000; i++) {
    rb.ApplyForce({i, 0, -i}, {0, i, 0});
  }

  for (double i = 0; i < 500000; i++) {
    rb.ApplyForce({i, 0, -i}, {0, 0, 0});
  }

  using namespace cmn::tm;
  Stopwatch<HardwareClock> s;
  s.Start();
  rb.GetResultantTorque();
  s.Stop();
  std::cout << s.GetElapsedTime();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
