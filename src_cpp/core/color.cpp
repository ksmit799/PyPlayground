#include "core/color.h"

#include <algorithm>

#include "pybind11/pybind11.h"
#include "pybind11/operators.h"
#include "wrapper.h"

namespace playground {

namespace py = pybind11;

const Color Color::kBlack(0, 0, 0);
const Color Color::kWhite(255, 255, 255);
const Color Color::kClear(0, 0, 0, 0);
const Color Color::kRed(255, 0, 0);
const Color Color::kGreen(0, 255, 0);
const Color Color::kBlue(0, 0, 255);
const Color Color::kGray(128, 128, 128);
const Color Color::kGrey(128, 128, 128);
const Color Color::kYellow(255, 255, 0);
const Color Color::kMagenta(255, 0, 255);
const Color Color::kCyan(0, 255, 255);

Color::Color() : r(0), g(0), b(0), a(255) {}

Color::Color(const uint8_t& r, const uint8_t& g,
             const uint8_t& b, const uint8_t& a)
  : r(r), g(g), b(b), a(a) {}

Color::Color(const uint8_t& r, const uint8_t& g,
             const uint8_t& b)
  : r(r), g(g), b(b), a(255) {}

Color::Color(const uint32_t& hex_int) : a(255) {
  r = ((hex_int & 0xFF0000) >> 16);
  g = ((hex_int & 0x00FF00) >> 8);
  b = ((hex_int & 0x0000FF) >> 0);
}

Color::Color(std::string hex_string) : a(255) {
  // Strip the '#' if it exists.
  if (hex_string[0] == '#') {
    hex_string.erase(0, 1);
  }

  uint32_t hex_int = std::stoul(hex_string, nullptr, 16);

  r = ((hex_int & 0xFF0000) >> 16);
  g = ((hex_int & 0x00FF00) >> 8);
  b = ((hex_int & 0x0000FF) >> 0);
}

Color::~Color() {}

bool operator ==(const Color& left, const Color& right) {
  return (left.r == right.r) &&
         (left.g == right.g) &&
         (left.b == right.b) &&
         (left.a == right.a);
}

bool operator !=(const Color& left, const Color& right) {
  return !(left == right);
}

Color operator +(const Color& left, const Color& right) {
  return Color(uint8_t(std::min(int(left.r) + right.r, 255)),
               uint8_t(std::min(int(left.g) + right.g, 255)),
               uint8_t(std::min(int(left.b) + right.b, 255)),
               uint8_t(std::min(int(left.a) + right.a, 255)));
}

Color operator -(const Color& left, const Color& right) {
  return Color(uint8_t(std::max(int(left.r) - right.r, 0)),
               uint8_t(std::max(int(left.g) - right.g, 0)),
               uint8_t(std::max(int(left.b) - right.b, 0)),
               uint8_t(std::max(int(left.a) - right.a, 0)));
}

Color operator *(const Color& left, const Color& right) {
  return Color(uint8_t(int(left.r) * right.r / 255),
               uint8_t(int(left.g) * right.g / 255),
               uint8_t(int(left.b) * right.b / 255),
               uint8_t(int(left.a) * right.a / 255));
}

Color& operator +=(Color& left, const Color& right) {
  return left = left + right;
}

Color& operator -=(Color& left, const Color& right) {
  return left = left - right;
}

Color& operator *=(Color& left, const Color& right) {
  return left = left * right;
}

void wrap_core_color(py::module& m) {
  py::module color = m.def_submodule("color", "");

  py::class_<Color>(color, "Color")
    // Constructors.
    .def(py::init<>())
    .def(py::init<const uint8_t&, const uint8_t&, const uint8_t&, const uint8_t&>())
    .def(py::init<const uint8_t&, const uint8_t&, const uint8_t&>())
    .def(py::init<const uint32_t&>())
    .def(py::init<std::string>())
    // Operators.
    .def(py::self == py::self)
    .def(py::self != py::self)
    .def(py::self + py::self)
    .def(py::self - py::self)
    .def(py::self * py::self)
    .def(py::self += py::self)
    .def(py::self -= py::self)
    .def(py::self *= py::self)
    // Constants.
    .def_readonly_static("BLACK", &Color::kBlack)
    .def_readonly_static("WHITE", &Color::kWhite)
    .def_readonly_static("CLEAR", &Color::kClear)
    .def_readonly_static("RED", &Color::kRed)
    .def_readonly_static("GREEN", &Color::kGreen)
    .def_readonly_static("BLUE", &Color::kBlue)
    .def_readonly_static("GRAY", &Color::kGray)
    .def_readonly_static("GREY", &Color::kGrey)
    .def_readonly_static("YELLOW", &Color::kYellow)
    .def_readonly_static("MAGENTA", &Color::kMagenta)
    .def_readonly_static("CYAN", &Color::kCyan)
    // Functions & variables.
    .def_readwrite("r", &Color::r)
    .def_readwrite("g", &Color::g)
    .def_readwrite("b", &Color::b)
    .def_readwrite("a", &Color::a);
}

} // namespace playground