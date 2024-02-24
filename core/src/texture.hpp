#include <string>

#include <SDL3/SDL.h>

namespace core {

class Texture {
public:
  Texture(const std::string &path, float frame_width, float frame_heigth);

private:
  std::string _path;
  SDL_Texture *_texture;
};

} // namespace core