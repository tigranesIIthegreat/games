#pragma once

#include "board.hpp"
#include "color.hpp"
#include "figure.hpp"
#include <core/game_state.hpp>
#include <core/window.hpp>
#include <vector>

namespace checkers {

enum class SelectionMode { SOURCE = 0, DESTINATION = 1 };

class PlayState : public core::GameState {
public:
    PlayState();

public:
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual std::string name() override;

private:
    void _fill_board_with_figures();
    void _switch_players();

protected:
    virtual void handle_inputs() override;

private:
    static constexpr size_t _figure_count = 24;

private:
    float _board_size;
    float _cell_size;
    std::vector<FigureRef> _white_figures;
    std::vector<FigureRef> _black_figures;
    Color _current_player;
    // SelectionMode _current_mode;
};

}  // namespace checkers