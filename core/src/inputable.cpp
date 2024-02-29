#include "inputable.hpp"

#include <algorithm>

namespace core {

KeyboardInputable::KeyMapping KeyboardInputable::_mapping = {
    {KeyboardKey::UNKNOWN, SDL_SCANCODE_UNKNOWN},
    {KeyboardKey::UP, SDL_SCANCODE_UP},
    {KeyboardKey::DOWN, SDL_SCANCODE_DOWN},
    {KeyboardKey::LEFT, SDL_SCANCODE_LEFT},
    {KeyboardKey::RIGHT, SDL_SCANCODE_RIGHT},
    {KeyboardKey::RETURN, SDL_SCANCODE_RETURN},
    {KeyboardKey::ESCAPE, SDL_SCANCODE_ESCAPE},
    {KeyboardKey::BACKSPACE, SDL_SCANCODE_BACKSPACE},
    {KeyboardKey::TAB, SDL_SCANCODE_TAB},
    {KeyboardKey::A, SDL_SCANCODE_A},
    {KeyboardKey::B, SDL_SCANCODE_B},
    {KeyboardKey::B, SDL_SCANCODE_C},
    {KeyboardKey::D, SDL_SCANCODE_D},
    {KeyboardKey::E, SDL_SCANCODE_E},
    {KeyboardKey::F, SDL_SCANCODE_F},
    {KeyboardKey::G, SDL_SCANCODE_G},
    {KeyboardKey::H, SDL_SCANCODE_H},
    {KeyboardKey::I, SDL_SCANCODE_I},
    {KeyboardKey::J, SDL_SCANCODE_J},
    {KeyboardKey::K, SDL_SCANCODE_K},
    {KeyboardKey::L, SDL_SCANCODE_L},
    {KeyboardKey::M, SDL_SCANCODE_M},
    {KeyboardKey::N, SDL_SCANCODE_N},
    {KeyboardKey::O, SDL_SCANCODE_O},
    {KeyboardKey::P, SDL_SCANCODE_P},
    {KeyboardKey::Q, SDL_SCANCODE_Q},
    {KeyboardKey::R, SDL_SCANCODE_R},
    {KeyboardKey::S, SDL_SCANCODE_S},
    {KeyboardKey::T, SDL_SCANCODE_T},
    {KeyboardKey::U, SDL_SCANCODE_U},
    {KeyboardKey::V, SDL_SCANCODE_V},
    {KeyboardKey::W, SDL_SCANCODE_W},
    {KeyboardKey::X, SDL_SCANCODE_X},
    {KeyboardKey::Y, SDL_SCANCODE_Y},
    {KeyboardKey::Z, SDL_SCANCODE_Z}

};

void KeyboardInputable::update_inputs() {
    SDL_PumpEvents();
    _keyboard_state = SDL_GetKeyboardState(nullptr);
}

KeyboardInputable::KeyboardInputable() {
    update_inputs();
}

bool KeyboardInputable::is_key_down(KeyboardKey key) const {
    return _keyboard_state[_mapping[key]] == 1;
}

} // namespace core