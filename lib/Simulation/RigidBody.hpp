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

namespace sim {

template<std::floating_point Tf = double, bool APPLY_GRAVITY = true>
class RigidBody {
  using Vec3 = Eigen::Vector3<Tf>;
  using Quat = Eigen::Quaternion<Tf>;
  using BodyMatrix = Eigen::DiagonalMatrix<Tf, 3>;
  using ForceWrapper = TypeWrapper<Vec3>;
  using TorqueWrapper = TypeWrapper<Vec3>;
  using PointForce = std::pair<ForceWrapper, Vec3>;

 protected:
  virtual void CalculateInertiaMatrix() {};

 public:
  RigidBody() {
    if (APPLY_GRAVITY) {
      ApplyForce({0, 0, -9.81});
    }
  }

  RigidBody(const BodyMatrix& inertia_matrix, const Tf mass)
      : inertia_matrix_(inertia_matrix),
        inertia_matrix_inverse_(inertia_matrix.inverse()),
        mass_(mass) {
    if (APPLY_GRAVITY) {
      ApplyForce({0, 0, -9.81});
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
  void ApplyForce(std::function<Vec3()> force_callback, const Vec3& point_of_application = Vec3::Zero()) {
    point_forces_.emplace_back(ForceWrapper(force_callback), point_of_application);
  }

  void ApplyForce(std::reference_wrapper<Vec3> force_reference, const Vec3& point_of_application = Vec3::Zero()) {
    point_forces_.emplace_back(ForceWrapper(force_reference), point_of_application);
  }

  void ApplyForce(const Vec3& force_value, const Vec3& point_of_application = Vec3::Zero()) {
    point_forces_.emplace_back(ForceWrapper(force_value), point_of_application);
  }

  void ApplyTorque(std::function<Vec3()> torque_callback) {
    torques_.push_back(ToruqeWrapper(torque_callback));
  }

  void ApplyTorque(std::reference_wrapper<Vec3> torque_reference) {
    torques_.push_back(TorqueWrapper(torque_reference));
  }

  void ApplyTorque(const Vec3& torque_value) {
    torques_.push_back(TorqueWrapper(torque_value));
  }

  void RemoveForce(const Vec3& force, const Vec3& point_of_application = Vec3::Zero()) {
    std::erase(point_forces_, std::make_pair(ForceWrapper(force), point_of_application));
  }

  void RemoveTorque(const Vec3& torque) {
    std::erase(torques_, TorqueWrapper(torque));
  }

  void ClearForces() {
    point_forces_.clear();
    if (APPLY_GRAVITY) {
      ApplyForce({0, 0, -9.81});
    }
  }

  Vec3 GetResultantForce() const {
    using namespace std::ranges;

    return fold_left_first(
        point_forces_
            | views::keys
            | views::transform(&ForceWrapper::get),
        std::plus<Vec3>()
    ).value_or(Vec3::Zero());
  }

  Vec3 GetResultantTorque() const {
    using namespace std::ranges;

    const Vec3 induced_torques = fold_left_first(
        point_forces_
            | views::transform([](const PointForce& pf) { return pf.second.cross(pf.first.get()); }),
        std::plus<Vec3>()
    ).value_or(Vec3::Zero());

    const Vec3 direct_torques = fold_left_first(
        torques_
            | views::transform(&TorqueWrapper::get),
        std::plus<Vec3>()
    ).value_or(Vec3::Zero());

    return induced_torques + direct_torques;
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
  std::vector<PointForce> point_forces_{};
  std::vector<TorqueWrapper> torques_{};
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_SIMULATION_RIGIDBODY_HPP_
