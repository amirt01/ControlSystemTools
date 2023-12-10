//
// Created by amirt on 12/8/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_SIMULATION_FORCER_HPP_
#define CONTROLSYSTEMTOOLS_LIB_SIMULATION_FORCER_HPP_

#include <concepts>

#include <Eigen/Dense>

namespace sim {

template<std::floating_point Tf = double>
struct Forcer {
  Eigen::Vector3<Tf> force{0, 0, 0};

  bool operator<=>(const Forcer& rhs) const = default;
};

}  // namespace sim

#endif //CONTROLSYSTEMTOOLS_LIB_SIMULATION_FORCER_HPP_
