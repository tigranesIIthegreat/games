#pragma once

#include "figure.hpp"

#include <array>
#include <memory>
#include <optional>

namespace checkers {

using namespace core;

class Board : public Renderable {
public:
    bool is_valid_position(size_t x, size_t y) const;
    std::optional<FigureRef> at(size_t x, size_t y);
    constexpr size_t size() const;

private:
    static constexpr size_t _size = 8;
    using Cells = std::array<std::array<std::optional<FigureRef>, _size>, _size>;
    Cells _cells;
};

using BoardRef = std::shared_ptr<Board>;

} // namespace checkers