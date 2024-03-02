#include "figure.hpp"

namespace checkers {

Figure::Figure(Vec2 coords, float width, float height, Texture& texture,
               WindowRef window, Vec2 velocity, Vec2 acceleration,
               FigureColor color, bool is_king)
    : Movable{coords, width, height, texture, window, velocity, acceleration}
    , _color{color}
    , _is_king{is_king}
    , _is_high_from_board{false} {}

FigureColor Figure::color() const {
    return _color;
}

bool Figure::is_king() const {
    return _is_king;
}
bool Figure::is_high_from_board() const {
    return _is_high_from_board;
}

} // namespace checkers