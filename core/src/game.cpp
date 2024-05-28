#include "game.hpp"

#include "texture.hpp"
#include "vec.hpp"

namespace core {

Game::Game(int fps)
    : _running{false}
    , _frame_delay(1000.0f / fps) {}

void Game::run() {
    _running = true;
    size_t frame_start{};
    size_t frame_duration{};

    while (_running) {
        frame_start = SDL_GetTicks();

        handle_inputs();
        _one_iteration();
        // _update();
        input::InputManager::get_instance().update();
        _render();

        frame_duration = frame_start - SDL_GetTicks();
        if (frame_duration < _frame_delay) {
            SDL_Delay(static_cast<int>(_frame_delay - frame_duration));
        }
    }
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

void Game::handle_inputs() {
    if (input::InputManager::get_instance().need_to_quit()) {
        _running = false;
    }
    // TODO: additional input handling
    _states.top()->handle_inputs();
}

void Game::_one_iteration() {
    _states.top()->run();
}

void Game::_update() {
    input::InputManager::get_instance().update();
}

void Game::_render() {
    decltype(auto) renderer = Window::get_instance().sdl_renderer();
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    _states.top()->render();
    SDL_RenderPresent(renderer);
}

}  // namespace core