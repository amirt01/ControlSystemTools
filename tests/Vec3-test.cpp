//
// Created by amirt on 10/3/2023.
//

#include <gtest/gtest.h>

#include "Vec3.hpp"

struct DefaultFloat : public testing::Test { Vec3d v{}; };
struct DefaultInt : public testing::Test { Vec3d v{}; };
struct Zeros : public testing::Test { Vec3d v{0, 0, 0}; };
struct Double : public testing::Test { Vec3d v{1, 1, 1}; };
struct Float : public testing::Test { Vec3f v{1, 1, 1}; };
struct IntegralFloating : public testing::Test { Vec3i vi{4, 1, 3}; Vec3f vf{7, 5, 9}; };
struct ScalarFloating : public testing::Test { float f{3.0}; Vec3f vf{6, 8, 5}; };

TEST(Constructing, Array) {
  int a[3] = {1, 2, 3}; Vec3i vi(a);
  EXPECT_EQ(vi[0], 1); EXPECT_EQ(vi[1], 2); EXPECT_EQ(vi[2], 3);
}

TEST(Constructing, Copy) {
  Vec3i vi1{1, 2, 3}; Vec3i vi2(vi1);
  EXPECT_EQ(vi2[0], 1); EXPECT_EQ(vi2[1], 2); EXPECT_EQ(vi2[2], 3);
}

TEST(Constructing, Move) {
  Vec3f vf1{1, 2, 3}; Vec3f vf2(std::move(vf1));
  EXPECT_EQ(vf2[0], 1); EXPECT_EQ(vf2[1], 2); EXPECT_EQ(vf2[2], 3);
}

TEST(Constructing, AssignNarrowing) {
  Vec3f vi1{1, 2, 3}; Vec3f vi2 = vi1;
  EXPECT_EQ(vi2[0], 1); EXPECT_EQ(vi2[1], 2); EXPECT_EQ(vi2[2], 3);
}

TEST(Constructing, FillNarrowing) {
  const double value = 3.0; Vec3f vf(value);
  EXPECT_EQ(vf[0], 3); EXPECT_EQ(vf[1], 3); EXPECT_EQ(vf[2], 3);
}

TEST(Constructing, ArrayNarrowing) {
  std::array<float, 3> da = {3.0, 5.1, 3.8}; Vec3f vf(da);
  EXPECT_EQ(vf[0], 3); EXPECT_FLOAT_EQ(vf[1], 5.1); EXPECT_FLOAT_EQ(vf[2], 3.8);
}

TEST(Constructing, CArrayNarrowing) {
  float cda[3] = {3.0, 5.1, 3.8}; Vec3f vf(cda);
  EXPECT_EQ(vf[0], 3); EXPECT_FLOAT_EQ(vf[1], 5.1); EXPECT_FLOAT_EQ(vf[2], 3.8);
}

TEST_F(DefaultFloat, XValue) { EXPECT_TRUE(std::isnan(v.x)); }
TEST_F(DefaultFloat, YValue) { EXPECT_TRUE(std::isnan(v.y)); }
TEST_F(DefaultFloat, ZValue) { EXPECT_TRUE(std::isnan(v.z)); }
TEST_F(DefaultFloat, FirstValue) { EXPECT_TRUE(std::isnan(v[0])); }
TEST_F(DefaultFloat, SecondValue) { EXPECT_TRUE(std::isnan(v[1])); }
TEST_F(DefaultFloat, ThirdValue) { EXPECT_TRUE(std::isnan(v[2])); }

TEST_F(DefaultInt, XValue) { EXPECT_TRUE(std::isnan(v.x)); }
TEST_F(DefaultInt, YValue) { EXPECT_TRUE(std::isnan(v.y)); }
TEST_F(DefaultInt, ZValue) { EXPECT_TRUE(std::isnan(v.z)); }
TEST_F(DefaultInt, FirstValue) { EXPECT_TRUE(std::isnan(v[0])); }
TEST_F(DefaultInt, SecondValue) { EXPECT_TRUE(std::isnan(v[1])); }
TEST_F(DefaultInt, ThirdValue) { EXPECT_TRUE(std::isnan(v[2])); }

