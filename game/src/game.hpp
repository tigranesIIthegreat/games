#include <game/window.hpp>

namespace checkers {

class Game {
public:
    Game();
    void run();
private:
    sdl::Window _window;
};

} // namespace checkers