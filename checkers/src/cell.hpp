#pragma once

#include "figure.hpp"
#include <core/renderable.hpp>
#include <core/texture.hpp>
#include <optional>

namespace checkers {

struct Cell : public core::Renderable {
    Cell(core::Rect position = {}, std::optional<FigureRef> figure = nullptr);
    std::optional<FigureRef> figure;

private:
    static core::TextureRef _green_texture;
};

} // namespace checkers