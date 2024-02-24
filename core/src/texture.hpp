#include <string>

#include <SDL3/SDL.h>

namespace core {

class Texture {
public:
  Texture(const std::string &path, size_t frame_width, size_t frame_heigth);

private:
  std::string _path;
  SDL_Texture *_texture;
};

} // namespace core