//
// Created by amirt on 3/20/2024.
//

#ifndef CONTROLSYSTEMTOOLS_LIB_COMMON_STAGES_STATEMACHINE_HPP_
#define CONTROLSYSTEMTOOLS_LIB_COMMON_STAGES_STATEMACHINE_HPP_

#include <array>

namespace sm {

typedef void(* StateFun)();
template<std::size_t N_STATES> using StateArray = std::array<StateFun, N_STATES>;

typedef void (* TransitionFun)();
struct Transition {
  StateFun from;
  StateFun to;
  TransitionFun transition_fun;

  Transition(StateFun from, StateFun to, TransitionFun transition_fun = nullptr)
      : from(from), to(to), transition_fun(transition_fun) {}
};
template<std::size_t N_TRANSITIONS> using TransitionArray = std::array<Transition, N_TRANSITIONS>;

template<std::size_t N_STATES, std::size_t N_TRANSITIONS>
class StateMachine {
 private:
  StateArray<N_STATES> states;
  TransitionArray<N_TRANSITIONS> transitions;

  StateFun current_state;

 public:
  StateMachine(const StateArray<N_STATES>& states, const TransitionArray<N_TRANSITIONS>& transitions,
               StateFun start_state)
      : states(states), transitions(transitions), current_state(start_state) {}

  StateMachine(const StateArray<N_STATES>& states, const TransitionArray<N_TRANSITIONS>& transitions)
      : StateMachine(states, transitions, states.front()) {}

  void run() { current_state(); }
  bool transition_to(StateFun state) {
    // No need to transition if we are already at the target state
    if (state == current_state) {
      return false;
    }

    auto transition_itr = std::ranges::find_if(transitions, [this, state](auto transition) {
      return transition.from == current_state && transition.to == state;
    });

    // Check if the transition was found
    if (transition_itr == transitions.end()) {
      return false;
    }

    // Check if the transition is non-trivial
    if (transition_itr->transition_fun) {
      transition_itr->transition_fun();
    }

    current_state = transition_itr->to;

    return true;
  }
};

}

#endif //CONTROLSYSTEMTOOLS_LIB_COMMON_STAGES_STATEMACHINE_HPP_
