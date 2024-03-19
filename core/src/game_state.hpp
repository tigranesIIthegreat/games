#pragma once

#include "input.hpp"
#include "window.hpp"

#include <memory>
#include <string>

namespace core {

class GameState : public input::Inputable {
public:
    GameState(WindowRef _window, input::InputManagerRef input_manager);
    virtual ~GameState() = default;

public:
    virtual void one_iteration() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void on_enter() = 0;
    virtual void on_exit() = 0;
    virtual std::string name() = 0;
    
protected:
    WindowRef _window;
    input::InputManagerRef _input_manager;
};

using GameStateRef = std::shared_ptr<GameState>;

} // namespace core