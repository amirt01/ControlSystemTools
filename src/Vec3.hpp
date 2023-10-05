// Copyright (c) 2023 Amir Tadros

#ifndef CONTROLSYSTEMTOOLS_VEC3_H
#define CONTROLSYSTEMTOOLS_VEC3_H

#include "Vector.hpp"

template<typename Tp, typename = typename std::enable_if<std::is_arithmetic<Tp>::value, Tp>::type>
struct Vec3 : public Vector<Tp, 3> {
  union {
    struct { Tp x, y, z; };
    std::array<Tp, 3> values;
  };

  //! Constructors
  Vec3() : Vector<Tp, 3>() {}
  Vec3(Tp x, Tp y, Tp z) : Vector<Tp, 3>({x, y, z}) {}
  explicit Vec3(const Tp value) : Vector<Tp, 3>(value) {}
  explicit Vec3(const Tp source[3]) : Vector<Tp, 3>(source) {}
  explicit Vec3(const std::array<Tp, 3>& source) : Vector<Tp, 3>(source) {}

  //! Explicit Cast
  template<typename CastType>
  explicit operator Vec3<CastType>() { return {x, y, z}; }

  //! Mathematical Functions
  Vec3 Cross(const Vec3& rhs) const { return {y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x}; }
};

//! Instances We Care About
typedef Vec3<char> Vec3c;
typedef Vec3<short> Vec3s;
typedef Vec3<unsigned> Vec3u;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

#endif //CONTROLSYSTEMTOOLS_VEC3_H
