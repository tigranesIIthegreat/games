#include <emscripten/emscripten.h>
#include <checkers/game.hpp>
#include <core/window.hpp>

checkers::Game game = checkers::Game();

void main_loop() {
    game.run();
}

int main(int, char**) {
    core::Window& window = core::Window::instance();
    emscripten_set_main_loop(main_loop, -1, 1);
}