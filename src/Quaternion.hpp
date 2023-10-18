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
  constexpr Quaternion() : Quaternion(std::numeric_limits<RealType>::quiet_NaN()) {};
  constexpr Quaternion(const RealType s, RealType x, const RealType y, const RealType z) : values{s, x, y, z} {}
  constexpr explicit Quaternion(const RealType value) : Quaternion(value, value, value, value) {}
  constexpr explicit Quaternion(const RealType source[4]) : Quaternion(source[0], source[1], source[2], source[3]) {}
  constexpr explicit Quaternion(const std::array<RealType, 4>& source) : Quaternion(source.data()) {}
  constexpr Quaternion(const RealType s, const RealType vec[3]) : s(s), vector(vec) {}
  constexpr Quaternion(const RealType s, const Vec3<RealType>& vec) : s(s), vector(vec) {}
  constexpr Quaternion(const RealType s, const std::array<RealType, 3>& vec) : s(s), vector(vec) {}

  //! Special Quaternions
  constexpr static Quaternion Identity() { return {1, 0, 0, 0}; }

  //! Accessors
  constexpr RealType operator[](size_t i) const { return values[i]; }
  RealType& operator[](size_t i) { return values[i]; }
  constexpr RealType at(size_t i) const { return values.at(i); }
  RealType& at(size_t i) { return values.at(i); }
  RealType* data() { return values.data(); };

  //! Mathematical Operators (Quaternion)
  constexpr Quaternion operator+(const Quaternion& rhs) const { return {s + rhs.s, vector + rhs.vector}; }
  constexpr Quaternion operator-(const Quaternion& rhs) const { return {s - rhs.s, vector - rhs.vector}; }
  constexpr Quaternion operator*(const Quaternion& rhs) const {
    return {s * rhs.s - vector.Dot(rhs.vector), s * rhs.vector + rhs.s * vector + vector.Cross(rhs.vector)};
  }

  //! Elementwise Post-Scalar Mathematical Operators
  constexpr Quaternion operator*(const RealType rhs) const { return {s * rhs, x * rhs, y * rhs, z * rhs}; }
  constexpr Quaternion operator/(const RealType rhs) const { return {s / rhs, x / rhs, y / rhs, z / rhs}; }

  //! Assignment Operators
  Quaternion operator+=(const Quaternion& rhs) { return *this = *this + rhs; }
  Quaternion operator-=(const Quaternion& rhs) { return *this = *this - rhs; }
  Quaternion operator*=(const Quaternion& rhs) { return *this = *this * rhs; }
  Quaternion operator*=(const RealType rhs) { return *this = *this * rhs; }
  Quaternion operator/=(const RealType rhs) { return *this = *this / rhs; }

  //! Equality Operator
  constexpr bool operator==(const Quaternion& rhs) const { return values == rhs.values; }
  constexpr bool operator!=(const Quaternion& rhs) const { return values != rhs.values; }

  //! Explicit Cast
  template<typename CastType>
  constexpr explicit operator Quaternion<CastType>() const { return {s, x, y, z}; }

  //! Aesthetic Operators
  constexpr Quaternion operator+() const { return *this; }
  constexpr Quaternion operator-() const { return *this * -1; }

  //! Mathematical Functions
  constexpr RealType Dot(const Quaternion& rhs) const { return s * rhs.s + vector.Dot(rhs.vector); }
  constexpr RealType NormSquared() const { return Dot(*this); }
  constexpr RealType Norm() const { return std::sqrt(NormSquared()); }
  constexpr Quaternion Normalize() const { return *this / Norm(); }
  constexpr Quaternion Conjugate() const { return {s, -vector}; }
  constexpr Quaternion Inverse() const { return Conjugate() / NormSquared(); }

  constexpr Vec3<RealType> ToVector() const { return s > 0 ? vector : -vector; }

  //! Operations
  void fill(const RealType source) { values.fill(source); }
  void swap(Quaternion& source) noexcept { std::swap(values, source.values); }

  //! Iterators
  decltype(values.begin()) begin() { return values.begin(); };
  decltype(values.end()) end() { return values.end(); };
  constexpr decltype(values.cbegin()) cbegin() const noexcept { return values.cbegin(); };
  constexpr decltype(values.cend()) cend() const noexcept { return values.cend(); };
};

//! Pre-Scalar Multiplication
template<typename Tl, typename Tr>
constexpr Quaternion<Tr> operator*(const Tl lhs, const Quaternion<Tr>& rhs) { return static_cast<Tr>(lhs) * rhs; }

//! Instances We Care About
typedef Quaternion<float> Quatf;
typedef Quaternion<double> Quatd;
typedef Quaternion<long double> Quatl;

#endif //CONTROLSYSTEMTOOLS_SRC_QUATERNION_HPP_
