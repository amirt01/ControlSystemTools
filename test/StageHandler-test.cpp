//
// Created by amirt on 11/23/2023.
//

#include <gtest/gtest.h>

#include "StageHandler.hpp"

using namespace cmn::sgs;

TEST(Defaut, AddStage) {
  StageHandler sh{};
  sh.AddStage({[] { std::cout << "test\n"; },
               {1, 0},
               {2, 0}});
  sh.AddStage({[] { std::cout << "test2\n"; },
               {2, 0},
               {3, 0}});
  sh.AddStage({[] { std::cout << "test3\n"; },
               {3, 0},
               {4, 0}});
  sh.Update({1, 0});
  sh.Update({2, 0});
  sh.Update({3, 0});
  sh.Update({4, 0});
}

TEST(Defaut, Constructed) {
  StageHandler sh{
      {[] { std::cout << "test\n"; },
       {1, 0},
       {2, 0}},
      {[] { std::cout << "test2\n"; },
       {2, 0},
       {3, 0}},
      {[] { std::cout << "test3\n"; },
       {3, 0},
       {4, 0}}
  };
  sh.Update({1, 0});
  sh.Update({2, 0});
  sh.Update({3, 0});
  sh.Update({4, 0});
}

TEST(Defaut, StartTime) {
  StageHandler sh{
      {
          {[] { std::cout << "test\n"; },
           {1, 0},
           {2, 0}},
          {[] { std::cout << "test2\n"; },
           {2, 0},
           {3, 0}},
          {[] { std::cout << "test3\n"; },
           {3, 0},
           {4, 0}}
      },
      {1, 0}
  };
  sh.Update({1, 0});
  sh.Update({2, 0});
  sh.Update({3, 0});
}

TEST(Defaut, FailAdd) {
  StageHandler sh{};
  sh.AddStage({[] {},
               {1, 0},
               {2, 0}});
  EXPECT_DEBUG_DEATH(
      sh.AddStage({[] {},
                   {1, 0},
                   {3, 0}}),
      "New stage's start time and the last stage's end time cannot overlap"
  );
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
