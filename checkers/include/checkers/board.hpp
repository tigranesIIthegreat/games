#pragma once

#include <array>
#include <core/game_object.hpp>
#include <memory>
#include "cell.hpp"
#include "color.hpp"
#include "figure.hpp"

namespace checkers {

using namespace core;

enum class SelectionMode { SOURCE = 0, DESTINATION = 1 };

class Board : public GameObject, public std::enable_shared_from_this<Board> {
public:
    Board(Rect position, TextureRef texture);
    virtual void handle_inputs() override;

public:
    void move(CellRef src, CellRef dst);
    bool is_valid_position(int x, int y) const;
    CellRef at(int x, int y);
    int cell_size() const;
    static int size();

private:
    int _cell_size{};

private:
    static constexpr int _size = 8;
};

using BoardRef = std::shared_ptr<Board>;

}  // namespace checkers