#pragma once

#include <array>
#include <unordered_map>

#include <SDL3/SDL.h>

namespace core {

class Inputable {};

enum class KeyboardKey { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 2, SPACE = 4 };

class KeyboardInputable : public Inputable {
public:
    KeyboardInputable();

public:
    bool is_key_down(KeyboardKey key) const;
    virtual void update_inputs();

private:
    const uint8_t* _keyboard_state;

private:
    using KeyMapping = std::unordered_map<KeyboardKey, SDL_Scancode>;
    static KeyMapping _mapping;
};

} // namespace core