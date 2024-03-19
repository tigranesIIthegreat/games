#include "game.hpp"

namespace checkers {

Game::Game() 
    : core::Game{"checkers", 512, 512} {
    _push_state(std::make_shared<PlayState>(_window, _input_manager));
}

void Game::_handle_inputs() {
    core::Game::_handle_inputs();
    // TODO: add state changing logic
}

} // namespace checkers