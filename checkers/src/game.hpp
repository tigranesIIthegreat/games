#pragma once

#include "play_state.hpp"

#include <core/game.hpp>
#include <core/inputable.hpp>

namespace checkers {

class Game : public core::Game {
public:
    Game();

private:
    PlayState _play_state;
};

} // namespace checkers