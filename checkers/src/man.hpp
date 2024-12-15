#pragme once

#include "figure.hpp"

namespace checkers {

class Man : public Figure {
private:
    static core::TextureRef _white_man_texture;
    static core::TextureRef _black_man_texture;
};

} // namesapce checkers