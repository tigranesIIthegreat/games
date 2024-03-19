#include "game_state.hpp"

namespace core {

GameState::GameState(WindowRef window, input::InputManagerRef input_manager)
    : _window{window} 
    , _input_manager{input_manager} {}

} // namespace core