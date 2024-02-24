#include <game/window.hpp>

namespace checkers {

class Game {
public:
  Game();
  void run();

private:
  core::WindowRef _window;
};

} // namespace checkers