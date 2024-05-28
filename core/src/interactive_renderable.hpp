#pragma once

#include "input.hpp"
#include "renderable.hpp"

namespace core {

class InteractiveRenderable : public input::Interactive, public Renderable {
public:
    InteractiveRenderable() = default;
    InteractiveRenderable(Rect position, TextureRef texture);
};

} // namespace core