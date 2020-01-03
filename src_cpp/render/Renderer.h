#ifndef RENDER_RENDERER_H_
#define RENDER_RENDERER_H_

#include <memory>

#include "SDL.h"
#include "core/color.h"
#include "render/container.h"

namespace playground {

class PlaygroundBase;

class Renderer {
 public:
  Renderer(PlaygroundBase* playground);
  ~Renderer();

  void Render();

  void AddChild(Container* child);
  void RemoveChild(Container* child);

  void SetBackgroundColor(const Color& color);
  Color GetBackgroundColor();

 protected:
  SDL_Renderer* sdl_renderer_ptr_;
  std::unique_ptr<Container> container_root_;

 private:
  PlaygroundBase* playground_ptr_;
};

} // namespace playground

#endif // RENDER_RENDERER_H_