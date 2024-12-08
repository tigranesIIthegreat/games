#pragma once

#include <array>
#include <core/game_object.hpp>
#include <memory>
#include "cell.hpp"
#include "figure.hpp"

namespace checkers {

using namespace core;

class Board : public GameObject {
public:
    Board(Rect position, TextureRef texture);
    virtual void handle_inputs() override;

public:
    bool is_valid_position(size_t x, size_t y) const;
    CellRef at(size_t x, size_t y);
    static size_t size();

private:
    static constexpr size_t _size = 8;
};

using BoardRef = std::shared_ptr<Board>;

}  // namespace checkers