#pragma once

#include "vec.hpp"

#include <array>
#include <memory>
#include <unordered_map>

#include <SDL3/SDL.h>

namespace core::input {

enum class MouseButton;
enum class Key;

class Inputable {
private:
    virtual void _handle_inputs() = 0;
};

class InputManager {
public:
    InputManager();
    void update();

public:
    bool is_down(Key key) const;
    bool is_down(MouseButton button) const;
    Vec2 mouse_position() const;
    bool need_to_quit() const;

private:
    void _update_quitting_necessity();
    void _update_mouse_state();
    void _update_keyboard_state();

private:
    using KeyMapping = std::unordered_map<Key, SDL_Scancode>;
    static KeyMapping _key_mapping;
    std::array<bool, 3> _mouse_button_states;
    Vec2 _mouse_position;
    const uint8_t* _keyboard_states;
    SDL_Event _event;
    bool _need_to_quit;
};

enum class MouseButton { LEFT, MIDDLE, RIGHT };

enum class Key {
    UNKNOWN, UP, DOWN, LEFT, RIGHT,
    RETURN, ESCAPE, BACKSPACE, TAB, SPACE,
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};

using InputManagerRef = std::shared_ptr<InputManager>;

} // namespace core::input