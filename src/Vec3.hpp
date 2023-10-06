// Copyright (c) 2023 Amir Tadros

#ifndef CONTROLSYSTEMTOOLS_VEC3_H
#define CONTROLSYSTEMTOOLS_VEC3_H

#include <array>
#include <cmath>

template<
    typename RealType,
    typename = typename std::enable_if<std::is_arithmetic<RealType>::value, RealType>::type
>
struct Vec3 {
  union {
    struct { RealType x, y, z; };
    std::array<RealType, 3> values;
  };

  //! Constructors
  Vec3() : Vec3(std::numeric_limits<RealType>::quiet_NaN()) {};
  Vec3(const RealType x, const RealType y, const RealType z) : values{x, y, z} {}
  explicit Vec3(const RealType value) : Vec3(value, value, value) {}
  explicit Vec3(const RealType source[3]) : Vec3(source[0], source[1], source[2]) {}
  explicit Vec3(const std::array<RealType, 3>& source) : Vec3(source.data()) {}

  //! Accessors
  RealType operator[](size_t i) const { return values.at(i); }
  RealType& operator[](size_t i) { return values.at(i); }
  RealType at(size_t i) const { return values.at(i); }
  RealType& at(size_t i) { return values.at(i); }
  RealType* data() { return values.data(); };

  //! Elementwise Mathematical Operators (Vec3)
  Vec3 operator+(const Vec3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
  Vec3 operator-(const Vec3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }
  Vec3 operator*(const Vec3& rhs) const { return {x * rhs.x, y * rhs.y, z * rhs.z}; }

  //! Elementwise Post-Scalar Mathematical Operators
  Vec3 operator*(const RealType rhs) const { return *this * Vec3(rhs); }
  Vec3 operator/(const RealType rhs) const { return {x / rhs, y / rhs, z / rhs}; }

  //! Assignment Operators
  Vec3 operator+=(const Vec3& rhs) { return *this = *this + rhs; }
  Vec3 operator-=(const Vec3& rhs) { return *this = *this - rhs; }
  Vec3 operator*=(const Vec3& rhs) { return *this = *this * rhs; }
  Vec3 operator*=(const RealType rhs) { return *this = *this * rhs; }
  Vec3 operator/=(const RealType rhs) { return *this = *this / rhs; }

  //! Equality Operator
  bool operator==(const Vec3& rhs) const { return values == rhs.values; }
  bool operator!=(const Vec3& rhs) const { return values != rhs.values; }

  //! Explicit Cast
  template<typename CastType>
  explicit operator Vec3<CastType>() { return {x, y, z}; }

  //! Aesthetic Operators
  Vec3 operator+() const { return *this; }
  Vec3 operator-() const { return *this * -1; }

  //! Mathematical Functions
  RealType Dot(const Vec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
  Vec3 Cross(const Vec3& rhs) const {
    return {y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x};
  }

  RealType GetNorm2Squared() const { return Dot(*this); };
  RealType GetNorm2() const { return std::sqrt(GetNorm2Squared()); };
  Vec3 GetUnitVector() const { return *this / GetNorm2(); }

  //! Operations
  void fill(const RealType source) { values.fill(source); }
  void swap(Vec3& source) noexcept { std::swap(values, source.values); }

  //! Iterators
  decltype(values.begin()) begin() { return values.begin(); };
  decltype(values.end()) end() { return values.end(); };
  decltype(values.cbegin()) cbegin() const noexcept { return values.cbegin(); };
  decltype(values.cend()) cend() const noexcept { return values.cend(); };
};

//! Pre-Scalar Multiplication
template<typename Ts, typename Tv>
Vec3<Tv> operator*(const Ts lhs, const Vec3<Tv>& rhs) { return rhs * static_cast<Tv>(lhs); }

//! Instances We Care About
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<long double> Vec3l;

#endif //CONTROLSYSTEMTOOLS_VEC3_H
