#include "Slide.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "Canvas.h"

using namespace std;

void DrawPicture(CSlide& slide, ICanvas& canvas)
{
	slide.InsertShape(make_shared<CEllipse>(RectD({ 225, 25 }, 40, 40), CLineStyle(false), CStyle(true, 0xffff00ff)));
	slide.InsertShape(make_shared<CRectangle>(RectD({ 0, 130 }, 300, 70), CLineStyle(true), CStyle(true, 0x00ff00ff)));
	slide.InsertShape(make_shared<CRectangle>(RectD({ 90, 90 }, 10, 30), CLineStyle(true), CStyle(true, 0xff0000ff)));
	slide.InsertShape(make_shared<CTriangle>(PointD{ 80, 100 }, PointD{ 110, 120 }, PointD{ 50, 120 },
		CLineStyle(true), CStyle(true, 0x888888ff)));
	slide.CreateGroup(set<size_t>{ 2, 3 });
	slide.InsertShape(make_shared<CRectangle>(RectD({ 60, 120 }, 40, 35), CLineStyle(true), CStyle(true, 0xff8800ff)));
	slide.CreateGroup(set<size_t>{ 2, 3 });
	slide.Draw(canvas);
}

int main()
{
	CSlide slide(300, 200, 0x0000ffff);
	CCanvas canvas;
	DrawPicture(slide, canvas);
}