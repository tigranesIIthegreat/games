#pragma once

#include "figure.hpp"

#include <array>
#include <memory>
#include <optional>

namespace checkers {

using namespace core;

class Board : public Renderable {
public:
    Board(Vec2 coords, float width, float height, Texture& texture,
          WindowRef window);

public:
    virtual void update() override;
    virtual void render() override;

public:
    bool is_valid_position(size_t x, size_t y) const;
    std::optional<FigureRef> at(size_t x, size_t y);
    size_t size() const;

private:
    static constexpr size_t _size = 8;
    using Cells = std::array<std::array<std::optional<FigureRef>, _size>, _size>;
    Cells _cells;
};

using BoardRef = std::shared_ptr<Board>;

} // namespace checkers