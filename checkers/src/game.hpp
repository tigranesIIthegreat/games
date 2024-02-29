#pragma once

#include <core/game.hpp>
#include <core/inputable.hpp>

namespace checkers {

class Game : public core::Game, public core::KeyboardInputable {};


} // namespace checkers