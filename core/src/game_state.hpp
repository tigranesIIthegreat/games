#pragma once

#include <memory>
#include <string>

namespace core {

class GameState {
public:
    virtual ~GameState() = default;
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void on_enter() = 0;
    virtual void on_exit() = 0;
    virtual std::string name() = 0;
};

using GameStateRef = std::shared_ptr<GameState>;

} // namespace core