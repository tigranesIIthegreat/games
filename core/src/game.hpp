#pragma once

#include "game_state.hpp"
#include "input.hpp"
#include "window.hpp"

#include <memory>
#include <stack>
#include <string>

namespace core {

class Game : public input::Inputable {
public:
    Game(const std::string& title, int width, int height, int fps = 60);
    virtual ~Game() = default;

public:
    void run();

protected:
    void _one_iteration();
    virtual void _handle_inputs();
    void _update();
    void _render();

protected:
    void _push_state(GameStateRef state);
    void _pop_state();

protected:
    std::stack<GameStateRef> _states;
    WindowRef _window;
    input::InputManagerRef _input_manager;
    bool _running;
    const size_t _frame_delay;
};

}  // namespace core