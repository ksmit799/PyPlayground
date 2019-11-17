#ifndef RENDER_RENDERER_H_
#define RENDER_RENDERER_H_

#include "SDL.h"
#include "core/color.h"

namespace playground {

class PlaygroundBase;

class Renderer {
 public:
  Renderer(PlaygroundBase* playground);
  ~Renderer();

  void Render();

  void SetBackgroundColor(const Color& color);
  Color GetBackgroundColor();

 private:
  PlaygroundBase* playground_ptr_;
  SDL_Renderer* sdl_renderer_ptr_;
};

} // namespace playground

#endif // RENDER_RENDERER_H_