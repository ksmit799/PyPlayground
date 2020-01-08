#include "render/container.h"

#include <algorithm>

#include "pybind11/pybind11.h"
#include "wrapper.h"
#include "render/renderer.h"

namespace playground {

namespace py = pybind11;

Container::Container() : active_(true), parent_(nullptr) {

}

Container::~Container() {
  Destroy();
}

void Container::Destroy() {
  // We're no longer active.
  SetActive(false);

  // If we have a parent, remove ourself.
  if (parent_ != nullptr) {
    parent_->RemoveChild(this);
  }

  // Children are recursively destroyed as well.
  for (Container* child : children_) {
    child->Destroy();
  }

  assert(parent_ == nullptr);
  assert(children_.empty());
}

void Container::RenderPass(Renderer* renderer) {
  // Only render this part of the render tree if we're active.
  if (!active_) {
    return;
  }

  // Render ourself first (if overridden).
  Render(renderer);

  // Render children.
  for (Container* child : children_) {
    child->RenderPass(renderer);
  }
}

void Container::Render(Renderer* renderer) {
  // Inheritors should override with rendering logic.
}

void Container::SetActive(bool active) {
  active_ = active;
}

void Container::AddChild(Container* child) {
  // Make sure we're not adding ourself!
  if (child == this) {
    return;
  }

  // If the child already has a parent container,
  // remove it from that container first.
  if (child->parent_ != nullptr) {
    child->parent_->RemoveChild(child);
  }

  child->parent_ = this;
  children_.push_back(child);
}

void Container::RemoveChild(Container* child) {
  // Remove the child if it's one of our children.
  std::list<Container*>::iterator child_index = std::find(children_.begin(), children_.end(), child);
  if (child_index != children_.end()) {
    child->parent_ = nullptr;
    children_.erase(child_index);
  }
}

void wrap_render_container(py::module& m) {
  py::module container = m.def_submodule("container", "");

  py::class_<Container>(container, "Container")
    // Constructors.
    .def(py::init<>())
    // Functions & variables.
    .def("destroy", &Container::Destroy, "")
    .def("set_active", &Container::SetActive, "")
    .def("add_child", &Container::AddChild, "")
    .def("remove_child", &Container::RemoveChild, "")
    .def_readwrite("active", &Container::active_);
}

} // namespace playground