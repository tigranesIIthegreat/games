#include "game.hpp"

namespace core {

Game::Game(const std::string& title, int width, int height, int fps)
    : _window{std::make_shared<Window>(title, width, height)},
      _running{false},
      _frame_delay(1000.0f / fps) {}

void Game::run() {
    _running = true;
    size_t frame_start{};
    size_t frame_duration{};
    while (_running) {
        frame_start = SDL_GetTicks();
        handle_events();
        update();
        render();
        frame_duration = frame_start - SDL_GetTicks();
        if (frame_duration < _frame_delay) {
            SDL_Delay((int)(_frame_delay - frame_duration));
        }
    }
}

bool Game::running() const {
    return _running;
}

void Game::push_state(GameStateRef state) {
    _states.push(state);
    _states.top()->on_enter();
}

void Game::pop_state() {
    if (_states.empty()) {
        throw std::runtime_error("Cannot pop state from an empty FSM");
    }
    _states.top()->on_exit();
    _states.pop();
}

}  // namespace core