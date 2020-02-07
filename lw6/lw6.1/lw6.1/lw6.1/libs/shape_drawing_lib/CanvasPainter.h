#include "ICanvasDrawable.h"

using namespace graphics_lib;

namespace shape_drawing_lib
{
	class CCanvasPainter
	{
	public:
		CCanvasPainter(ICanvas& canvas)
			: m_canvas(canvas)
		{
		}

		void Draw(const ICanvasDrawable& drawable)
		{
			drawable.Draw(m_canvas);
		}

	private:
		graphics_lib::ICanvas& m_canvas;
	};
}
