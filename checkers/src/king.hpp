#pragma once

#include "figure.hpp"

namespace checkers {

class King : public Figure {
public:
    King(core::Coords, int size, Color color, BoardRef board);
    std::vector<CellRef> valid_destinations() const override;

private:
    static core::TextureRef _white_king_texture;
    static core::TextureRef _black_king_texture;
};

}  // namespace checkers