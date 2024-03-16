#include "input.hpp"

#include <algorithm>

namespace core::input {

void InputDevice::update() {
    SDL_PumpEvents();
}

void Keyboard::update() {
    InputDevice::update();
    _keyboard_state = SDL_GetKeyboardState(nullptr);
}

bool Keyboard::is_key_down(Key key) const {
    return _keyboard_state[_key_mapping[key]] == 1;
}

Keyboard::KeyMapping Keyboard::_key_mapping = {
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
    {Key::Z, SDL_SCANCODE_Z}
};

} // namespace core::input