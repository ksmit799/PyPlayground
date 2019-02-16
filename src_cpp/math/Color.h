#ifndef MATH_COLOR_H
#define MATH_COLOR_H

#include "math/Vector4.h"

namespace playground
{

class Color
{

public:
	Color();

	Color operator=(const Color &vector);

	Vector4 toVector();

private:

};

} // namespace playground

#endif // MATH_COLOR_H