#include "wrapper.h"

#include "pybind11/pybind11.h"

namespace playground
{

namespace py = pybind11;

/**
 * Core submodule.
 */
void wrap_core_playground_base(py::module& m);
void wrap_core_playground_exception(py::module& m);
void wrap_core_color(py::module& m);

/**
 * Display submodule.
 */
void wrap_display_window(py::module& m);

/**
 * Render submodule.
 */
void wrap_render_renderer(py::module& m);

PYBIND11_MODULE(_pyplayground, m)
{
	// Core submodule.
	py::module core = m.def_submodule("core", "");
	wrap_core_playground_base(core);
	wrap_core_playground_exception(core);
	wrap_core_color(core);

	// Display submodule.
	py::module display = m.def_submodule("display", "");
	wrap_display_window(display);

	// Render submodule.
	py::module render = m.def_submodule("render", "");
	wrap_render_renderer(render);
}

} // namespace playground