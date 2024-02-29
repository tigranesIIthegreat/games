#pragma once

#include "game_state.hpp"
#include <memory>
#include <stack>

namespace core {

class GameStateMachine {
public:
    void push_state(GameStateRef state);
    void pop_state();

protected:
    std::stack<GameStateRef> _states;
};

using GameStateMachineRef = std::shared_ptr<GameStateMachine>;

} // namespace core