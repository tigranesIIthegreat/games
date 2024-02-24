#include "game.hpp"

namespace checkers {

Game::Game() : _window{std::make_shared<core::Window>("Checkers", 800, 600)} {}

void Game::run() {
  SDL_Event e;
  while (e.type != SDL_EVENT_QUIT) {
    SDL_PollEvent(&e);
  }
}

} // namespace checkers