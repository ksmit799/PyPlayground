#include "core/playground_base.h"

#include "SDL.h"
#include "pybind11/pybind11.h"
#include "wrapper.h"
#include "core/playground_exception.h"

namespace playground {

namespace py = pybind11;

PlaygroundBase* PlaygroundBase::instance_ptr_ = nullptr;

PlaygroundBase::PlaygroundBase() {
  // Attempt to initialize SDL.
  // This should only happen once during the programs lifetime.
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    py::print("[PLAYGROUND]: An error occurred when initializing SDL: ", SDL_GetError());
    throw PlaygroundException("Failed to initialize SDL");
  }

  window = new Window(this);
  renderer = new Renderer(this);
}

PlaygroundBase::~PlaygroundBase() {
  instance_ptr_ = nullptr;

  // Cleanup SDL subsystems.
  SDL_Quit();
}

/**
 * Returns a singleton instance of PlaygroundBase.
 */
PlaygroundBase* PlaygroundBase::instance() {
  if (instance_ptr_ == nullptr) {
    instance_ptr_ = new PlaygroundBase();
  }

  return instance_ptr_;
}

void wrap_core_playground_base(py::module& m) {
  py::class_<PlaygroundBase>(m, "PlaygroundBase")
    .def_static("instance", &PlaygroundBase::instance, "")
    .def_readonly("window", &PlaygroundBase::window, "")
    .def_readonly("renderer", &PlaygroundBase::renderer, "");
}

} // namespace playground