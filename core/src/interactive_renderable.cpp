#include "interactive_renderable.hpp"

namespace core {

InteractiveRenderable::InteractiveRenderable(Rect position, TextureRef texture)
    : Interactive{}
    , Renderable{position, texture} {}

bool InteractiveRenderable::mouse_hovers() const {
    auto mouse_position = core::input::InputManager::get_instance().mouse_position();
    return _position[0] <= mouse_position[0] and
           mouse_position[0] <= _position[0] + _position[2] and
           _position[1] <= mouse_position[1] and
           mouse_position[1] <= _position[1] + _position[3];
}

} // namespace core