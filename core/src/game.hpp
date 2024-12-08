#pragma once

#include "game_object.hpp"
#include "game_state.hpp"
#include "window.hpp"

#include <memory>
#include <stack>
#include <string>

namespace core {

class Game : public GameObject {
public:
    Game(int fps = 30);
    virtual ~Game() = default;

public:
    void run();

protected:
    virtual void handle_inputs() override;
    virtual void render() override;

protected:
    void _push_state(GameStateRef state);
    void _pop_state();

protected:
    std::stack<GameStateRef> _states;
    bool _running;
    const size_t _frame_delay;
};

}  // namespace core