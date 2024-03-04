#include <checkers/play_state.hpp>

int main() {
    auto window = std::make_shared<core::Window>("checkers_demo", 800, 800);
    checkers::PlayState play_state{window};
}