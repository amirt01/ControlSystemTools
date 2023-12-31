// Copyright (c) 2023 Amir Tadros

#ifndef CONTROLSYSTEMTOOLS_VEC3_H
#define CONTROLSYSTEMTOOLS_VEC3_H

#include <array>
#include <cmath>
#include <limits>

template<std::floating_point Tf>
struct Vec3 {
  union {
    struct { Tf x, y, z; };
    std::array<Tf, 3> values;
  };

  //! Constructors
  constexpr Vec3(const Tf x, const Tf y, const Tf z) : x(x), y(y), z(z) {}
  constexpr explicit Vec3(const Tf source[3]) : Vec3(source[0], source[1], source[2]) {}
  constexpr explicit Vec3(const Tf value) : Vec3(value, value, value) {}
  constexpr Vec3() : Vec3(std::numeric_limits<Tf>::quiet_NaN()) {};
  constexpr explicit Vec3(const std::array<Tf, 3> source) : values(std::move(source)) {}

  //! Accessors
  constexpr Tf operator[](size_t i) const { return values[i]; }
  constexpr Tf at(size_t i) const { return values.at(i); }
  Tf& operator[](size_t i) { return values[i]; }
  Tf& at(size_t i) { return values.at(i); }
  constexpr Tf* data() { return values.data(); };

  //! Elementwise Mathematical Operators (Vec3)
  constexpr Vec3 operator+(const Vec3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
  constexpr Vec3 operator-(const Vec3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }
  constexpr Vec3 operator*(const Vec3& rhs) const { return {x * rhs.x, y * rhs.y, z * rhs.z}; }

  //! Elementwise Post-Scalar Mathematical Operators
  constexpr Vec3 operator*(const Tf rhs) const { return *this * Vec3(rhs); }
  constexpr Vec3 operator/(const Tf rhs) const { return {x / rhs, y / rhs, z / rhs}; }

  //! Assignment Operators
  Vec3 operator+=(const Vec3& rhs) { return *this = *this + rhs; }
  Vec3 operator-=(const Vec3& rhs) { return *this = *this - rhs; }
  Vec3 operator*=(const Tf rhs) { return *this = *this * rhs; }
  Vec3 operator/=(const Tf rhs) { return *this = *this / rhs; }

  //! Equality Operator
  constexpr bool operator==(const Vec3& rhs) const { return values == rhs.values; }
  constexpr bool operator!=(const Vec3& rhs) const { return values != rhs.values; }

  //! Explicit Cast
  template<typename CastType>
  constexpr explicit operator Vec3<CastType>() { return {x, y, z}; }

  //! Aesthetic Operators
  constexpr Vec3 operator+() const { return *this; }
  constexpr Vec3 operator-() const { return *this * -1; }

  //! Mathematical Functions
  [[nodiscard]] constexpr Tf Dot(const Vec3& rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
  [[nodiscard]] constexpr Vec3 Cross(const Vec3& rhs) const {
    return {y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x};
  }

  [[nodiscard]] constexpr Tf GetNorm2Squared() const { return Dot(*this); };
  [[nodiscard]] Tf GetNorm2() const { return std::sqrt(GetNorm2Squared()); };
  [[nodiscard]] Vec3 GetUnitVector() const { return *this / GetNorm2(); }

  //! Operations
  void fill(const Tf source) { values.fill(source); }
  void swap(Vec3& source) noexcept { std::swap(values, source.values); }

  //! Iterators
  decltype(values.begin()) begin() { return values.begin(); };
  decltype(values.end()) end() { return values.end(); };
  constexpr decltype(values.cbegin()) cbegin() const noexcept { return values.cbegin(); };
  constexpr decltype(values.cend()) cend() const noexcept { return values.cend(); };
};

//! Pre-Scalar Multiplication
template<std::floating_point Ts, std::floating_point Tv>
constexpr Vec3<Tv> operator*(const Ts lhs, const Vec3<Tv>& rhs) { return rhs * static_cast<Tv>(lhs); }

//! Instances We Care About
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<long double> Vec3l;

#endif //CONTROLSYSTEMTOOLS_VEC3_H
