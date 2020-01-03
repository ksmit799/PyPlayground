#include "render/renderer.h"

#include <assert.h>

#include "pybind11/pybind11.h"
#include "wrapper.h"
#include "core/playground_base.h"
#include "core/playground_exception.h"

namespace playground {

namespace py = pybind11;

Renderer::Renderer(PlaygroundBase* playground) {
  playground_ptr_ = playground;

  SDL_Window* active_window = playground_ptr_->window->get_sdl_window();
  assert(active_window != nullptr);

  sdl_renderer_ptr_ = SDL_CreateRenderer(
    active_window,
    -1,
    0
  );

  // Make sure the creation of the renderer was successful.
  if (sdl_renderer_ptr_ == nullptr) {
    py::print("[PLAYGROUND]: A renderer creation error occurred: ", SDL_GetError());
    throw PlaygroundException("Failed to create renderer");
  }

  container_root_ = std::make_unique<Container>();

  SetBackgroundColor(Color::kBlack);
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(sdl_renderer_ptr_);
}

void Renderer::Render() {
  SDL_RenderClear(sdl_renderer_ptr_);

  container_root_->RenderPass(this);

  SDL_RenderPresent(sdl_renderer_ptr_);
}

void Renderer::AddChild(Container* child) {
  container_root_->AddChild(child);
}

void Renderer::RemoveChild(Container* child) {
  container_root_->RemoveChild(child);
}

void Renderer::SetBackgroundColor(const Color& color) {
  SDL_SetRenderDrawColor(sdl_renderer_ptr_,
                         color.r, color.g,
                         color.b, color.a);
}

Color Renderer::GetBackgroundColor() {
  Color color;

  SDL_GetRenderDrawColor(sdl_renderer_ptr_,
                         &color.r, &color.g,
                         &color.b, &color.a);

  return color;
}

void wrap_render_renderer(py::module& m) {
  py::module renderer = m.def_submodule("renderer", "");

  py::class_<Renderer>(renderer, "Renderer")
    .def("render", &Renderer::Render, "")
    .def("add_child", &Renderer::AddChild, "")
    .def("remove_child", &Renderer::RemoveChild, "")
    .def("set_background_color", &Renderer::SetBackgroundColor, "")
    .def("get_background_color", &Renderer::GetBackgroundColor, "");
}

} // namespace playground