#pragma once

#include "figure.hpp"

namespace checkers {

class Man : public Figure {
public:
    Man(core::Coords, int size, Color color, BoardRef board);
    std::vector<CellRef> valid_destinations() const override;

private:
    static core::TextureRef _white_man_texture;
    static core::TextureRef _black_man_texture;
};

} // namesapce checkers