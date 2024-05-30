#pragma once

#include "input.hpp"
#include "renderable.hpp"

namespace core {

class InteractiveRenderable : public input::Interactive, public Renderable {
public:
    InteractiveRenderable() = default;
    InteractiveRenderable(Rect position, TextureRef texture);

    bool mouse_hovers_over() const;
};

} // namespace core