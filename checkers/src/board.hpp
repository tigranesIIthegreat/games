#pragma once

#include "figure.hpp"
#include <array>
#include <optional>

namespace checkers {

using namespace core;

class Board : public Renderable {
public:
    static constexpr size_t size = 8;
    static constexpr size_t figure_count = 24;

public:
    // figures are expected in the following order:
    // 12 white then 12 black figures
    Board(const std::array<FigureRef, figure_count>& figures);

public:
    bool is_valid_position(size_t x, size_t y) const;

private:
    void fill_with_figures(const std::array<FigureRef, figure_count>& figures);

private:
    using Figures = std::array<std::array<std::optional<FigureRef>, size>, size>;
    Figures _figures;
};

} // namespace checkers