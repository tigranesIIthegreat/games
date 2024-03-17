#pragma once

#include "play_state.hpp"

#include <core/game.hpp>
#include <core/input.hpp>

namespace checkers {

class Game : public core::Game {
public:
    Game();

public:
    virtual void handle_inputs() override;

private:
    PlayState _play_state;
};

} // namespace checkers