#include "renderable.hpp"

namespace core {

Renderable::Renderable(Vec2 coords, float width, float height, Texture& texture, WindowRef window) 
    : _coords{coords}
    , _width{width}
    , _height{height}
    , _texture{texture}
    , _window{window} {}

void Renderable::update() {
    _texture.update();
}

void Renderable::render() {
    _texture.render(_coords, _width, _height);
}

}  // namespace core