#include "renderable.hpp"

namespace core {

Renderable::Renderable(Vec2 coords, float width, float height, TextureRef texture, WindowRef window) 
    : _coords{coords}
    , _width{width}
    , _height{height}
    , _texture{texture}
    , _window{window} {}

void Renderable::update() {
    _texture->update();
}

void Renderable::render() {
    _texture->render(_coords, _width, _height);
}

void Renderable::set_coords(Vec2 coords) {
    _coords = coords;
}
Vec2 Renderable::coords() const {
    return _coords;
}

}  // namespace core