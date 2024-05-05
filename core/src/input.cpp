#include "input.hpp"

#include <algorithm>

namespace core::input {

InputManager::InputManager() {
    std::fill(std::begin(_mouse_button_states), std::end(_mouse_button_states),
              false);
    update();
}

void InputManager::update() {
    SDL_PollEvent(&_event);
    SDL_PumpEvents();

    _update_quitting_necessity();
    _update_mouse_state();
    _update_keyboard_state();
}

bool InputManager::is_down(Key key) const {
    return _keyboard_states[_key_mapping[key]] == 1;
}

bool InputManager::is_down(MouseButton button) const {
    return _mouse_button_states[static_cast<size_t>(button)];
}

Point InputManager::mouse_position() const {
    return _mouse_position;
}

bool InputManager::need_to_quit() const {
    return _need_to_quit;
}

void InputManager::_update_quitting_necessity() {
    _need_to_quit = _event.type == SDL_EVENT_QUIT;
}

void InputManager::_update_mouse_state() {
    if (_event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        _mouse_button_states[_event.button.button - 1] = true;
    } else if (_event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        _mouse_button_states[_event.button.button - 1] = false;
    } else if (_event.type == SDL_EVENT_MOUSE_MOTION) {
        _mouse_position = {_event.motion.x, _event.motion.y};
    }
}

void InputManager::_update_keyboard_state() {
    _keyboard_states = SDL_GetKeyboardState(nullptr);
}

InputManager::KeyMapping InputManager::_key_mapping = {
    {Key::UNKNOWN, SDL_SCANCODE_UNKNOWN},
    {Key::UP, SDL_SCANCODE_UP},
    {Key::DOWN, SDL_SCANCODE_DOWN},
    {Key::LEFT, SDL_SCANCODE_LEFT},
    {Key::RIGHT, SDL_SCANCODE_RIGHT},
    {Key::RETURN, SDL_SCANCODE_RETURN},
    {Key::ESCAPE, SDL_SCANCODE_ESCAPE},
    {Key::BACKSPACE, SDL_SCANCODE_BACKSPACE},
    {Key::TAB, SDL_SCANCODE_TAB},
    {Key::A, SDL_SCANCODE_A},
    {Key::B, SDL_SCANCODE_B},
    {Key::B, SDL_SCANCODE_C},
    {Key::D, SDL_SCANCODE_D},
    {Key::E, SDL_SCANCODE_E},
    {Key::F, SDL_SCANCODE_F},
    {Key::G, SDL_SCANCODE_G},
    {Key::H, SDL_SCANCODE_H},
    {Key::I, SDL_SCANCODE_I},
    {Key::J, SDL_SCANCODE_J},
    {Key::K, SDL_SCANCODE_K},
    {Key::L, SDL_SCANCODE_L},
    {Key::M, SDL_SCANCODE_M},
    {Key::N, SDL_SCANCODE_N},
    {Key::O, SDL_SCANCODE_O},
    {Key::P, SDL_SCANCODE_P},
    {Key::Q, SDL_SCANCODE_Q},
    {Key::R, SDL_SCANCODE_R},
    {Key::S, SDL_SCANCODE_S},
    {Key::T, SDL_SCANCODE_T},
    {Key::U, SDL_SCANCODE_U},
    {Key::V, SDL_SCANCODE_V},
    {Key::W, SDL_SCANCODE_W},
    {Key::X, SDL_SCANCODE_X},
    {Key::Y, SDL_SCANCODE_Y},
    {Key::Z, SDL_SCANCODE_Z}};

}  // namespace core::input