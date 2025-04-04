#include <checkers/game.hpp>

#include <iostream>

int main() {
    try {
        checkers::Game game{};
        game.run();
    } catch (...) {
        std::cout << "unknown exception in games" << std::endl;
    }
}