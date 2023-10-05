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
struct MixedFloating : public testing::Test { Vec3d vd{2, 5, 9}; Vec3f vf{6, 3, 8}; };
struct IntegralFloating : public testing::Test { Vec3i vi{4, 1, 3}; Vec3f vf{7, 5, 9}; };
struct ScalarFloating : public testing::Test { double d{3.0}; int i{2}; Vec3f vf{6, 8, 5}; };

TEST(Constructing, Array) {
  int a[3] = {1, 2, 3}; Vec3i vi(a);
  EXPECT_EQ(vi[0], 1); EXPECT_EQ(vi[1], 2); EXPECT_EQ(vi[2], 3);
}

TEST(Constructing, Copy) {
  Vec3i vi1{1, 2, 3}; Vec3i vi2(vi1);
  EXPECT_EQ(vi2[0], 1); EXPECT_EQ(vi2[1], 2); EXPECT_EQ(vi2[2], 3);
}

TEST(Constructing, CopyNarrowing) {
  Vec3f vi1{1, 2, 3}; Vec3f vi2(vi1);
  EXPECT_EQ(vi2[0], 1); EXPECT_EQ(vi2[1], 2); EXPECT_EQ(vi2[2], 3);
}

TEST(Constructing, MoveNarrowing) {
  Vec3d vi1{1, 2, 3}; Vec3f vi2(std::move(vi1));
  EXPECT_EQ(vi2[0], 1); EXPECT_EQ(vi2[1], 2); EXPECT_EQ(vi2[2], 3);
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
  std::array<double, 3> da = {3.0, 5.1, 3.8}; Vec3f vf(da);
  EXPECT_EQ(vf[0], 3); EXPECT_FLOAT_EQ(vf[1], 5.1); EXPECT_FLOAT_EQ(vf[2], 3.8);
}

TEST(Constructing, CArrayNarrowing) {
  double cda[3] = {3.0, 5.1, 3.8}; Vec3f vf(cda);
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

TEST_F(MixedFloating, DotDF) { EXPECT_EQ(vd.Dot(vf), 99); EXPECT_EQ(typeid(vd.Dot(vf)), typeid(double)); }
TEST_F(MixedFloating, DotFD) { EXPECT_EQ(vf.Dot(vd), 99); EXPECT_EQ(typeid(vf.Dot(vd)), typeid(double)); }
TEST_F(MixedFloating, CrossDF) { EXPECT_EQ(vd.Cross(vf), Vec3<double>(13, 38, -24)); EXPECT_EQ(typeid(vd.Cross(vf)), typeid(Vec3<double>)); }
TEST_F(MixedFloating, CrossFD) { EXPECT_EQ(vf.Cross(vd), Vec3<double>(-13, -38, 24)); EXPECT_EQ(typeid(vf.Cross(vd)), typeid(Vec3<double>)); }

TEST_F(IntegralFloating, DotDF) { EXPECT_EQ(vi.Dot(vf), 60); EXPECT_EQ(typeid(vi.Dot(vf)), typeid(float)); }
TEST_F(IntegralFloating, DotFD) { EXPECT_EQ(vf.Dot(vi), 60); EXPECT_EQ(typeid(vf.Dot(vi)), typeid(float)); }
TEST_F(IntegralFloating, CrossDF) { EXPECT_EQ(vi.Cross(vf), Vec3<float>(-6, -15, 13)); EXPECT_EQ(typeid(vi.Cross(vf)), typeid(Vec3<float>)); }
TEST_F(IntegralFloating, CrossFD) { EXPECT_EQ(vf.Cross(vi), Vec3<float>(6, 15, -13)); EXPECT_EQ(typeid(vf.Cross(vi)), typeid(Vec3<float>)); }

//TEST_F(ScalarFloating, MultD) { vf*d; }
//TEST_F(ScalarFloating, MultD) { d*vf; }
TEST_F(ScalarFloating, FloatFirst) { EXPECT_EQ(vf*i, Vec3<float>(12, 16, 10)); EXPECT_EQ(typeid(vf*i), typeid(Vec3<float>)); }
TEST_F(ScalarFloating, FloatSecond) { EXPECT_EQ(i*vf, Vec3<float>(12, 16, 10)); EXPECT_EQ(typeid(i*vf), typeid(Vec3<float>)); }

TEST(Math, GetUnitVector) { Vec3<float> v(0, 0, 0); EXPECT_EQ(v.GetUnitVector(), Vec3<float>(0, 0, 0)); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
