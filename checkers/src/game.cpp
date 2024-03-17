#include "game.hpp"

namespace checkers {

Game::Game() 
    : core::Game{"checkers", 512, 512}
    , _play_state{_window} {
    _push_state(std::make_shared<PlayState>(_window));
}

void Game::_handle_inputs() {
    core::Game::_handle_inputs();
    // TODO: add state changing logic
}

} // namespace checkers