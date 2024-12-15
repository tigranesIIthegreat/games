#pragma once

#include <core/game_object.hpp>
#include <memory>
#include "color.hpp"

namespace checkers {

class Figure : public core::GameObject {
public:
    Figure(core::Coords coords, int size, Color color);

    Color color() const;
    core::Coords coords() const;
    void set_coords(core::Coords cords);

private:
    const Color _color;

private:
    static core::TextureRef _white_man_texture;
    static core::TextureRef _black_man_texture;
    static core::TextureRef _white_king_texture;
    static core::TextureRef _black_king_texture;
};

using FigureRef = std::shared_ptr<Figure>;

}  // namespace checkers