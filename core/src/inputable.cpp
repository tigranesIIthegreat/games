#include "inputable.hpp"

#include <algorithm>

namespace core {

KeyboardInputable::KeyMapping KeyboardInputable::_mapping = {
    {KeyboardKey::UP, SDL_SCANCODE_UP},
    {KeyboardKey::DOWN, SDL_SCANCODE_DOWN},
    {KeyboardKey::LEFT, SDL_SCANCODE_LEFT},
    {KeyboardKey::RIGHT, SDL_SCANCODE_RIGHT},
    {KeyboardKey::SPACE, SDL_SCANCODE_SPACE}
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