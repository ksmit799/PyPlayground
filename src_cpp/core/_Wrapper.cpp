#include "core/_Wrapper.h"

#include <pybind11/pybind11.h>

namespace playground
{

namespace py = pybind11;

// Core namespace.
void wrap_core_playgroundbase(py::module &m);

// Display namespace.
void wrap_display_window(py::module &m);

// Notify namespace.
void wrap_notify_notify(py::module &m);

// Task namespace.
void wrap_task_taskmanager(py::module &m);

PYBIND11_MODULE(PyPlayground, m)
{
	// Core sub-module.
	py::module core = m.def_submodule("core", "A submodule of 'core'");
	wrap_core_playgroundbase(core);

	// Display sub-module.
	py::module display = m.def_submodule("display", "A submodule of 'display'");
	wrap_display_window(display);

	// Notify sub-module.
	py::module notify = m.def_submodule("notify", "A submodule of 'notify'");
	wrap_notify_notify(notify);

	// Task sub-module.
	py::module task = m.def_submodule("task", "A submodule of 'task'");
	wrap_task_taskmanager(task);
}

} // namespace playground