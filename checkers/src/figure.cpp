#include "figure.hpp"

namespace checkers {

Figure::Figure(core::Vec2 coords, float width, float height,
               core::TextureRef texture, core::WindowRef window,
               core::input::InputManagerRef input_manager,
               FigureColor color, bool is_king)
    : Renderable{coords, width, height, texture, window}
    , _input_manager{input_manager}
    , _color{color}
    , _is_king{is_king}
    , _is_selected{false} {}

FigureColor Figure::color() const {
    return _color;
}

bool Figure::is_king() const {
    return _is_king;
}
bool Figure::is_selected() const {
    return _is_selected;
}

void Figure::set_selected(bool selected) {
    _is_selected = selected;
}

void Figure::_handle_inputs() {
    // TODO: add figure input handling
}

}  // namespace checkers