#pragma once

#include "game_object.hpp"
#include "window.hpp"

#include <memory>
#include <string>

namespace core {

class GameState : public GameObject {
public:
    GameState();
    virtual ~GameState() = default;
    virtual void handle_inputs() override;

public:
    virtual void on_enter() = 0;
    virtual void on_exit() = 0;
    virtual std::string name() = 0;
};

using GameStateRef = std::shared_ptr<GameState>;

}  // namespace core