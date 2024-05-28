#include "interactive_renderable.hpp"

namespace core {

InteractiveRenderable::InteractiveRenderable(Rect position, TextureRef texture)
    : Interactive{}
    , Renderable{position, texture} {}

} // namespace core