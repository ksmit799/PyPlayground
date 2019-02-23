#include "core/_Wrapper.h"
#include "notify/Notify.h"

#include <pybind11/pybind11.h>

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace playground
{

namespace py = pybind11;

Notify::Notify()
{}

void Notify::verbose(const std::string &message)
{
	py::print("[" + this->getTime() + "] [VERBOSE]: " + message);
}

void Notify::info(const std::string &message)
{
	py::print("[" + this->getTime() + "] [INFO]: " + message);
}

void Notify::warning(const std::string &message)
{
	py::print("[" + this->getTime() + "] [WARNING]: " + message);
}

void Notify::error(const std::string &message)
{
	py::print("[" + this->getTime() + "] [ERROR]: " + message);
}

std::string Notify::getTime()
{
	// Get our chrono time object.
	auto chronoTime = std::chrono::system_clock::now();
	auto currTime = std::chrono::system_clock::to_time_t(chronoTime);

	// Read our chrono time into a stream and return it as a string.
	std::stringstream ss;
	ss << std::put_time(std::localtime(&currTime), "%Y-%m-%d %T");
	return ss.str();
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