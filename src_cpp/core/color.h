#ifndef CORE_COLOR_H_
#define CORE_COLOR_H_

#include <cstdint>
#include <string>

namespace playground {

class Color {
 public:
  Color();
  Color(const uint8_t& r, const uint8_t& g,
        const uint8_t& b, const uint8_t& a);
  Color(const uint8_t& r, const uint8_t& g,
        const uint8_t& b);
  explicit Color(const uint32_t& hex_int);
  explicit Color(std::string hex_string);
  ~Color();

  static const Color kBlack;
  static const Color kWhite;
  static const Color kClear;
  static const Color kRed;
  static const Color kGreen;
  static const Color kBlue;
  static const Color kGray;
  static const Color kGrey;
  static const Color kYellow;
  static const Color kMagenta;
  static const Color kCyan;

  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

bool operator ==(const Color& left, const Color &right);
bool operator !=(const Color& left, const Color &right);
Color operator +(const Color& left, const Color &right);
Color operator -(const Color& left, const Color &right);
Color operator *(const Color& left, const Color &right);
Color& operator +=(Color& left, const Color &right);
Color& operator -=(Color& left, const Color &right);
Color& operator *=(Color& left, const Color &right);

} // namespace playground

#endif // CORE_COLOR_H_