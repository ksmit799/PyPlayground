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

  // The 'main' thread that PyPlayground has been instantiated on.
  main_thread_id_ = std::this_thread::get_id();

  window = std::make_shared<Window>(this);
  renderer = std::make_shared<Renderer>(this);
  task_manager = std::make_shared<TaskManager>(this);

  // Repeating tasks.
  render_task = task_manager->CreateTask("RenderPass", std::bind(&Renderer::Render, renderer), Task::kVeryLow);
  input_task = task_manager->CreateTask("InputPoll", std::bind(&PlaygroundBase::PollEvents, this), Task::kHigh);
}

PlaygroundBase::~PlaygroundBase() {
  Quit();
}

void PlaygroundBase::Quit() {
  instance_ptr_ = nullptr;

  task_manager->Shutdown();

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

// TODO(Ksmit799): Move this.
void PlaygroundBase::PollEvents() {
  SDL_Event e;
  SDL_PollEvent(&e);

  switch (e.type) {
    case SDL_QUIT:
      Quit();
      break;
    default:
      break;
  }
}

void wrap_core_playground_base(py::module& m) {
  py::module playground_base = m.def_submodule("playground_base", "");

  py::class_<PlaygroundBase>(playground_base, "PlaygroundBase")
    .def("quit", &PlaygroundBase::Quit, "")
    .def_static("instance", &PlaygroundBase::instance, "")
    .def_readonly("window", &PlaygroundBase::window, "")
    .def_readonly("renderer", &PlaygroundBase::renderer, "")
    .def_readonly("task_manager", &PlaygroundBase::task_manager, "")
    .def_readonly("render_task", &PlaygroundBase::render_task, "")
    .def_readonly("input_task", &PlaygroundBase::input_task, "");
}

} // namespace playground