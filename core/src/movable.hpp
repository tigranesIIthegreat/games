#pragma once

#include "renderable.hpp"
#include "vec.hpp"

namespace core {

class Movable : public Renderable {
public:
    Movable(Vec2 coords, float width, float height, Texture& texture,
            WindowRef window, Vec2 velocity, Vec2 acceleration);

public:
    virtual void update_coords() override;

protected:
    Vec2 _velocity;
    Vec2 _acceleration;
};

}  // namespace core