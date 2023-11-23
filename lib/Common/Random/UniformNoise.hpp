//
// Created by amirt on 11/22/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_UNIFORMNOISE_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_UNIFORMNOISE_HPP_

#include "Noise.hpp"

namespace cmn::rnd {

template<std::floating_point Tf = double>
class UniformNoise : public Noise<std::uniform_real_distribution, Tf> {
 public:
  UniformNoise() = default;

  explicit UniformNoise(const Tf a, const Tf b = 1)
      : Noise<std::uniform_real_distribution, Tf>(a, b) {}

  [[nodiscard]] Tf A() const noexcept { return this->gen.a(); }

  [[nodiscard]] Tf B() const noexcept { return this->gen.b(); }
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_RANDOM_UNIFORMNOISE_HPP_
