//
// Created by amirt on 12/8/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_SIMULATION_VTOL_HPP_
#define CONTROLSYSTEMTOOLS_LIB_SIMULATION_VTOL_HPP_

#include "RigidBody.hpp"
#include "MotorProp.hpp"

namespace sim {

template<std::size_t N_ROTORS, std::floating_point Tf = double>
class VTOL : RigidBody<Tf> {
 public:
  VTOL() = default;

 private:
  std::array<MotorProp<Tf>, N_ROTORS> motors;
};

}  // namespace sim

#endif //CONTROLSYSTEMTOOLS_LIB_SIMULATION_VTOL_HPP_
