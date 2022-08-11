#include "pch.h"
#include "Color.hpp"

namespace Engine2D
{
	Color::Color(float _r, float _g, float _b, float _a)
		: r{ _r }
		, g{ _g }
		, b{ _b }
		, a{ _a }
	{
	}
	Color::Color(float(&_array)[4])
		: array{ _array[0],_array[1],_array[2],_array[3] }
	{
	}
	Color::~Color()
	{
	}
}
