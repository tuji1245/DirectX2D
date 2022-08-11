#pragma once

namespace Engine2D
{
	class Color final
	{
	public:
		Color(float _r, float _g, float _b, float _a);
		Color(float (&_array)[4]);
		~Color();
	public:
		union
		{
			struct
			{
				float r, g, b, a;
			};
			struct
			{
				float array[4];
			};
		};
	};
}