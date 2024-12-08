#pragma once

#include <core/game_object.hpp>
#include <memory>
#include "color.hpp"

namespace checkers {

class Figure : public core::GameObject {
public:
    Figure(core::Rect position, Color color);

    Color color() const;
    bool is_king() const;
    bool is_selected() const;
    void set_selected(bool selected);

public:
    virtual void handle_inputs() override;

private:
    const Color _color;
    bool _is_king;
    bool _is_selected;

private:
    static core::TextureRef _white_man_texture;
    static core::TextureRef _black_man_texture;
    static core::TextureRef _white_king_texture;
    static core::TextureRef _black_king_texture;
};

using FigureRef = std::shared_ptr<Figure>;

}  // namespace checkers