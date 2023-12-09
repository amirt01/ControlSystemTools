//
// Created by amirt on 12/8/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_SIMULATION_MOTORPROP_HPP_
#define CONTROLSYSTEMTOOLS_LIB_SIMULATION_MOTORPROP_HPP_

#include "Forcer.hpp"
#include "RigidBody.hpp"

namespace sim {

template<std::floating_point Tf>
class MotorProp : Forcer<Tf>, RigidBody<Tf> {

};

}

#endif //CONTROLSYSTEMTOOLS_LIB_SIMULATION_MOTORPROP_HPP_
