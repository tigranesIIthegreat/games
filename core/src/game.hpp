#pragma once

#include <memory>
#include <stack>
#include <string>

#include "game_state.hpp"
#include "window.hpp"

namespace core {

class Game {
public:
    Game(const std::string& title, int width, int height, int fps);
    virtual ~Game() = default;

public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handle_events() = 0;

public:
    void run();
    bool running() const;

protected:
    void push_state(GameStateRef state);
    void pop_state();

protected:
    std::stack<GameStateRef> _states;
    WindowRef _window;
    bool _running;
    const size_t _frame_delay;
};

}  // namespace core