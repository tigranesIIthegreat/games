#pragma once

#include <core/movable.hpp>

#include <memory>

namespace checkers {

using namespace core;

enum class FigureColor { WHITE, BLACK };

class Figure : public Movable {
public:
    Figure(Vec2 coords, float width, float height, Texture& texture, 
           WindowRef window, Vec2 velocity, Vec2 acceleration, 
           FigureColor color, bool is_king);

    FigureColor color() const;
    bool is_king() const;
    bool is_high_from_board() const;

private:
    const FigureColor _color;
    const bool _is_king;
    bool _is_high_from_board;
};

using FigureRef = std::shared_ptr<Figure>;

} // namespace checkers