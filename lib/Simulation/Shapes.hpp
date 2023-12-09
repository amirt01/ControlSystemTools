//
// Created by amirt on 12/7/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_SIMULATION_SHAPES_HPP_
#define CONTROLSYSTEMTOOLS_LIB_SIMULATION_SHAPES_HPP_

#include "RigidBody.hpp"

namespace sim {

template<std::floating_point Tf>
class Sphere : RigidBody<Tf> {
  void CalculateInertiaMatrix() override {
    this->inertia_matrix_.diagonal().setConstant(Tf(2) / 5 * this->mass * radius_ * radius_);
  }

 public:
  Sphere() = default;
  explicit Sphere(Tf radius) : radius_(radius) {}
  Sphere(Tf radius_, Tf mass) : radius_(radius_) { this->SetMass(mass); }

 private:
  Tf radius_;
};

template<std::floating_point Tf>
class Cube : RigidBody<Tf> {
  void CalculateInertiaMatrix() override {
    this->inertia_matrix_.diagonal().setConstant(this->mass * side_length_ * side_length_ / 6);
  }

 public:
  Cube() = default;
  explicit Cube(Tf side_length) : side_length_(side_length) {}
  Cube(Tf side_length, Tf mass) : side_length_(side_length) { this->SetMass(mass); }

  void SetSideLength(Tf side_length) {
    side_length_ = side_length;
    CalculateInertiaMatrix();
  }

 private:
  Tf side_length_;
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_SIMULATION_SHAPES_HPP_
