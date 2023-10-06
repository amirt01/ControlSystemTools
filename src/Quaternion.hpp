//
// Created by amirt on 10/4/2023.
//

#ifndef CONTROLSYSTEMTOOLS_SRC_QUATERNION_HPP_
#define CONTROLSYSTEMTOOLS_SRC_QUATERNION_HPP_

#include "Vec3.hpp"

template<
    typename RealType,
    typename = typename std::enable_if<std::is_arithmetic<RealType>::value, RealType>::type
>
struct Quaternion {
  union {
    struct {
      RealType s;
      union {
        struct { RealType x, y, z; };
        Vec3<RealType> vec;
      };
    };
    std::array<RealType, 4> values;
  };

  //! Constructors
  Quaternion() : Quaternion(std::numeric_limits<RealType>::quiet_NaN()) {};
  Quaternion(const RealType s, RealType x, const RealType y, const RealType z) : values{s, x, y, z} {}
  explicit Quaternion(const RealType value) : Quaternion(value, value, value, value) {}
  explicit Quaternion(const RealType source[4]) : Quaternion(source[0], source[1], source[2], source[3]) {}
  explicit Quaternion(const std::array<RealType, 4>& source) : Quaternion(source.data()) {}
  Quaternion(const RealType s, const Vec3<RealType>& vec) : s(s), vec(vec)  {}
  Quaternion(const RealType s, const std::array<RealType, 3>& vec) : s(s), vec(vec) {}

  //! Accessors
  RealType operator[](size_t i) const { return values.at(i); }
  RealType& operator[](size_t i) { return values.at(i); }
  RealType at(size_t i) const { return values.at(i); }
  RealType& at(size_t i) { return values.at(i); }
  RealType* data() { return values.data(); };

  //! Mathematical Operators (Quaternion)
  Quaternion operator+(const Quaternion& rhs) const { return {s + rhs.s, vec + rhs.vec}; }
  Quaternion operator-(const Quaternion& rhs) const { return {s - rhs.s, vec - rhs.vec}; }
  Quaternion operator*(const Quaternion& rhs) const {
    return {s * rhs.s - vec.Dot(rhs.vec),
            s * rhs.vec + rhs.s * vec + vec.Cross(rhs.vec)};
  }

  //! Elementwise Post-Scalar Mathematical Operators
  Quaternion operator*(const RealType rhs) const { return {s * rhs, x * rhs, y * rhs, z * rhs}; }
  Quaternion operator/(const RealType rhs) const { return {s / rhs, x / rhs, y / rhs, z / rhs}; }

  //! Assignment Operators
  Quaternion operator+=(const Quaternion& rhs) { return *this = *this + rhs; }
  Quaternion operator-=(const Quaternion& rhs) { return *this = *this - rhs; }
  Quaternion operator*=(const Quaternion& rhs) { return *this = *this * rhs; }
  Quaternion operator*=(const RealType rhs) { return *this = *this * rhs; }
  Quaternion operator/=(const RealType rhs) { return *this = *this / rhs; }

  //! Equality Operator
  bool operator==(const Quaternion& rhs) const { return values == rhs.values; }
  bool operator!=(const Quaternion& rhs) const { return values != rhs.values; }

  //! Explicit Cast
  template<typename CastType>
  explicit operator Quaternion<CastType>() { return {s, x, y, z}; }

  //! Aesthetic Operators
  Quaternion operator+() const { return *this; }
  Quaternion operator-() const { return *this * -1; }

  //! Mathematical Functions
  RealType NormSquared() {}
  RealType Norm() {}
  Quaternion UnitNorm() {}
  Quaternion Conjugate() {}
  Quaternion Inverse() {}

  //! Operations
  void fill(const RealType source) { values.fill(source); }
  void swap(Quaternion& source) noexcept { std::swap(values, source.values); }

  //! Iterators
  decltype(values.begin()) begin() { return values.begin(); };
  decltype(values.end()) end() { return values.end(); };
  decltype(values.cbegin()) cbegin() const noexcept { return values.cbegin(); };
  decltype(values.cend()) cend() const noexcept { return values.cend(); };
};

//! Pre-Scalar Multiplication
template<typename Ts, typename Tq>
Quaternion<Tq> operator*(const Ts lhs, const Quaternion<Tq>& rhs) { return rhs * static_cast<Tq>(lhs); }

//! Instances We Care About
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<long double> Vec3l;

#endif //CONTROLSYSTEMTOOLS_SRC_QUATERNION_HPP_
