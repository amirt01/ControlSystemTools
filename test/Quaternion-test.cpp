//
// Created by amirt on 10/3/2023.
//

#include <gtest/gtest.h>

#include "Quaternion.hpp"

template<typename T>
class Constructed : public testing::Test {
 private:
  T cArray[4]{1, 2, 3, 4};
  std::array<T, 4> cppArray{1, 2, 3, 4};

 public:
  Quaternion<T> defaultConstructed{};
  Quaternion<T> valuesConstructed{1, 2, 3, 4};
  Quaternion<T> valueConstructed{1};
  Quaternion<T> fromCArray{cArray};
  Quaternion<T> fromCppArray{cppArray};
};

using FloatingTypes = testing::Types<float, double, long double>;
using IntegerTypes = testing::Types<char, short, unsigned, int>;
using AllTypes = testing::Types<char, short, unsigned, int, float, double>;
TYPED_TEST_SUITE(Constructed, FloatingTypes);

TYPED_TEST(Constructed, DefaultConstructed) {
  EXPECT_TRUE(std::isnan(TestFixture::defaultConstructed.data()[0]));
  EXPECT_TRUE(std::isnan(TestFixture::defaultConstructed.data()[1]));
  EXPECT_TRUE(std::isnan(TestFixture::defaultConstructed.data()[1]));
}
TYPED_TEST(Constructed, ValuesConstructed) {
  EXPECT_EQ(TestFixture::valuesConstructed.data()[0], 1);
  EXPECT_EQ(TestFixture::valuesConstructed.data()[1], 2);
  EXPECT_EQ(TestFixture::valuesConstructed.data()[2], 3);
  EXPECT_EQ(TestFixture::valuesConstructed.data()[3], 4);
}
TYPED_TEST(Constructed, ValueConstructed) {
  EXPECT_EQ(TestFixture::valueConstructed.data()[0], 1);
  EXPECT_EQ(TestFixture::valueConstructed.data()[1], 1);
  EXPECT_EQ(TestFixture::valueConstructed.data()[2], 1);
  EXPECT_EQ(TestFixture::valueConstructed.data()[3], 1);
}
TYPED_TEST(Constructed, FromCArray) {
  EXPECT_EQ(TestFixture::fromCArray.data()[0], 1);
  EXPECT_EQ(TestFixture::fromCArray.data()[1], 2);
  EXPECT_EQ(TestFixture::fromCArray.data()[2], 3);
  EXPECT_EQ(TestFixture::fromCArray.data()[3], 4);
}
TYPED_TEST(Constructed, FromCppArray) {
  EXPECT_EQ(TestFixture::fromCppArray.data()[0], 1);
  EXPECT_EQ(TestFixture::fromCppArray.data()[1], 2);
  EXPECT_EQ(TestFixture::fromCppArray.data()[2], 3);
  EXPECT_EQ(TestFixture::fromCppArray.data()[3], 4);
}

TYPED_TEST(Constructed, Equality) {
  EXPECT_EQ(TestFixture::fromCArray, TestFixture::fromCppArray);
  EXPECT_NE(TestFixture::valuesConstructed, TestFixture::valueConstructed);
}

TYPED_TEST(Constructed, Aestehtic) {
  EXPECT_EQ(-TestFixture::valuesConstructed.s, -1);
  EXPECT_EQ(-TestFixture::valuesConstructed.x, -2);
  EXPECT_EQ(-TestFixture::valuesConstructed.y, -3);
  EXPECT_EQ(-TestFixture::valuesConstructed.z, -4);
  EXPECT_EQ(-TestFixture::valuesConstructed.s, -1);
  EXPECT_EQ(+TestFixture::valuesConstructed.x, 2);
  EXPECT_EQ(+TestFixture::valuesConstructed.y, 3);
  EXPECT_EQ(+TestFixture::valuesConstructed.z, 4);
}
TYPED_TEST(Constructed, AestehticNAN) {
  EXPECT_TRUE(std::isnan(-TestFixture::defaultConstructed.s));
  EXPECT_TRUE(std::isnan(-TestFixture::defaultConstructed.x));
  EXPECT_TRUE(std::isnan(-TestFixture::defaultConstructed.y));
  EXPECT_TRUE(std::isnan(-TestFixture::defaultConstructed.z));
}

