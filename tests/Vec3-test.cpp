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

using MyTypes  = testing::Types<char, short, unsigned, int, float, double>;
TYPED_TEST_SUITE(Constructed, MyTypes);
TYPED_TEST_SUITE(Comparison, MyTypes);

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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
