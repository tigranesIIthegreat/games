#include "game_state_machine.hpp"

namespace core {

void GameStateMachine::push_state(GameStateRef state) {
    _states.push(state);
    _states.top()->on_enter();
}

void GameStateMachine::pop_state() {
    if (_states.empty()) {
        throw std::runtime_error("Cannot pop state from an empty FSM");
    }
    _states.top()->on_exit();
    _states.pop();
}

} // namespace core