#pragma once

#include <core/movable.hpp>

#include <memory>

namespace checkers {

enum class FigureColor { WHITE, BLACK };

class Figure : public core::Renderable {
public:
    Figure(core::Vec2 coords, float width, float height, core::TextureRef texture, 
           core::WindowRef window, FigureColor color, bool is_king);

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