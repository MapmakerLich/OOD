#pragma once

#include "lib/graphics_lib/ICanvas.h"
#include "lib/modern_graphics_lib/ModernGraphicsRenderer.h"

namespace app
{
	class CGraphicsAdapter
		: public modern_graphics_lib::CModernGraphicsRenderer
		, public graphics_lib::ICanvas
	{
	public:
		CGraphicsAdapter(ostream& strm)
			: CModernGraphicsRenderer(strm)
			, m_point(0, 0)
			, m_color(0, 0, 0, 1)
		{
		}

		void SetColor(uint32_t argbColor) override
		{
			m_color.a = (float)(argbColor & 0xff000000) / (float)0xff000000;
			m_color.r = (float)(argbColor & 0xff0000) / (float)0xff0000;
			m_color.g = (float)(argbColor & 0xff00) / (float)0xff00;
			m_color.b = (float)(argbColor & 0xff) / (float)0xff;
		}
		void MoveTo(int x, int y) override
		{
			m_point.x = x;
			m_point.y = y;
		}
		void LineTo(int x, int y) override
		{
			DrawLine(m_point, { x, y }, m_color);
			MoveTo(x, y);
		}

	private:
		modern_graphics_lib::CPoint m_point;
		modern_graphics_lib::CRGBAColor m_color;
	};
}
