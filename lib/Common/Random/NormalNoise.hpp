//
// Created by amirt on 11/22/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_NORMALNOISE_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_NORMALNOISE_HPP_

#include "Noise.hpp"

namespace cmn::rnd {

template<std::floating_point Tf = double>
class NormalNoise : public Noise<std::normal_distribution, Tf> {
 public:
  NormalNoise() = default;

  explicit NormalNoise(const Tf mean, const Tf stddev = 1)
      : Noise<std::normal_distribution, Tf>(mean, stddev) {}

  [[nodiscard]] Tf Mean() const noexcept { return this->gen.mean(); }

  [[nodiscard]] Tf Stddev() const noexcept { return this->gen.stddev(); }
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_NORMALNOISE_HPP_
