//
// Created by amirt on 12/9/2023.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_TYPES_TYPEWRAPPER_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_TYPES_TYPEWRAPPER_HPP_

#include <functional>
#include <variant>

template<class T>
class TypeWrapper {
  using Callback = std::function<T()>;
  using Reference = std::reference_wrapper<T>;

 public:
  TypeWrapper() = default;
  explicit TypeWrapper(Callback callback) : var(callback) {}
  explicit TypeWrapper(T value) : var(value) {}
  explicit TypeWrapper(Reference reference) : var(reference) {}

  bool operator==(TypeWrapper rhs) const { return get() == rhs.get(); }

  explicit operator T() const { return get(); }

  //TODO: convert this to compile time
  T get() const {
    switch (var.index()) {
      case 0: return std::get<Callback>(var)();
      case 1: return std::get<Reference>(var).get();
      default: return std::get<T>(var);
    }
  }

 private:
  std::variant<Callback, Reference, T> var;
};

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_TYPES_TYPEWRAPPER_HPP_
