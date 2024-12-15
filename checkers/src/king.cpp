#include "king.hpp"

namespace checkers {

King::King(core::Coords coords, int size, Color color, BoardRef board)
    : Figure(coords, size, color, board) {
    _texture = (color == Color::WHITE) ? _white_king_texture : _black_king_texture;
}

core::TextureRef King::_white_king_texture =
    std::make_shared<core::Texture>("king_white");

core::TextureRef King::_black_king_texture =
    std::make_shared<core::Texture>("king_black");

}  // namespace checkers