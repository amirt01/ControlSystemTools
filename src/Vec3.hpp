// Copyright (c) 2023 Amir Tadros

#ifndef CONTROLSYSTEMTOOLS_VEC3_H
#define CONTROLSYSTEMTOOLS_VEC3_H

#include <array>
#include <cmath>

template<typename RealType, typename = typename std::enable_if<std::is_arithmetic<RealType>::value, RealType>::type>
struct Vec3 {
  union {
    struct { RealType x, y, z; };
    std::array<RealType, 3> values{std::numeric_limits<RealType>::quiet_NaN(),
                                   std::numeric_limits<RealType>::quiet_NaN(),
                                   std::numeric_limits<RealType>::quiet_NaN()};
  };

  //! Constructors
  Vec3() = default;
  Vec3(const RealType x, const RealType y, const RealType z) : values{x, y, z} {}
  explicit Vec3(const RealType value) : Vec3(value, value, value) {}
  explicit Vec3(const RealType source[3]) : Vec3(source[0], source[1], source[2]) {}
  explicit Vec3(const std::array<RealType, 3>& source) : Vec3(source.data()) {}

  //! Accessors
  RealType operator[](size_t i) const { return values.at(i); }
  RealType& operator[](size_t i) { return values.at(i); }
  RealType* data() { return values.data(); };

  //! Elementwise Mathematical Operators (Vec3)
  Vec3 operator+(const Vec3& source) const { return {x + source.x, y + source.y, z + source.z}; }
  Vec3 operator-(const Vec3& source) const { return {x - source.x, y - source.y, z - source.z}; }
  Vec3 operator*(const Vec3& source) const { return {x * source.x, y * source.y, z * source.z}; }

  //! Elementwise Pre-Scalar Mathematical Operators
  Vec3 operator*(const RealType source) const { return *this * Vec3(source); }
  Vec3 operator/(const RealType source) const { return {x / source, y / source, z / source}; }

  //! Assignment Operators
  Vec3 operator+=(const Vec3& rhs) { return *this = *this + rhs; }
  Vec3 operator-=(const Vec3& rhs) { return *this = *this - rhs; }
  Vec3 operator*=(const Vec3& rhs) { return *this = *this * rhs; }
  Vec3 operator*=(const RealType& rhs) { return *this = *this * rhs; }
  Vec3 operator/=(const RealType& rhs) { return *this = *this / rhs; }

  //! Equality Operator
  bool operator==(const Vec3& source) const { return values == source.values; }

  //! Aesthetic Operators
  Vec3 operator+() const { return *this; }
  Vec3 operator-() const { return *this * static_cast<RealType>(-1); }

  //! Mathematical Functions
  RealType Dot(const Vec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
  Vec3 Cross(const Vec3& rhs) const { return {y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x}; }

  RealType GetNorm2Squared() const { return this->Dot(*this); };
  RealType GetNorm2() const { return std::sqrt(GetNorm2Squared()); };
  Vec3 GetUnitVector() const { return *this / this->GetNorm2(); }

  //! Operations
  void fill(const RealType source) { values.fill(source); }
  void swap(Vec3& source) noexcept { std::swap(values, source.values); }

  //! Iterators
  decltype(values.begin()) begin() { return values.begin(); };
  decltype(values.end()) end() { return values.end(); };
  decltype(values.cbegin()) cbegin() const noexcept { return values.cbegin(); };
  decltype(values.cend()) cend() const noexcept { return values.cend(); };

  //! Legacy Functions
  double tsqrt(double in) { return sqrt(in); }
  float tsqrt(float in) { return sqrtf(in); }
};

//! Post-Scalar Operators
template<typename RealType>
Vec3<RealType> operator*(const RealType& lhs, const Vec3<RealType>& rhs) { return rhs * lhs; }

//! Instances We Care About
typedef Vec3<char> Vec3c;
typedef Vec3<short> Vec3s;
typedef Vec3<unsigned> Vec3u;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

#endif //CONTROLSYSTEMTOOLS_VEC3_H
