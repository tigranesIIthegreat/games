#include "cell.hpp"

namespace checkers {

core::TextureRef Cell::_green25_texture =
    std::make_shared<core::Texture>("green25");

core::TextureRef Cell::_green50_texture =
    std::make_shared<core::Texture>("green50");

Cell::Cell(core::Rect position, FigureRef figure)
    : core::InteractiveRenderable(position, nullptr) {
    _components.push_back(figure);
}

FigureRef Cell::figure() {
    return std::static_pointer_cast<Figure>(_components[0]);
}

void Cell::set_figure(FigureRef figure) {
    _components[0] = figure;
}

void Cell::handle_inputs() {
    // TODO: add proper input handling
    auto& input_manager = core::input::InputManager::get_instance();
    bool mouse_clicked = input_manager.is_clicked(core::input::MouseButton::LEFT);
    bool a_is_pressed = input_manager.is_pressed(core::input::Key::A);
    if (mouse_hovers_over() && (mouse_clicked || a_is_pressed)) {
        _texture = _texture ? nullptr : _green50_texture;
    }
}

}  // namespace checkers