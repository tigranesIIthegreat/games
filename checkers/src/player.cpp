#include "player.hpp"
#include <iostream> // TODO: remove

namespace checkers {

Player::Player(const std::string& name, const std::vector<FigureRef>& figures)
    : _name{name}
    , _figures{figures} {}

void Player::play() {
    // TODO: play logic
}

} // namespace checkers