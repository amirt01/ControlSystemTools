//
// Created by amirt on 11/22/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_NOISE_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_NOISE_HPP_

#include <random>

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

 protected:
  static inline std::random_device rd{};
  static inline std::mt19937 dev{rd()};
  Td<Tf> gen;
};

}  // namespace cmn::rnd

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_NOISE_HPP_
