#ifndef DISPLAY_WINDOW_H_
#define DISPLAY_WINDOW_H_

#include "SDL.h"

namespace playground {

class PlaygroundBase;

class Window {
 public:
  explicit Window(PlaygroundBase* playground);
  ~Window();

  SDL_Window* get_sdl_window();

 private:
  PlaygroundBase* playground_ptr_;
  SDL_Window* sdl_window_ptr_;
};

} // namespace playground

#endif // DISPLAY_WINDOW_H_
