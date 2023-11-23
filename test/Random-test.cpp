//
// Created by amirt on 11/22/2023.
//

#include <gtest/gtest.h>

#include "NormalNoise.hpp"
#include "UniformNoise.hpp"

using namespace cmn::rnd;

class NormalNoiseTest : public testing::Test {
 public:
  NormalNoise<> nn{};
  NormalNoise<> nn2{10, 2};
};

class UniformNoiseTest : public testing::Test {
  public:
   UniformNoise<> un{};
   UniformNoise<> un2{10, 2};
};

TEST_F(NormalNoiseTest, Default) {
  std::cout << nn();

  EXPECT_EQ(nn.Mean(), 0);
  EXPECT_EQ(nn.Stddev(), 1);
}

TEST_F(NormalNoiseTest, Set) {
  std::cout << nn2();

  EXPECT_EQ(nn2.Mean(), 10);
  EXPECT_EQ(nn2.Stddev(), 2);
}

TEST_F(NormalNoiseTest, Reset) {
  nn.Reset(10, 2);

  std::cout << nn();

  EXPECT_EQ(nn.Mean(), 10);
  EXPECT_EQ(nn.Stddev(), 2);
}


TEST_F(UniformNoiseTest, Default) {
  std::cout << un();

  EXPECT_EQ(un.A(), 0);
  EXPECT_EQ(un.B(), 1);
}

TEST_F(UniformNoiseTest, Set) {
  std::cout << un2();

  EXPECT_EQ(un2.A(), 10);
  EXPECT_EQ(un2.B(), 2);
}

TEST_F(UniformNoiseTest, Reset) {
  un.Reset(10, 2);

  std::cout << un();

  EXPECT_EQ(un.A(), 10);
  EXPECT_EQ(un.B(), 2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
