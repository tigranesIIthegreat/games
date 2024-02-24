#include <game/window.hpp>

#include <memory>

namespace checkers {

class Game {
public:
    Game();
    void run();
private:
    std::shared_ptr<sdl::Window> _window;
};

} // namespace checkers