TYPED_TEST(Constructed, Addition) {
  EXPECT_EQ((TestFixture::valuesConstructed + TestFixture::valuesConstructed)[0], 2);
  EXPECT_EQ((TestFixture::valuesConstructed + TestFixture::valuesConstructed)[1], 4);
  EXPECT_EQ((TestFixture::valuesConstructed + TestFixture::valuesConstructed)[2], 6);
  EXPECT_EQ((TestFixture::valuesConstructed + TestFixture::valuesConstructed)[3], 8);
}
TYPED_TEST(Constructed, Subtraction) {
  EXPECT_EQ((TestFixture::valuesConstructed - TestFixture::valuesConstructed)[0], 0);
  EXPECT_EQ((TestFixture::valuesConstructed - TestFixture::valuesConstructed)[1], 0);
  EXPECT_EQ((TestFixture::valuesConstructed - TestFixture::valuesConstructed)[2], 0);
  EXPECT_EQ((TestFixture::valuesConstructed - TestFixture::valuesConstructed)[3], 0);
}
TYPED_TEST(Constructed, ContainerMultiplication) {
  EXPECT_EQ((TestFixture::valuesConstructed * TestFixture::valuesConstructed)[0], -28);
  EXPECT_EQ((TestFixture::valuesConstructed * TestFixture::valuesConstructed)[1], 4);
  EXPECT_EQ((TestFixture::valuesConstructed * TestFixture::valuesConstructed)[2], 6);
  EXPECT_EQ((TestFixture::valuesConstructed * TestFixture::valuesConstructed)[3], 8);
}
TYPED_TEST(Constructed, PreMultiplication) {
  EXPECT_EQ((2.0 * TestFixture::valuesConstructed)[0], 2);
  EXPECT_EQ((2.0 * TestFixture::valuesConstructed)[1], 4);
  EXPECT_EQ((2.0 * TestFixture::valuesConstructed)[2], 6);
  EXPECT_EQ((2.0 * TestFixture::valuesConstructed)[3], 8);
}
TYPED_TEST(Constructed, PostMultiplication) {
  EXPECT_EQ((TestFixture::valuesConstructed * 2.0)[0], 2);
  EXPECT_EQ((TestFixture::valuesConstructed * 2.0)[1], 4);
  EXPECT_EQ((TestFixture::valuesConstructed * 2.0)[2], 6);
  EXPECT_EQ((TestFixture::valuesConstructed * 2.0)[3], 8);
}
TYPED_TEST(Constructed, ScalarDevision) {
  EXPECT_EQ((TestFixture::valuesConstructed / 2)[0], 0.5);
  EXPECT_EQ((TestFixture::valuesConstructed / 2)[1], 1);
  EXPECT_EQ((TestFixture::valuesConstructed / 2)[2], 1.5);
  EXPECT_EQ((TestFixture::valuesConstructed / 2)[3], 2);
}

