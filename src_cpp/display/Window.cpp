#include "display/window.h"

#include "pybind11/pybind11.h"
#include "wrapper.h"

namespace playground {

namespace py = pybind11;

Window::Window(PlaygroundBase* playground) {
  playground_ptr_ = playground;

  // Create a new SDL window with some default settings.
  sdl_window_ptr_ = SDL_CreateWindow(
    "My Game - Created with PyPlayground",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    480,
    SDL_WINDOW_RESIZABLE
  );

  // Make sure the creation of the window was successful.
  if (sdl_window_ptr_ == nullptr) {
    py::print("[PLAYGROUND]: A window creation error occurred: ", SDL_GetError());
    throw std::exception("Failed to create window");
  }
}

Window::~Window() {
  SDL_DestroyWindow(sdl_window_ptr_);
}

SDL_Window* Window::get_sdl_window() {
  return sdl_window_ptr_;
}

void wrap_display_window(py::module& m) {
  py::class_<Window>(m, "Window");
}

} // namespace playground