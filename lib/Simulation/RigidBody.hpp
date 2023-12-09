//
// Created by amirt on 12/7/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_SIMULATION_RIGIDBODY_HPP_
#define CONTROLSYSTEMTOOLS_LIB_SIMULATION_RIGIDBODY_HPP_

#include <vector>
#include <functional>
#include <algorithm>
#include <ranges>

#include <Eigen/Dense>

#include "Time.hpp"
#include "TypeWrapper.hpp"

#include "Forcer.hpp"

namespace sim {

template<std::floating_point Tf = double, bool APPLY_GRAVITY = true>
class RigidBody {
  using Vec3 = Eigen::Vector3<Tf>;
  using Quat = Eigen::Quaternion<Tf>;
  using BodyMatrix = Eigen::DiagonalMatrix<Tf, 3>;
  using Forcer = TypeWrapper<Forcer<Tf>>;
  using PointForce = std::pair<Forcer, Vec3>;

 protected:
  virtual void CalculateInertiaMatrix() {};

 public:
  RigidBody() = default;
  RigidBody(const BodyMatrix& inertia_matrix, const Tf mass)
      : inertia_matrix_(inertia_matrix),
        inertia_matrix_inverse_(inertia_matrix.inverse()),
        mass_(mass) {}

  //! Getters
  [[nodiscard]] Vec3 GetPosition() const noexcept { return position_; }
  [[nodiscard]] Quat GetOrientation() const noexcept { return orientation_; }

  //! Setters
  void SetPosition(const Vec3& position) { position_ = position; }
  void SetOrientation(const Quat& orientation) { orientation_ = orientation; }
  void SetMomentOfInertia(const BodyMatrix& inertia_matrix) {
    inertia_matrix_ = inertia_matrix;
    inertia_matrix_inverse_ = inertia_matrix_.inverse();
  }
  void SetMass(const Tf mass) {
    this->mass_ = mass;
    CalculateInertiaMatrix();
    inertia_matrix_inverse_ = inertia_matrix_.inverse();
  };

  //! Physical Functions
  void ApplyForce(const Forcer& forcer, const Vec3& pointOfApplication = {0, 0, 0}) {
    forces_.emplace_back(forcer, pointOfApplication);
  }

  void ClearForces() {
    forces_.clear();
  }

  Vec3 GetResultantForce() const {
    return std::ranges::fold_left(
        forces_ | std::ranges::views::keys,  // sum all the forces; disregard their point of applications
        Vec3{0, 0, 0},
        [](const Vec3& resultant, const Forcer& force) -> Vec3 {
          return resultant + force.get().force;
        }
    );
  }

  Vec3 GetResultantTorque() const {
    return std::ranges::fold_left(
        forces_,
        Vec3{0, 0, 0},
        [](const Vec3& resultant, const PointForce& force) -> Vec3 {
          return resultant + force.second.cross(force.first.get().force);
        }
    );
  }

  void Update(const cmn::tm::Time& dt) {
    const Tf dt_s = dt.AsSeconds();

    acceleration_ = GetResultantForce() / mass_;
    if constexpr (APPLY_GRAVITY) {
      acceleration_.z() -= Tf(9.81);
    }
    velocity_ += acceleration_ * dt_s;
    position_ += velocity_ * dt_s + Tf(0.5) * acceleration_ * dt_s * dt_s;

    angular_velocity_ += inertia_matrix_inverse_
        * (GetResultantTorque() - angular_velocity_.cross(inertia_matrix_ * angular_velocity_)) * dt_s;
    orientation_.coeffs() += (orientation_ * Quat(0, angular_velocity_)).coeffs() * Tf(0.5) * dt_s;
    orientation_.normalize();
  }

 private:
  //! Dynamic Attributes
  Vec3 acceleration_{};
  Vec3 velocity_{};
  Vec3 position_{};

  Vec3 angular_velocity_{};
  Quat orientation_{};

  //! Physical Attributes
  BodyMatrix inertia_matrix_{}, inertia_matrix_inverse_{};
  Tf mass_{};

  //! Kinematic Attributes
  std::vector<PointForce> forces_{};
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_SIMULATION_RIGIDBODY_HPP_
