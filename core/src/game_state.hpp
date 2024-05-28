#pragma once

#include "input.hpp"
#include "renderable.hpp"
#include "window.hpp"

#include <memory>
#include <string>

namespace core {

class GameState : public Renderable, public input::Interactive {
public:
    GameState();
    virtual ~GameState() = default;

public:
    virtual void run() = 0;
    virtual void on_enter() = 0;
    virtual void on_exit() = 0;
    virtual std::string name() = 0;
};

using GameStateRef = std::shared_ptr<GameState>;

}  // namespace core