// Copyright (c) 2023 Amir Tadros

#ifndef CONTROLSYSTEMTOOLS_VEC3_H
#define CONTROLSYSTEMTOOLS_VEC3_H

#include <array>
#include <cmath>
#include <limits>

template<
    typename RealType,
    typename = typename std::enable_if<std::is_floating_point<RealType>::value, RealType>::type
>
struct Vec3 {
  union {
    struct { RealType x, y, z; };
    std::array<RealType, 3> vector;
  };

  //! Constructors
  Vec3() : Vec3(std::numeric_limits<RealType>::quiet_NaN()) {};
  Vec3(const RealType x, const RealType y, const RealType z) : vector{x, y, z} {}
  explicit Vec3(const RealType value) : Vec3(value, value, value) {}
  explicit Vec3(const RealType source[3]) : Vec3(source[0], source[1], source[2]) {}
  explicit Vec3(const std::array<RealType, 3>& source) : Vec3(source.data()) {}

  //! Accessors
  RealType operator[](size_t i) const { return vector[i]; }
  RealType& operator[](size_t i) { return vector[i]; }
  RealType at(size_t i) const { return vector.at(i); }
  RealType& at(size_t i) { return vector.at(i); }
  RealType* data() { return vector.data(); };

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
  bool operator==(const Vec3& rhs) const { return vector == rhs.vector; }
  bool operator!=(const Vec3& rhs) const { return vector != rhs.vector; }

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

  RealType Norm2Squared() const { return Dot(*this); };
  RealType Norm2() const { return std::sqrt(Norm2Squared()); };
  Vec3 UnitVector() const { return *this / Norm2(); }

  //! Operations
  void fill(const RealType source) { vector.fill(source); }
  void swap(Vec3& source) noexcept { std::swap(vector, source.vector); }

  //! Iterators
  decltype(vector.begin()) begin() { return vector.begin(); };
  decltype(vector.end()) end() { return vector.end(); };
  decltype(vector.cbegin()) cbegin() const noexcept { return vector.cbegin(); };
  decltype(vector.cend()) cend() const noexcept { return vector.cend(); };
};

//! Pre-Scalar Multiplication
template<typename Ts, typename Tv>
Vec3<Tv> operator*(const Ts lhs, const Vec3<Tv>& rhs) { return rhs * static_cast<Tv>(lhs); }

//! Instances We Care About
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<long double> Vec3l;

#endif //CONTROLSYSTEMTOOLS_VEC3_H
