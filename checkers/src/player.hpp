#pragma once

#include "figure.hpp"

#include <vector>

namespace checkers {

class Player {
public:
    Player(const std::vector<FigureRef>& figures, FigureColor color);
    virtual ~Player() = default;

private:
    std::vector<FigureRef> _figures;
    FigureColor _color;
};

} // namespace checkers