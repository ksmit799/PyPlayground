#include "core/_Wrapper.h"
#include "math/Color.h"

#include <pybind11/pybind11.h>

namespace playground
{

namespace py = pybind11;

Color::Color()
{

}

Color Color::operator=(const Color &color)
{
}

Vector4 Color::toVector()
{
	Vector4 vec;
	/*
	vec.x = this->r / 255.0f;
	vec.y = this->g / 255.0f;
	vec.z = this->b / 255.0f;
	vec.w = this->a / 255.0f;
	return vec;
	*/
	return vec;
}

void wrap_math_color(py::module &m)
{}

} // namespace playground