#pragma once

#include "renderable.hpp"
#include "vec.hpp"

namespace core {

class Movable : public Renderable {
public:
    Movable(Rect position, TextureRef texture, WindowRef window, Point velocity, Point acceleration);

public:
    virtual void update() override;

protected:
    Point _velocity;
    Point _acceleration;
};

}  // namespace core