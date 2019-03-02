#include "core/_Wrapper.h"
#include "messenger/Messenger.h"

#include <pybind11/pybind11.h>

namespace playground
{

namespace py = pybind11;

Messenger::Messenger()
{}

void wrap_messenger_messenger(py::module &m)
{
	py::class_<Messenger>(m, "Messenger");
}

} // namespace playground