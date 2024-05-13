#pragma once

#include <core/input.hpp>
#include <core/renderable.hpp>

#include <memory>

namespace checkers {

enum class FigureColor { WHITE, BLACK };

class Figure : public core::Renderable, public core::input::Inputable {
public:
    Figure(core::Rect position,
           core::TextureRef texture,
           FigureColor color,
           bool is_king);

    FigureColor color() const;
    bool is_king() const;
    bool is_selected() const;
    void set_selected(bool selected);

public:
    virtual void handle_inputs() override;

private:
    const FigureColor _color;
    const bool _is_king;
    bool _is_selected;
};

using FigureRef = std::shared_ptr<Figure>;

}  // namespace checkers