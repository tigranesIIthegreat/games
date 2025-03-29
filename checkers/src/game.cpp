#include <checkers/game.hpp>

namespace checkers {

Game::Game() {
    _push_state(std::make_shared<PlayState>());
}

void Game::handle_inputs() {
    core::Game::handle_inputs();
    // TODO: add state changing logic
}

} // namespace checkers