TYPED_TEST(Constructed, AdditiveAssignemnt) {
  TestFixture::valuesConstructed += TestFixture::valuesConstructed;
  EXPECT_EQ(TestFixture::valuesConstructed[0], 2);
  EXPECT_EQ(TestFixture::valuesConstructed[1], 4);
  EXPECT_EQ(TestFixture::valuesConstructed[2], 6);
  EXPECT_EQ(TestFixture::valuesConstructed[3], 8);
}
TYPED_TEST(Constructed, SubtractiveAssignemnt) {
  TestFixture::valuesConstructed -= TestFixture::valuesConstructed;
  EXPECT_EQ(TestFixture::valuesConstructed[0], 0);
  EXPECT_EQ(TestFixture::valuesConstructed[1], 0);
  EXPECT_EQ(TestFixture::valuesConstructed[2], 0);
  EXPECT_EQ(TestFixture::valuesConstructed[3], 0);
}
TYPED_TEST(Constructed, MultiplicativeAssignemnt) {
  TestFixture::valuesConstructed *= TestFixture::valuesConstructed;
  EXPECT_EQ(TestFixture::valuesConstructed[0], -28);
  EXPECT_EQ(TestFixture::valuesConstructed[1], 4);
  EXPECT_EQ(TestFixture::valuesConstructed[2], 6);
  EXPECT_EQ(TestFixture::valuesConstructed[3], 8);
}
TYPED_TEST(Constructed, MultiplicativeScalarAssignemnt) {
  TestFixture::valuesConstructed *= 3.0;
  EXPECT_EQ(TestFixture::valuesConstructed[0], 3);
  EXPECT_EQ(TestFixture::valuesConstructed[1], 6);
  EXPECT_EQ(TestFixture::valuesConstructed[2], 9);
  EXPECT_EQ(TestFixture::valuesConstructed[3], 12);
}
TYPED_TEST(Constructed, DivisorAssignemnt) {
  TestFixture::valuesConstructed /= 3.0;
  EXPECT_FLOAT_EQ(TestFixture::valuesConstructed[0], 1.0/3.0);
  EXPECT_FLOAT_EQ(TestFixture::valuesConstructed[1], 2.0/3.0);
  EXPECT_FLOAT_EQ(TestFixture::valuesConstructed[2], 1);
  EXPECT_FLOAT_EQ(TestFixture::valuesConstructed[3], 4.0/3.0);
}

TYPED_TEST(Constructed, Dot) {
  EXPECT_EQ(TestFixture::valuesConstructed.Dot(TestFixture::valuesConstructed), 30);
  EXPECT_EQ(TestFixture::valueConstructed.Dot(TestFixture::valueConstructed), 4);
  EXPECT_EQ(TestFixture::valuesConstructed.Dot(TestFixture::valueConstructed), 10);
  EXPECT_EQ(TestFixture::valueConstructed.Dot(TestFixture::valuesConstructed), 10);
}
TYPED_TEST(Constructed, NormSquared) {
  EXPECT_EQ(TestFixture::valuesConstructed.NormSquared(), 30);
}
TYPED_TEST(Constructed, GetNorm) {
  EXPECT_FLOAT_EQ(TestFixture::valuesConstructed.Norm(), sqrt(30));
}
//TYPED_TEST(Constructed, GetUnitVector) {
//  auto uv = TestFixture::valuesConstructed.UnitVector();
//  EXPECT_FLOAT_EQ(uv[0], 1/sqrt(30));
//  EXPECT_FLOAT_EQ(uv[1], 2/sqrt(30));
//  EXPECT_FLOAT_EQ(uv[2], 3/sqrt(30));
//  EXPECT_FLOAT_EQ(uv[3], 4/sqrt(30));
//}
TYPED_TEST(Constructed, Conjugate) {

}
TYPED_TEST(Constructed, Inverse) {

}

TYPED_TEST(Constructed, Fill) {
  TestFixture::fromCppArray.fill(5);
  EXPECT_EQ(TestFixture::fromCppArray[0], 5);
  EXPECT_EQ(TestFixture::fromCppArray[1], 5);
  EXPECT_EQ(TestFixture::fromCppArray[2], 5);
  EXPECT_EQ(TestFixture::fromCppArray[3], 5);
}
TYPED_TEST(Constructed, Swap) {
  TestFixture::valueConstructed.swap(TestFixture::valuesConstructed);
  EXPECT_EQ(TestFixture::valueConstructed[0], 1);
  EXPECT_EQ(TestFixture::valueConstructed[1], 2);
  EXPECT_EQ(TestFixture::valueConstructed[2], 3);
  EXPECT_EQ(TestFixture::valueConstructed[3], 4);
  EXPECT_EQ(TestFixture::valuesConstructed[0], 1);
  EXPECT_EQ(TestFixture::valuesConstructed[1], 1);
  EXPECT_EQ(TestFixture::valuesConstructed[2], 1);
  EXPECT_EQ(TestFixture::valuesConstructed[3], 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
