//
// Created by amirt on 10/3/2023.
//

#include <gtest/gtest.h>

#include "Vec3.hpp"

template<typename T>
class Constructed : public testing::Test {
 private:
  T cArray[3]{1, 2, 3};
  std::array<T, 3> cppArray{1, 2, 3};
  Container<T, 3> container{1, 2, 3};

 public:
  Vec3<T> defaultConstructed{};
  Vec3<T> valuesConstructed{1, 2, 3};
  Vec3<T> valueConstructed{1};
  Vec3<T> fromCArray{cArray};
  Vec3<T> fromCppArray{cppArray};
  Vec3<T> fromContainer{container};
};

using FloatingTypes = testing::Types<float, double>;
using IntegerTypes = testing::Types<char, short, unsigned, int>;
TYPED_TEST_SUITE(Constructed, FloatingTypes);
TYPED_TEST_SUITE(Comparison, FloatingTypes);

TYPED_TEST(Constructed, DefaultConstructed) {
  EXPECT_TRUE(std::isnan(TestFixture::defaultConstructed.data()[0]));
  EXPECT_TRUE(std::isnan(TestFixture::defaultConstructed.data()[1]));
  EXPECT_TRUE(std::isnan(TestFixture::defaultConstructed.data()[1]));
}
TYPED_TEST(Constructed, ValuesConstructed) {
  EXPECT_EQ(TestFixture::valuesConstructed.data()[0], 1);
  EXPECT_EQ(TestFixture::valuesConstructed.data()[1], 2);
  EXPECT_EQ(TestFixture::valuesConstructed.data()[2], 3);
}
TYPED_TEST(Constructed, ValueConstructed) {
  EXPECT_EQ(TestFixture::valueConstructed.data()[0], 1);
  EXPECT_EQ(TestFixture::valueConstructed.data()[1], 1);
  EXPECT_EQ(TestFixture::valueConstructed.data()[2], 1);
}
TYPED_TEST(Constructed, FromCArray) {
  EXPECT_EQ(TestFixture::fromCArray.data()[0], 1);
  EXPECT_EQ(TestFixture::fromCArray.data()[1], 2);
  EXPECT_EQ(TestFixture::fromCArray.data()[2], 3);
}
TYPED_TEST(Constructed, FromCppArray) {
  EXPECT_EQ(TestFixture::fromCppArray.data()[0], 1);
  EXPECT_EQ(TestFixture::fromCppArray.data()[1], 2);
  EXPECT_EQ(TestFixture::fromCppArray.data()[2], 3);
}
TYPED_TEST(Constructed, FromContainer) {
  EXPECT_EQ(TestFixture::fromContainer.data()[0], 1);
  EXPECT_EQ(TestFixture::fromContainer.data()[1], 2);
  EXPECT_EQ(TestFixture::fromContainer.data()[2], 3);
}

TYPED_TEST(Constructed, Equality) {
  EXPECT_EQ(TestFixture::fromCArray, TestFixture::fromCppArray);
  EXPECT_NE(TestFixture::valuesConstructed, TestFixture::valueConstructed);
}

TYPED_TEST(Constructed, Aestehtic) {
  EXPECT_EQ(-TestFixture::valuesConstructed.x, -1);
  EXPECT_EQ(-TestFixture::valuesConstructed.y, -2);
  EXPECT_EQ(-TestFixture::valuesConstructed.z, -3);
  EXPECT_EQ(+TestFixture::valuesConstructed.x, 1);
  EXPECT_EQ(+TestFixture::valuesConstructed.y, 2);
  EXPECT_EQ(+TestFixture::valuesConstructed.z, 3);
}

TYPED_TEST(Constructed, AestehticNAN) {
  EXPECT_TRUE(std::isnan(-TestFixture::defaultConstructed.x));
  EXPECT_TRUE(std::isnan(-TestFixture::defaultConstructed.y));
  EXPECT_TRUE(std::isnan(-TestFixture::defaultConstructed.z));
}

TYPED_TEST(Constructed, Addition) {
  EXPECT_EQ((TestFixture::valuesConstructed + TestFixture::valuesConstructed)[0], 2);
  EXPECT_EQ((TestFixture::valuesConstructed + TestFixture::valuesConstructed)[1], 4);
  EXPECT_EQ((TestFixture::valuesConstructed + TestFixture::valuesConstructed)[2], 6);
}
TYPED_TEST(Constructed, Subtraction) {
  EXPECT_EQ((TestFixture::valuesConstructed - TestFixture::valuesConstructed)[0], 0);
  EXPECT_EQ((TestFixture::valuesConstructed - TestFixture::valuesConstructed)[1], 0);
  EXPECT_EQ((TestFixture::valuesConstructed - TestFixture::valuesConstructed)[2], 0);
}
TYPED_TEST(Constructed, ContainerMultiplication) {
  EXPECT_EQ((TestFixture::valuesConstructed * TestFixture::valuesConstructed)[0], 1);
  EXPECT_EQ((TestFixture::valuesConstructed * TestFixture::valuesConstructed)[1], 4);
  EXPECT_EQ((TestFixture::valuesConstructed * TestFixture::valuesConstructed)[2], 9);
}
TYPED_TEST(Constructed, PreMultiplication) {
  EXPECT_EQ((2 * TestFixture::valuesConstructed)[0], 2);
  EXPECT_EQ((2 * TestFixture::valuesConstructed)[1], 4);
  EXPECT_EQ((2 * TestFixture::valuesConstructed)[2], 6);
}
TYPED_TEST(Constructed, PostMultiplication) {
  EXPECT_EQ((TestFixture::valuesConstructed * 2)[0], 2);
  EXPECT_EQ((TestFixture::valuesConstructed * 2)[1], 4);
  EXPECT_EQ((TestFixture::valuesConstructed * 2)[2], 6);
}
TYPED_TEST(Constructed, ScalarDevision) {
  EXPECT_EQ((TestFixture::valuesConstructed / 2)[0], 0.5);
  EXPECT_EQ((TestFixture::valuesConstructed / 2)[1], 1);
  EXPECT_EQ((TestFixture::valuesConstructed / 2)[2], 1.5);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
