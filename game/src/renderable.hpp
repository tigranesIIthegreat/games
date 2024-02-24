#include <game/window.hpp>

class Renderable {
public:
  Renderable(core::WindowRef window);
  virtual void update() = 0;
  virtual void render();

private:
  core::WindowRef _window;
};