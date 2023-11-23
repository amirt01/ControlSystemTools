//
// Created by amirt on 11/22/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_NOISE_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_NOISE_HPP_

#include <random>
#include <algorithm>

#include <Eigen/Dense>

namespace cmn::rnd {

template<template<typename> typename Td, std::floating_point Tf = double>
class Noise {
 public:
  Noise() = default;

  template<std::convertible_to<Tf> ...Tp>
  explicit Noise(Tp...args) : gen(args...) {}

  template<std::convertible_to<Tf> ...Tp>
  void Reset(Tp...args) { gen = Td<Tf>(args...); }

  Tf operator()() { return gen(dev); }

  template<int N>
  Eigen::Vector<Tf, N> Vector() {
    Eigen::Vector<Tf, N> noiseVec{};
    std::ranges::generate(noiseVec, *this);
    return noiseVec;
  }

  template<std::convertible_to<Tf> Ts>
  void Apply(Ts& source) { source += (*this)(); }

  template<std::convertible_to<Tf> Ts, int N>
  void Apply(Eigen::Vector<Ts, N>& source) {
    std::ranges::for_each(source, [this](Ts& value) { return Apply(value); });
  }

 protected:
  static inline std::random_device rd{};
  static inline std::mt19937 dev{rd()};
  Td<Tf> gen;
};

}  // namespace cmn::rnd

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_NOISE_HPP_
