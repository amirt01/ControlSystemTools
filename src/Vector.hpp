//
// Created by amirt on 10/4/2023.
//

#ifndef CONTROLSYSTEMTOOLS_SRC_VECTOR_HPP_
#define CONTROLSYSTEMTOOLS_SRC_VECTOR_HPP_

#include <limits>
#include <array>
#include <cmath>
#include <functional>

template<typename Tp, std::size_t N, typename = typename std::enable_if<std::is_arithmetic<Tp>::value, Tp>::type>
struct Vector {
  union {
    struct { Tp container[N]; };
    std::array<Tp, N> values;
  };

  //! Constructors
  Vector() : Vector(std::numeric_limits<Tp>::quiet_NaN()) {};
  Vector(std::initializer_list<Tp> l) { std::copy(l.begin(), l.end(), values.begin()); }
  explicit Vector(const Tp value) { values.fill(value); }
  explicit Vector(const Tp source[N]) { std::copy(source, source + N, values.begin()); }
  explicit Vector(const std::array<Tp, N>& source) : Vector(source.data()) {}

  //! Accessors
  Tp operator[](size_t i) const { return this->at(i); }
  Tp& operator[](size_t i) { return this->at(i); }
  Tp at(size_t i) const { return values.at(i); }
  Tp& at(size_t i) { return values.at(i); }
  Tp* data() { return values.data(); };

  //! Elementwise Mathematical Operators (Container)
  Vector operator+(const Vector& rhs) const { return ElementwiseOperation(rhs, std::plus<Tp>()); }
  Vector operator-(const Vector& rhs) const { return ElementwiseOperation(rhs, std::minus<Tp>()); }
  Vector operator*(const Vector& rhs) const { return ElementwiseOperation(rhs, std::multiplies<Tp>()); }

  //! Elementwise Post-Scalar Mathematical Operators
  Vector operator*(const Tp rhs) const { return *this * Vector(rhs); }

  Vector operator/(const Tp rhs) const {
    Vector ret;
    for (size_t i = 0; i < values.size(); i++) ret.at(i) = values.at(i) / rhs;
    return ret;
  }

  //! Assignment Operators
  Vector operator+=(const Vector& rhs) { return *this = *this + rhs; }
  Vector operator-=(const Vector& rhs) { return *this = *this - rhs; }
  Vector operator*=(const Vector& rhs) { return *this = *this * rhs; }
  Vector operator*=(const Tp rhs) { return *this = *this * rhs; }
  Vector operator/=(const Tp rhs) { return *this = *this / rhs; }

  //! Equality Operator
  bool operator==(const Vector& rhs) const { return values == rhs.values; }

  //! Explicit Cast
  template<typename CastType>
  explicit operator Vector<CastType, N>() { return {std::initializer_list<CastType>(values.data)}; }

  //! Aesthetic Operators
  Vector operator+() const { return *this; }
  Vector operator-() const { return *this * -1; }

  //! Mathematical Functions
  Tp Dot(const Vector& rhs) const {
    Tp ret = 0;
    for (size_t i = 0; i < values.size(); i++) ret += values.at(i) * rhs.values.at(i);
    return ret;
  }

  Tp GetNorm2Squared() const { return this->Dot(*this); };
  Tp GetNorm2() const { return std::sqrt(GetNorm2Squared()); };
  Vector GetUnitVector() const { return *this / this->GetNorm2(); }

  //! Operations
  void fill(const Tp source) { values.fill(source); }
  void swap(Vector& source) noexcept { std::swap(values, source.values); }

  //! Iterators
  decltype(values.begin()) begin() { return values.begin(); };
  decltype(values.end()) end() { return values.end(); };
  decltype(values.cbegin()) cbegin() const noexcept { return values.cbegin(); };
  decltype(values.cend()) cend() const noexcept { return values.cend(); };

 private:
  //! Internal Utilities
  template<class F>
  Vector ElementwiseOperation(const Vector& rhs, F f) const {
    Vector ret;
    for (size_t i = 0; i < values.size(); i++) ret.at(i) = f(values.at(i), rhs.at(i));
    return ret;
  }
};

//! Pre-Scalar Multiplication
template<typename Tp, std::size_t N>
Vector<Tp, N> operator*(const Tp lhs, const Vector<Tp, N>& rhs) { return rhs * lhs; }

#endif //CONTROLSYSTEMTOOLS_SRC_VECTOR_HPP_
