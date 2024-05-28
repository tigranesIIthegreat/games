#pragma once

#include "game_state.hpp"
#include "input.hpp"
#include "renderable.hpp"
#include "window.hpp"

#include <memory>
#include <stack>
#include <string>

namespace core {

class Game : public Renderable, public input::Interactive {
public:
    Game(int fps = 60);
    virtual ~Game() = default;

public:
    void run();

protected:
    void _one_iteration();
    virtual void handle_inputs() override;
    void _update();
    void _render();

protected:
    void _push_state(GameStateRef state);
    void _pop_state();

protected:
    std::stack<GameStateRef> _states;
    bool _running;
    const size_t _frame_delay;
};

}  // namespace core