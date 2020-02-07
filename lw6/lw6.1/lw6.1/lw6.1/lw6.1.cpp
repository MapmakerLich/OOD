#include "libs/graphics_lib/Canvas.h"
#include "libs/shape_drawing_lib/Triangle.h"
#include "libs/shape_drawing_lib/Rectangle.h"
#include "libs/shape_drawing_lib/CanvasPainter.h"
#include "GraphicsAdapter.h"
#include <string>

using namespace std;
using namespace graphics_lib;
using namespace shape_drawing_lib;
using namespace modern_graphics_lib;

namespace app
{
	void PaintPicture(CCanvasPainter& painter)
	{
		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xf010d020);
		CRectangle rectangle({ 30, 40 }, 18, 24, 0xa000e0c0);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		CCanvas simpleCanvas;
		CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		CModernGraphicsRenderer renderer(cout);
		CGraphicsAdapter adapter(renderer);
		CCanvasPainter painter(adapter);
		renderer.BeginDraw();
		PaintPicture(painter);
	}
}

using namespace app;

int main()
{
	cout << "Should we use new API (y)?";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		PaintPictureOnCanvas();
	}
}