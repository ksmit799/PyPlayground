#include "core/_Wrapper.h"
#include "notify/Notify.h"

#include <pybind11/pybind11.h>

namespace playground
{

namespace py = pybind11;

Notify::Notify()
{}

void Notify::verbose(const std::string &message)
{
	py::print("[TIME] [VERBOSE]:", message);
}

void Notify::info(const std::string &message)
{
	py::print("[TIME] [INFO]:", message);
}

void Notify::warning(const std::string &message)
{
	py::print("[TIME] [WARNING]:", message);
}

void Notify::error(const std::string &message)
{
	py::print("[TIME] [ERROR]:", message);
}

void wrap_notify_notify(py::module &m)
{	
	py::class_<Notify>(m, "Notify")
		.def("verbose", &Notify::verbose, "")
		.def("info", &Notify::info, "")
		.def("warning", &Notify::warning, "")
		.def("error", &Notify::error, "");
}

} // namespace playground