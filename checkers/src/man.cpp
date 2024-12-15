#include "man.hpp"
#include "board.hpp"

#include <iostream>

namespace checkers {

Man::Man(core::Coords coords, int size, Color color, BoardRef board)
    : Figure(coords, size, color, board) {
    _texture = (color == Color::WHITE) ? _white_man_texture : _black_man_texture;
}

std::vector<CellRef> Man::valid_destinations() const {
    auto step = _color == Color::WHITE ? 1 : -1;
    std::vector<CellRef> result{};
    int x = _position[1] / _position[3];
    int y = _position[0] / _position[2];

    // consider up-left direction
    if (_board->is_valid_position(x + step, y - 1)) {
        if (_board->at(x + step, y - 1)->figure() == nullptr) {
            std::cout << x + step << y - 1 << std::endl;
            result.push_back(_board->at(x + step, y - 1));
        } else if (_board->is_valid_position(x + 2 * step, y - 2) &&
                   _board->at(x + 2 * step, y - 2)->figure() == nullptr &&
                   _board->at(x + step, y - 1)->figure()->color() != _color) {
            std::cout << x + 2 * step << y - 2 << std::endl;
            result.push_back(_board->at(x + 2 * step, y - 2));
        }
    }

    // consider up-right direction
    if (_board->is_valid_position(x + step, y + 1)) {
        if (_board->at(x + step, y + 1)->figure() == nullptr) {
            std::cout << x + step << y + 1 << std::endl;
            result.push_back(_board->at(x + step, y + 1));
        } else if (_board->is_valid_position(x + 2 * step, y + 2) &&
                   _board->at(x + 2 * step, y + 2)->figure() == nullptr &&
                   _board->at(x + step, y + 1)->figure()->color() != _color) {
            std::cout << x + 2 * step << y + 2 << std::endl;
            result.push_back(_board->at(x + 2 * step, y + 2));
        }
    }
    std::cout << "size : " << result.size();
    return result;
}

core::TextureRef Man::_white_man_texture =
    std::make_shared<core::Texture>("man_white");

core::TextureRef Man::_black_man_texture =
    std::make_shared<core::Texture>("man_black");

} // namespace checkers