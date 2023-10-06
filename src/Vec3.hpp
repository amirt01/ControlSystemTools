// Copyright (c) 2023 Amir Tadros

#ifndef CONTROLSYSTEMTOOLS_VEC3_H
#define CONTROLSYSTEMTOOLS_VEC3_H

#include "Container.hpp"

template<typename Tp>
struct Vec3 {
  union {
    struct { Tp x, y, z; };
    Container<Tp, 3> values;
  };

  //! Constructors
  Vec3() : values() {}
  Vec3(Tp x, Tp y, Tp z) : values({x, y, z}) {}
  explicit Vec3(const Tp value) : values(value) {}
  explicit Vec3(const Tp source[3]) : values(source) {}
  explicit Vec3(const std::array<Tp, 3>& source) : values(source) {}
  explicit Vec3(const Container<Tp, 3>& source) : values(source) {}

  //! Accessors
  Tp operator[](size_t i) const { return values.at(i); }
  Tp& operator[](size_t i) { return values.at(i); }
  Tp at(size_t i) const { return values.at(i); }
  Tp& at(size_t i) { return values.at(i); }
  Tp* data() { return values.data(); };

  //! Elementwise Mathematical Operators (Container)
  Vec3 operator+(const Vec3& rhs) const { return Vec3{values + rhs.values}; }
  Vec3 operator-(const Vec3& rhs) const { return Vec3{values - rhs.values}; }
  Vec3 operator*(const Vec3& rhs) const { return Vec3{values * rhs.values}; }

  //! Elementwise Post-Scalar Mathematical Operators
  template<typename ST>
  Vec3 operator*(const ST rhs) const { return Vec3{values * rhs}; }
  template<typename ST>
  Vec3 operator/(const ST rhs) const { return Vec3{values / rhs}; }

  //! Assignment Operators
  Vec3 operator+=(const Vec3& rhs) { return Vec3{values += rhs.values}; }
  Vec3 operator-=(const Vec3& rhs) { return Vec3{values += rhs.values}; }
  Vec3 operator*=(const Vec3& rhs) { return Vec3{values += rhs.values}; }
  Vec3 operator*=(const Tp rhs) { return Vec3{values *= rhs}; }
  Vec3 operator/=(const Tp rhs) { return Vec3{values /= rhs}; }

  //! Comparison Operators
  bool operator==(const Vec3& rhs) const { return values == rhs.values; }
  bool operator!=(const Vec3& rhs) const { return values != rhs.values; }

  //! Explicit Cast
  template<typename CastType>
  explicit operator Vec3<CastType>() { return Vec3{std::initializer_list<CastType>(values.data)}; }

  //! Aesthetic Operators
  Vec3 operator+() const { return *this; }
  Vec3 operator-() const { return Vec3{values * -1}; }

  Tp GetNorm2Squared() const { return values.Dot(values); };
  Tp GetNorm2() const { return std::sqrt(GetNorm2Squared()); };
  Vec3 GetUnitVector() const { return Vec3{values / GetNorm2()}; }

  //! Operations
  void fill(const Tp source) { values.fill(source); }
  void swap(Vec3& source) noexcept { values.swap(source.values); }

  //! Iterators
  decltype(values.begin()) begin() { return values.begin(); };
  decltype(values.end()) end() { return values.end(); };
  decltype(values.cbegin()) cbegin() const noexcept { return values.cbegin(); };
  decltype(values.cend()) cend() const noexcept { return values.cend(); };

  //! Mathematical Functions
  Tp Dot(const Vec3& rhs) const { return values.Dot(rhs.values); }
  Vec3 Cross(const Vec3& rhs) const { return {y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x}; }
};

//! Pre-Scalar Multiplication
template<typename SP, typename Tp>
Vec3<Tp> operator*(const SP lhs, const Vec3<Tp>& rhs) { return rhs * lhs; }

//! Instances We Care About
typedef Vec3<char> Vec3c;
typedef Vec3<short> Vec3s;
typedef Vec3<unsigned> Vec3u;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

#endif //CONTROLSYSTEMTOOLS_VEC3_H
