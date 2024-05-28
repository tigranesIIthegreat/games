#pragma once

#include "vec.hpp"

#include <array>
#include <memory>
#include <unordered_map>

#include <SDL3/SDL.h>

namespace core::input {

enum class MouseButton;
enum class Key;

class InputManager {
public:
    static InputManager& get_instance();
    void update();

public:
    bool is_down(Key key) const;
    bool is_down(MouseButton button) const;
    Point mouse_position() const;
    bool need_to_quit() const;

private:
    void _update_quitting_necessity();
    void _update_mouse_state();
    void _update_keyboard_state();

private:
    InputManager();

private:
    using KeyMapping = std::unordered_map<Key, SDL_Scancode>;
    static KeyMapping _key_mapping;
    std::array<bool, 3> _mouse_states;
    Point _mouse_position;
    const uint8_t* _keyboard_states;
    SDL_Event _event;
    bool _need_to_quit;
};

using InputManagerRef = std::shared_ptr<InputManager>;

class Interactive {
public:
    virtual void handle_inputs() = 0;
};

enum class MouseButton { LEFT, MIDDLE, RIGHT };

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

}  // namespace core::input