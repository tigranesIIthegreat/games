#pragma once

#include "figure.hpp"

#include <memory>
#include <vector>

namespace checkers {

class Player {
public:
    Player(const std::vector<FigureRef>& figures);
    virtual ~Player() = default;

public:
    void play();

private:
    std::vector<FigureRef> _figures;
};

using PlayerRef = std::shared_ptr<Player>;

} // namespace checkers