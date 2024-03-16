#pragma once

#include <array>
#include <unordered_map>

#include <SDL3/SDL.h>

namespace core::input {

enum class Key;

class Inputable {
public:
    virtual void handle_inputs() = 0;
};

class InputDevice {
public:
    virtual ~InputDevice() = 0;
    virtual void update();
};

class Mouse : public InputDevice {
public:
    virtual void update() override;
};

class Keyboard : public InputDevice {
public:
    bool is_key_down(Key key) const;
    virtual void update() override;

private:
    using KeyMapping = std::unordered_map<Key, SDL_Scancode>;
    const uint8_t* _keyboard_state;
    static KeyMapping _key_mapping;
};

enum class Key {
    UNKNOWN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    RETURN,
    ESCAPE,
    BACKSPACE,
    TAB,
    SPACE,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z
};

} // namespace core::input