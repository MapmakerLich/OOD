#pragma once

namespace modern_graphics_lib
{
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		float r;
		float g;
		float b;
		float a;
	};
}