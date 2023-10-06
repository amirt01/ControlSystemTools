//
// Created by amirt on 10/4/2023.
//

#ifndef CONTROLSYSTEMTOOLS_SRC_CONTAINER_HPP_
#define CONTROLSYSTEMTOOLS_SRC_CONTAINER_HPP_

#include <limits>
#include <array>
#include <cmath>
#include <algorithm>
#include <numeric>

template<typename Tp, std::size_t N>
struct Container {
  std::array<Tp, N> values;

  //! Constructors
  Container() : Container(std::numeric_limits<Tp>::quiet_NaN()) {};
  Container(std::initializer_list<Tp> l) { std::copy(l.begin(), l.end(), values.begin()); }
  explicit Container(const Tp value) { values.fill(value); }
  explicit Container(const Tp source[N]) { std::copy(source, source + N, values.begin()); }
  explicit Container(const std::array<Tp, N>& source) : Container(source.data()) {}

  //! Accessors
  Tp operator[](size_t i) const { return this->at(i); }
  Tp& operator[](size_t i) { return this->at(i); }
  Tp at(size_t i) const { return values.at(i); }
  Tp& at(size_t i) { return values.at(i); }
  Tp* data() { return values.data(); };

  //! Elementwise Mathematical Operators (Container)
  Container operator+(const Container& rhs) const { return ElementwiseOperation(rhs, std::plus<Tp>()); }
  Container operator-(const Container& rhs) const { return ElementwiseOperation(rhs, std::minus<Tp>()); }
  Container operator*(const Container& rhs) const { return ElementwiseOperation(rhs, std::multiplies<Tp>()); }

  //! Elementwise Post-Scalar Mathematical Operators
  Container operator*(const Tp rhs) const { return *this * Container(rhs); }

  Container operator/(const Tp rhs) const {
    Container ret;
    std::transform(values.cbegin(), values.cend(), ret.begin(),
                   std::bind(std::divides<Tp>(), std::placeholders::_1, rhs));
    return ret;
  }

  //! Assignment Operators
  Container operator+=(const Container& rhs) { return *this = *this + rhs; }
  Container operator-=(const Container& rhs) { return *this = *this - rhs; }
  Container operator*=(const Container& rhs) { return *this = *this * rhs; }
  Container operator*=(const Tp rhs) { return *this = *this * rhs; }
  Container operator/=(const Tp rhs) { return *this = *this / rhs; }

  //! Comparison Operators
  bool operator==(const Container& rhs) const { return values == rhs.values; }
  bool operator!=(const Container& rhs) const { return values != rhs.values; }

  //! Explicit Cast
  template<typename CastType>
  explicit operator Container<CastType, N>() { return {std::initializer_list<CastType>(values.data)}; }

  //! Aesthetic Operators
  Container operator+() const { return *this; }
  Container operator-() const { return *this * -1; }

  //! Mathematical Functions
  Tp Dot(const Container& rhs) const {
    return std::inner_product(values.begin(), values.end(), rhs.cbegin(), static_cast<Tp>(0));
  }

  Tp GetNorm2Squared() const { return Dot(*this); };
  Tp GetNorm2() const { return std::sqrt(GetNorm2Squared()); };
  Container GetUnitVector() const { return *this / GetNorm2(); }

  //! Operations
  void fill(const Tp source) { values.fill(source); }
  void swap(Container& source) noexcept { std::swap(values, source.values); }

  //! Iterators
  decltype(values.begin()) begin() { return values.begin(); };
  decltype(values.end()) end() { return values.end(); };
  decltype(values.cbegin()) cbegin() const noexcept { return values.cbegin(); };
  decltype(values.cend()) cend() const noexcept { return values.cend(); };

 private:
  //! Internal Utilities
  template<class F>
  Container ElementwiseOperation(const Container& rhs, F f) const {
    Container ret;
    std::transform(values.cbegin(), values.cend(), rhs.cbegin(), ret.begin(), f);
    return ret;
  }
};

//! Pre-Scalar Multiplication
template<typename Ts, typename Tp, std::size_t N>
Container<Tp, N> operator*(const Ts lhs, const Container<Tp, N>& rhs) { return rhs * static_cast<Tp>(lhs); }

#endif //CONTROLSYSTEMTOOLS_SRC_CONTAINER_HPP_
