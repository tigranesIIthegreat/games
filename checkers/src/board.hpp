#pragma once

#include "cell.hpp"
#include "figure.hpp"
#include <array>
#include <memory>

namespace checkers {

using namespace core;

class Board : public Renderable {
public:
    Board(Rect position, TextureRef texture);

public:
    bool is_valid_position(size_t x, size_t y) const;
    CellRef at(size_t x, size_t y);
    static size_t size();

private:
    static constexpr size_t _size = 8;
};

using BoardRef = std::shared_ptr<Board>;

}  // namespace checkers