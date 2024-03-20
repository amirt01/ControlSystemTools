//
// Created by amirt on 3/20/2024.
//

#include <gtest/gtest.h>

#include <iostream>

#include "StateMachine.hpp"

class StateMachineTest : public testing::Test {
 public:
  static void s1() { std::cout << "s1\n"; }
  static void s2() { std::cout << "s2\n"; }
  sm::StateArray<2> states{s1, s2};
  sm::TransitionArray<3> transitions{
      sm::Transition{s1, s2, [] { std::cout << "s0 -> s1\n"; }},
      sm::Transition{s2, s1},
      sm::Transition{s1, s1}
  };
  sm::StateMachine<2, 3> sm{states, transitions};

  void SetUp() override {
    sm.transition_to(states.front());
  }
};

TEST_F(StateMachineTest, BasicTransition) {
  sm.run();
  EXPECT_TRUE(sm.transition_to(s2));
  sm.run();
}

TEST_F(StateMachineTest, TrivialTransition) {
  sm.transition_to(s2);
  sm.run();
  EXPECT_TRUE(sm.transition_to(s1));
  sm.run();
}

TEST_F(StateMachineTest, TransitionToCurrentState) {
  sm.run();
  EXPECT_FALSE(sm.transition_to(s1));
  sm.run();
}

TEST_F(StateMachineTest, InvalidTransition) {
  auto s3 = [] { std::cout << "s3\n"; };
  sm.run();
  EXPECT_FALSE(sm.transition_to(s3));
  sm.run();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
