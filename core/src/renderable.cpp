#include "renderable.hpp"

namespace core {

Renderable::Renderable(Rect coords, Texture& texture, WindowRef window) 
    : _coords{coords}
    , _texture{texture}
    , _window{window} {}

void Renderable::update_texture() {
    _texture.update();
}

void Renderable::render() {
    _texture.render(_coords);
}

}  // namespace core