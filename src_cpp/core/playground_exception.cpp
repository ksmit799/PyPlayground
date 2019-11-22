#include "core/playground_exception.h"

#include "pybind11/pybind11.h"
#include "wrapper.h"

namespace playground {

namespace py = pybind11;

PlaygroundException::PlaygroundException()
	: description("An unknown error occurred") {}

PlaygroundException::PlaygroundException(const std::string& desc)
	: description(desc) {}

void wrap_core_playground_exception(py::module& m) {
  py::register_exception<PlaygroundException>(m, "PlaygroundException");
}

} // namespace playground