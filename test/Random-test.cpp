//
// Created by amirt on 11/22/2023.
//

#include <gtest/gtest.h>

#include "NormalNoise.hpp"

using namespace cmn::rnd;

class Constructed : public testing::Test {
 public:
  NormalNoise<> nn{};
  NormalNoise<> nn2{10, 2};

  void SetUp() override {
  }
};

TEST_F(Constructed, Default) {
  std::cout << nn();

  EXPECT_EQ(nn.Mean(), 0);
  EXPECT_EQ(nn.Stddev(), 1);
}

TEST_F(Constructed, Set) {
  std::cout << nn2();

  EXPECT_EQ(nn2.Mean(), 10);
  EXPECT_EQ(nn2.Stddev(), 2);
}

TEST_F(Constructed, Reset) {
  nn.Reset(10, 2);

  std::cout << nn();

  EXPECT_EQ(nn.Mean(), 10);
  EXPECT_EQ(nn.Stddev(), 2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
