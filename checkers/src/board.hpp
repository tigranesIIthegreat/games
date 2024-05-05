#pragma once

#include "figure.hpp"

#include <array>
#include <memory>
#include <optional>

namespace checkers {

using namespace core;

class Board : public Renderable {
public:
    Board(Rect position, TextureRef texture, WindowRef window);

public:
    virtual void update() override;
    virtual void render() override;

public:
    bool is_valid_position(size_t x, size_t y) const;
    std::optional<FigureRef>& at(size_t x, size_t y);
    size_t side_cell_count() const;

private:
    static constexpr size_t _side_cell_count = 8;
    using Cells =
        std::array<std::array<std::optional<FigureRef>, _side_cell_count>,
                   _side_cell_count>;
    Cells _cells;
};

using BoardRef = std::shared_ptr<Board>;

}  // namespace checkers