TEST_F(Zeros, XValue) { EXPECT_EQ(v.x, 0.0); EXPECT_EQ(typeid(v.x), typeid(double)); }
TEST_F(Zeros, YValue) { EXPECT_EQ(v.y, 0.0); EXPECT_EQ(typeid(v.y), typeid(double)); }
TEST_F(Zeros, ZValue) { EXPECT_EQ(v.z, 0.0); EXPECT_EQ(typeid(v.z), typeid(double)); }
TEST_F(Zeros, FirstValue) { EXPECT_EQ(v[0], 0.0); EXPECT_EQ(typeid(v[0]), typeid(double)); }
TEST_F(Zeros, SecondValue) { EXPECT_EQ(v[1], 0.0); EXPECT_EQ(typeid(v[1]), typeid(double)); }
TEST_F(Zeros, ThirdValue) { EXPECT_EQ(v[2], 0.0); EXPECT_EQ(typeid(v[2]), typeid(double)); }
TEST_F(Zeros, Dot) { EXPECT_EQ(v.Dot(v), 0); EXPECT_EQ(typeid(v.Dot(v)), typeid(double)); }

TEST_F(Double, XValue) { EXPECT_EQ(v.x, 1.0); EXPECT_EQ(typeid(v.x), typeid(double)); }
TEST_F(Double, YValue) { EXPECT_EQ(v.y, 1.0); EXPECT_EQ(typeid(v.y), typeid(double)); }
TEST_F(Double, ZValue) { EXPECT_EQ(v.z, 1.0); EXPECT_EQ(typeid(v.z), typeid(double)); }
TEST_F(Double, FirstValue) { EXPECT_EQ(v[0], 1.0); EXPECT_EQ(typeid(v[0]), typeid(double)); }
TEST_F(Double, SecondValue) { EXPECT_EQ(v[1], 1.0); EXPECT_EQ(typeid(v[1]), typeid(double)); }
TEST_F(Double, ThirdValue) { EXPECT_EQ(v[2], 1.0); EXPECT_EQ(typeid(v[2]), typeid(double)); }
TEST_F(Double, Dot) { EXPECT_EQ(v.Dot(v), 3.0); EXPECT_EQ(typeid(v.Dot(v)), typeid(double)); }
TEST_F(Double, Cross) { EXPECT_EQ(v.Cross(v), Vec3<double>(0.0, 0.0, 0.0)); EXPECT_EQ(typeid(v.Cross(v)), typeid(Vec3<double>)); }
TEST_F(Double, Negative) { EXPECT_EQ(-v, Vec3<double>(-1.0, -1.0, -1.0)); EXPECT_EQ(typeid(-v), typeid(Vec3<double>)); }

TEST_F(Float, XValue) { EXPECT_EQ(v.x, 1.f); EXPECT_EQ(typeid(v.x), typeid(float)); }
TEST_F(Float, YValue) { EXPECT_EQ(v.y, 1.f); EXPECT_EQ(typeid(v.y), typeid(float)); }
TEST_F(Float, ZValue) { EXPECT_EQ(v.z, 1.f); EXPECT_EQ(typeid(v.z), typeid(float)); }
TEST_F(Float, FirstValue) { EXPECT_EQ(v[0], 1.f); EXPECT_EQ(typeid(v[0]), typeid(float)); }
TEST_F(Float, SecondValue) { EXPECT_EQ(v[1], 1.f); EXPECT_EQ(typeid(v[1]), typeid(float)); }
TEST_F(Float, ThirdValue) { EXPECT_EQ(v[2], 1.f); EXPECT_EQ(typeid(v[2]), typeid(float)); }
TEST_F(Float, Dot) { EXPECT_EQ(v.Dot(v), 3.f); EXPECT_EQ(typeid(v.Dot(v)), typeid(float)); }
TEST_F(Float, Cross) { EXPECT_EQ(v.Cross(v), Vec3<float>(0.f, 0.f, 0.f)); EXPECT_EQ(typeid(v.Cross(v)), typeid(Vec3<float>)); }
TEST_F(Float, Negative) { EXPECT_EQ(-v, Vec3<float>(-1.f, -1.f, -1.f)); EXPECT_EQ(typeid(-v), typeid(Vec3<float>)); }

TEST_F(ScalarFloating, PreMult) { EXPECT_EQ(f*vf, Vec3<float>(3*6, 3*8, 3*5)); }
TEST_F(ScalarFloating, PostMult) { EXPECT_EQ(vf*f, Vec3<float>(3*6, 3*8, 3*5)); }

TEST(Math, GetUnitVector) { Vec3<float> v(1, 0, 0); EXPECT_EQ(v.GetUnitVector(), Vec3<float>(1, 0, 0)); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
