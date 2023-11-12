//
// Created by amirt on 11/10/2023.
//

#include <gtest/gtest.h>

#include "LQR.hpp"

template<std::floating_point Tf>
class Constructed : public testing::Test {
 public:

};

using FloatingTypes = testing::Types<float, double, long double>;
TYPED_TEST_SUITE(Constructed, FloatingTypes);

TYPED_TEST(Constructed, DefaultConstruct) {
}

TYPED_TEST(Constructed, ValueConstruct) {
}

TYPED_TEST(Constructed, ValueSet) {
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
