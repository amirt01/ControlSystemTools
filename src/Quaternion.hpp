//
// Created by amirt on 10/4/2023.
//

#ifndef CONTROLSYSTEMTOOLS_SRC_QUATERNION_HPP_
#define CONTROLSYSTEMTOOLS_SRC_QUATERNION_HPP_

#include "Vec3.hpp"

template<
    typename RealType,
    typename = typename std::enable_if<std::is_floating_point<RealType>::value, RealType>::type
>
struct Quaternion {
  union {
    struct {
      RealType s;
      union {
        struct { RealType x, y, z; };
        Vec3<RealType> vector;
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
  Quaternion(const RealType s, const Vec3<RealType>& vec) : s(s), vector(vec)  {}
  Quaternion(const RealType s, const std::array<RealType, 3>& vec) : s(s), vector(vec) {}

  //! Accessors
  RealType operator[](size_t i) const { return values[i]; }
  RealType& operator[](size_t i) { return values[i]; }
  RealType at(size_t i) const { return values.at(i); }
  RealType& at(size_t i) { return values.at(i); }
  RealType* data() { return values.data(); };

  //! Mathematical Operators (Quaternion)
  Quaternion operator+(const Quaternion& rhs) const { return {s + rhs.s, vector + rhs.vector}; }
  Quaternion operator-(const Quaternion& rhs) const { return {s - rhs.s, vector - rhs.vector}; }
  Quaternion operator*(const Quaternion& rhs) const {
    return {s * rhs.s - vector.Dot(rhs.vector),
            s * rhs.vector + rhs.s * vector + vector.Cross(rhs.vector)};
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
  RealType Dot(const Quaternion& rhs) const { return s * rhs.s + vector.Dot(rhs.vector); }
  RealType NormSquared() const { return Dot(*this); }
  RealType Norm() const { return std::sqrt(NormSquared()); }
  Quaternion Normalize() const { return *this / Norm(); }
  Quaternion Conjugate() const { return {s, -vector}; }
  Quaternion Inverse() const { return Conjugate() / *this * Conjugate(); }

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
typedef Quaternion<float> Quatf;
typedef Quaternion<double> Quatd;
typedef Quaternion<long double> Quatl;

#endif //CONTROLSYSTEMTOOLS_SRC_QUATERNION_HPP_
