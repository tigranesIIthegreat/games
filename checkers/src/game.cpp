#include "game.hpp"

namespace checkers {

Game::Game() 
    : core::Game{"checkers", 512, 512} {
    _push_state(std::make_shared<PlayState>(_window));
}

void Game::handle_inputs() {
    core::Game::handle_inputs();
    // TODO: add state changing logic
}

} // namespace checkers