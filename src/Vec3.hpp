// Copyright (c) 2023 Amir Tadros

#ifndef CONTROLSYSTEMTOOLS_VEC3_H
#define CONTROLSYSTEMTOOLS_VEC3_H

#include <type_traits>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <array>

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

  explicit Vec3(const RealType& value) : x(value), y(value), z(value) {}

  Vec3(const RealType x, const RealType y, const RealType z) : x(x), y(y), z(z) {}

  explicit Vec3(const RealType source[3]) { std::copy_n(source, 3, values.begin()); };

  template<typename SourceType>
  explicit Vec3(const std::array<SourceType, 3>& source) { std::copy_n(source.begin(), 3, values.begin()); }

  template<typename SourceType>
  explicit Vec3(const Vec3<SourceType>& source) { std::copy_n(source.values.begin(), 3, values.begin()); };

  //! Assignment Operators
  template<typename SourceType>
  Vec3& operator=(const Vec3<SourceType>& source) {
    values = source.values;
    return *this;
  }

  template<typename SourceType>
  Vec3& operator=(Vec3<SourceType>&& source) {
    std::copy_n(source.values.begin(), 3, values.begin());
    return *this;
  }

  template<typename SourceType>
  operator Vec3<SourceType>() const { return Vec3<SourceType>(*this); }

  template<typename SourceType>
  Vec3 operator+=(const Vec3<SourceType> rhs) { return *this = *this + rhs; }

  template<typename SourceType>
  Vec3 operator-=(const Vec3<SourceType> rhs) { return *this = *this - rhs; }

  template<typename SourceType>
  Vec3 operator*=(const SourceType& rhs) { return *this = *this * rhs; }

  template<typename SourceType>
  Vec3 operator/=(const SourceType& rhs) { return *this = (*this) / rhs; }

  //! Accessors
  RealType operator[](size_t i) const { return values.at(i); }
  RealType& operator[](size_t i) { return values.at(i); }
  auto data() -> decltype(values.data()) { return values.data(); };

  //! Equality Operator
  template<typename SourceType>
  bool operator==(const Vec3<SourceType>& source) const { return values == source.values; }

  //! Vec3 Mathematical Operators
  template<typename SourceType>
  auto operator+(const Vec3<SourceType>& source) const -> Vec3<decltype(x + source.x)> {
    return {x + source.x, y + source.y, z + source.z};
  }

  template<typename SourceType>
  auto operator-(const Vec3<SourceType>& source) const -> Vec3<decltype(x - source.x)> {
    return {x - source.x, y - source.y, z - source.z};
  }

  template<typename SourceType>
  auto operator/(const Vec3<SourceType>& source) const -> Vec3<decltype(x / source.x)> {
    return {x / source.x, y / source.y, z / source.z};
  }

  template<typename SourceType>
  auto operator*(const Vec3<SourceType>& source) const -> Vec3<decltype(x * source.x)> {
    return {x * source.x, y * source.y, z * source.z};
  }

  //! Post-Scalar Mathematical Operators
  template<typename SourceType>
  auto operator+(const SourceType source) const -> Vec3<decltype(x + source)> {
    return {x + source, y + source, z + source};
  }

  template<typename SourceType>
  auto operator-(const SourceType source) const -> Vec3<decltype(x - source)> {
    return {x - source.x, y - source.y, z - source.z};
  }

  template<typename SourceType>
  auto operator/(const SourceType source) const -> Vec3<decltype(x / source)> {
    return {x / source, y / source, z / source};
  }

  template<typename SourceType>
  auto operator*(const SourceType source) const -> Vec3<decltype(x * source)> {
    return {x * source, y * source, z * source};
  }

  Vec3 operator+() const { return *this; }
  Vec3 operator-() const { return *this * -1; }

  //! Mathematical Functions
  template<typename SourceType>
  auto Dot(const Vec3<SourceType> rhs) const -> decltype(x * rhs.x) {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }

  template<typename SourceType>
  auto Cross(const Vec3<SourceType> rhs) const -> Vec3<decltype(x * rhs.x)> {
    return {y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x};
  }

  RealType GetNorm2Squared() const { return this->Dot(*this); };
  RealType GetNorm2() const { return std::sqrt(GetNorm2Squared()); };
  Vec3 GetUnitVector() const { return x == 0 && y == 0 && z == 0 ? Vec3(0, 0, 0) : *this / this->GetNorm2(); }

  //! Operations
  template<typename SourceType>
  void fill(const SourceType& source) { values.fill(source); }

  template<typename SourceType>
  void swap(Vec3<SourceType>& source) noexcept { std::swap(values, source.values); }

  //! Iterators
  auto begin() -> decltype(values.begin()) { return values.begin(); };
  auto cbegin() const noexcept -> decltype(values.cbegin()) { return values.cbegin(); };
  auto end() -> decltype(values.end()) { return values.end(); };
  auto cend() const noexcept -> decltype(values.cend()) { return values.cend(); };

  //! Legacy Functions
  double tsqrt(double in) { return sqrt(in); }
  float tsqrt(float in) { return sqrtf(in); }
};

//! Pre-Scalar Operators
template<typename RealType, typename ScalarType>
auto operator*(const RealType& lhs, const Vec3<ScalarType>& rhs) -> Vec3<decltype(rhs.x * lhs)> {
  return {rhs.x * lhs, rhs.y * lhs, rhs.z * lhs};
}

template<typename RealType, typename ScalarType>
auto operator+(const RealType& lhs, const Vec3<ScalarType>& rhs) -> Vec3<decltype(rhs.x + lhs)> {
  return {rhs.x + lhs, rhs.y + lhs, rhs.z + lhs};
}

//! Delete Vec3<float>->Vec3<double> conversion for hard operations
void operator*(double, Vec3<float>) = delete;
void operator*(Vec3<float>, double) = delete;
void operator*(Vec3<float>, Vec3<double>) = delete;
void operator*(Vec3<double>, Vec3<float>) = delete;
void operator/(double, Vec3<float>) = delete;
void operator/(Vec3<float>, double) = delete;
void operator/(Vec3<float>, Vec3<double>) = delete;
void operator/(Vec3<double>, Vec3<float>) = delete;

//! Instances We Care About
typedef Vec3<char> Vec3c;
typedef Vec3<short> Vec3s;
typedef Vec3<unsigned> Vec3u;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

#endif //CONTROLSYSTEMTOOLS_VEC3_H
