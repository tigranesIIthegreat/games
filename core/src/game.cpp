#include "game.hpp"

#include "vec.hpp"
#include "texture.hpp"

namespace core {

Game::Game(const std::string& title, int width, int height, int fps)
    : _window{std::make_shared<Window>(title, width, height)},
      _running{false},
      _frame_delay(1000.0f / fps) {}

void Game::run() {
    _running = true;
    size_t frame_start{};
    size_t frame_duration{};

    SDL_Event e;
    while (e.type != SDL_EVENT_QUIT) {
        frame_start = SDL_GetTicks();

        // handle_events();
        SDL_PollEvent(&e);
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

void Game::_push_state(GameStateRef state) {
    _states.push(state);
    _states.top()->on_enter();
}

void Game::_pop_state() {
    if (_states.empty()) {
        throw std::runtime_error("Cannot pop state from an empty FSM");
    }
    _states.top()->on_exit();
    _states.pop();
}

void Game::update() {
    _states.top()->update();
}

void Game::render() {
    SDL_RenderClear(_window->_sdl_renderer);
    SDL_SetRenderDrawColor(_window->_sdl_renderer, 0, 0, 0, 0);
    _states.top()->render();
    SDL_RenderPresent(_window->_sdl_renderer);
}

}  // namespace core