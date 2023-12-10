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
  using ForcerWrapper = TypeWrapper<Forcer<Tf>>;
  using PointForcer = std::pair<ForcerWrapper, Vec3>;

 protected:
  virtual void CalculateInertiaMatrix() {};

 public:
  RigidBody() {
    if (APPLY_GRAVITY) {
      ApplyForce(Forcer(Vec3(0, 0, -9.81)));
    }
  }
  RigidBody(const BodyMatrix& inertia_matrix, const Tf mass)
      : inertia_matrix_(inertia_matrix),
        inertia_matrix_inverse_(inertia_matrix.inverse()),
        mass_(mass) {
    if (APPLY_GRAVITY) {
      ApplyForce(Forcer(Vec3(0, 0, -9.81)));
    }
  }

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
  void ApplyForce(const ForcerWrapper& forcer, const Vec3& point_of_application = {0, 0, 0}) {
    forcers_.emplace_back(forcer, point_of_application);
  }

  void RemoveForce(const ForcerWrapper& forcer, const Vec3& point_of_application = {0, 0, 0}) {
    std::erase(forcers_, std::make_pair(forcer, point_of_application));
  }

  void ClearForces() {
    forcers_.clear();
    if (APPLY_GRAVITY) {
      ApplyForce(Forcer(Vec3(0, 0, -9.81)));
    }
  }

  Vec3 GetResultantForce() const {
    return std::ranges::fold_left(
        forcers_ | std::ranges::views::keys,  // sum all the forces; disregard their point of applications
        Vec3{0, 0, 0},
        [](const Vec3& resultant, const ForcerWrapper& forcer) -> Vec3 {
          const Vec3 force = forcer.get().force;
          return resultant + force;
        }
    );
  }

  Vec3 GetResultantTorque() const {
    return std::ranges::fold_left(
        forcers_,
        Vec3{0, 0, 0},
        [](const Vec3& resultant, const PointForcer& point_forcer) -> Vec3 {
          const Vec3 radius = point_forcer.second;
          const Vec3 force = point_forcer.first.get().force;
          return resultant + radius.cross(force);
        }
    );
  }

  //! Kinematic Functions
  void Update(const cmn::tm::Time& dt) {
    const Tf dt_s = dt.AsSeconds();

    acceleration_ = GetResultantForce() / mass_;
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
  std::vector<PointForcer> forcers_{};
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_SIMULATION_RIGIDBODY_HPP_
