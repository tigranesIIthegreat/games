#include "king.hpp"
#include "board.hpp"

namespace checkers {

King::King(core::Coords coords, int size, Color color, BoardRef board)
    : Figure(coords, size, color, board) {
    _texture = (color == Color::WHITE) ? _white_king_texture : _black_king_texture;
}

std::vector<CellRef> King::valid_destinations() const {
    auto step = _color == Color::WHITE ? 1 : -1;
    std::vector<CellRef> result{};
    int x = _position[1] / _position[3];
    int y = _position[0] / _position[2];

    // TODO: use array to avoid code duplication

    // consider up-left direction
    if (_board->is_valid_position(x + step, y - 1)) {
        if (_board->at(x + step, y - 1)->figure() == nullptr) {
            result.push_back(_board->at(x + step, y - 1));
        } else if (_board->is_valid_position(x + 2 * step, y - 2) &&
                   _board->at(x + 2 * step, y - 2)->figure() == nullptr &&
                   _board->at(x + step, y - 1)->figure()->color() != _color) {
            result.push_back(_board->at(x + 2 * step, y - 2));
        }
    }

    // consider up-right direction
    if (_board->is_valid_position(x + step, y + 1)) {
        if (_board->at(x + step, y + 1)->figure() == nullptr) {
            result.push_back(_board->at(x + step, y + 1));
        } else if (_board->is_valid_position(x + 2 * step, y + 2) &&
                   _board->at(x + 2 * step, y + 2)->figure() == nullptr &&
                   _board->at(x + step, y + 1)->figure()->color() != _color) {
            result.push_back(_board->at(x + 2 * step, y + 2));
        }
    }

    // consider down-left direction
    if (_board->is_valid_position(x - step, y - 1)) {
        if (_board->at(x - step, y - 1)->figure() == nullptr) {
            result.push_back(_board->at(x - step, y - 1));
        } else if (_board->is_valid_position(x - 2 * step, y - 2) &&
                   _board->at(x - 2 * step, y - 2)->figure() == nullptr &&
                   _board->at(x - step, y - 1)->figure()->color() != _color) {
            result.push_back(_board->at(x - 2 * step, y - 2));
        }
    }

    // consider down-right direction
    if (_board->is_valid_position(x - step, y + 1)) {
        if (_board->at(x - step, y + 1)->figure() == nullptr) {
            result.push_back(_board->at(x - step, y + 1));
        } else if (_board->is_valid_position(x - 2 * step, y + 2) &&
                   _board->at(x - 2 * step, y + 2)->figure() == nullptr &&
                   _board->at(x - step, y + 1)->figure()->color() != _color) {
            result.push_back(_board->at(x - 2 * step, y + 2));
        }
    }
    return result;
}

core::TextureRef King::_white_king_texture =
    std::make_shared<core::Texture>("king_white");

core::TextureRef King::_black_king_texture =
    std::make_shared<core::Texture>("king_black");

}  // namespace checkers