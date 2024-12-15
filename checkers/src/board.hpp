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

class Board : public GameObject {
public:
    Board(Rect position, TextureRef texture);
    virtual void handle_inputs() override;

public:
    void move(CellRef src, CellRef dst);
    bool is_valid_position(size_t x, size_t y) const;
    CellRef at(size_t x, size_t y);
    static size_t size();

private:
    void switch_players();
    void switch_selection_modes();

private:
    float _cell_size{};
    Color _current_player;
    SelectionMode _current_selection;
    CellRef _selected_source{};

private:
    static constexpr size_t _size = 8;
};

using BoardRef = std::shared_ptr<Board>;

}  // namespace checkers