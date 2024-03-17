#pragma once

#include "play_state.hpp"

#include <core/game.hpp>
#include <core/input.hpp>

namespace checkers {

class Game : public core::Game {
public:
    Game();

private:
    virtual void _handle_inputs() override;
    virtual void _one_iteration() override;

private:
    PlayState _play_state;
};

} // namespace checkers