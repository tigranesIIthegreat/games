#include "game.hpp"

namespace checkers {

Game::Game() 
    : core::Game{"checkers", 800, 800}
    , _play_state{_window} {
    _push_state(std::make_shared<PlayState>(_window));
}

} // namespace checkers