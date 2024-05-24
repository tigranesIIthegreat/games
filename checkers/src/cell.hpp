#pragma once

#include "figure.hpp"
#include <optional>

namespace checkers {

struct Cell {
    std::optional<FigureRef> figure;
};

} // namespace checkers