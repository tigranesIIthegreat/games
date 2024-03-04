#pragma once

#include <memory>

namespace checkers {

class Player {};

using PlayerRef = std::shared_ptr<Player>;

} // namespace checkers