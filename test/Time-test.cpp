//
// Created by amirt on 11/21/2023.
//

#include <iostream>

#include <gtest/gtest.h>

#include "Stopwatch.hpp"

using namespace cmn::tm;

class Constructed : public testing::Test {
 public:
  MStopwatch sw{};

  void SetUp() override {
    ManualClock::Reset();
    sw.Reset();
  }
};

TEST_F(Constructed, DefaultConstruct) {
  EXPECT_EQ(sw.GetElapsedTime(), Time(0, 0));
}

TEST_F(Constructed, NonStartElapsed) {
  ManualClock::Advance(10, 0);

  EXPECT_FALSE(sw.GetRunning());
  EXPECT_EQ(sw.GetElapsedTime(), Time(0, 0));
}

TEST_F(Constructed, NonStopElapsed) {
  sw.Start();
  ManualClock::Advance(10, 0);

  EXPECT_TRUE(sw.GetRunning());
  EXPECT_EQ(sw.GetElapsedTime(), Time(10, 0));
}

TEST_F(Constructed, OperatorAdvance) {
  sw.Start();
  ManualClock::Advance(10, 0);
  sw.Stop();
  ManualClock::Advance(10, 0);

  EXPECT_FALSE(sw.GetRunning());
  EXPECT_EQ(sw.GetElapsedTime(), Time(10, 0));
}

TEST_F(Constructed, RunningAfterAdvance) {
  ManualClock::Advance(10, 0);
  sw.Start();
  ManualClock::Advance(10, 0);

  EXPECT_TRUE(sw.GetRunning());
  EXPECT_EQ(sw.GetElapsedTime(), Time(10, 0));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
