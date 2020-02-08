#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../lw7/GroupShape.h"
#include "../lw7/Rectangle.h"
#include "../lw7/Ellipse.h"
#include "../lw7/Canvas.h"
#include "../lw7/Shapes.h"
#include <sstream>

using namespace std;

TEST_CASE("Constructor group shape")
{
	CGroupShape group;

	CHECK(group.GetOutlineStyle() == CLineStyle());
	CHECK(group.GetFillStyle() == CStyle());
	CHECK(group.GetGroup() == &group);

	CHECK(group.GetShapesCount() == 0);
}

TEST_CASE("Insert shape to group")
{
	CGroupShape group;
	shared_ptr<IShape> rectangle = make_shared<CRectangle>(RectD({ 2, 3 }, 4, 5), CLineStyle(true), CStyle(true, 0xaa3399dd));
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(RectD({ 10, 14 }, 6, 7), CLineStyle(true, 0x001122ff, 2), CStyle(false));
	group.InsertShape(rectangle);
	group.InsertShape(ellipse);

	CHECK(group.GetOutlineStyle() == CLineStyle());
	CHECK(group.GetFillStyle() == CStyle());
	CHECK(group.GetGroup() == &group);

	CHECK(group.GetShapesCount() == 2);
	CHECK(group.GetShapeAtIndex(0) == rectangle);
	CHECK(group.GetShapeAtIndex(1) == ellipse);
}

TEST_CASE("Set outline style on group shape")
{
	CGroupShape group;
	shared_ptr<IShape> rectangle = make_shared<CRectangle>(RectD({ 2, 3 }, 4, 5), CLineStyle(true), CStyle(true, 0xaa3399dd));
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(RectD({ 10, 14 }, 6, 7), CLineStyle(true, 0x001122ff, 2), CStyle(false));
	group.InsertShape(rectangle);
	group.InsertShape(ellipse);

	CLineStyle outlineStyle(true, 0x112233aa, 3);
	group.SetOutlineStyle(outlineStyle);

	CHECK(rectangle->GetOutlineStyle() == outlineStyle);
	CHECK(ellipse->GetOutlineStyle() == outlineStyle);

	CHECK(group.GetOutlineStyle() == outlineStyle);
}

TEST_CASE("Set fill style on group shape")
{
	CGroupShape group;
	shared_ptr<IShape> rectangle = make_shared<CRectangle>(RectD({ 2, 3 }, 4, 5), CLineStyle(true), CStyle(true, 0xaa3399dd));
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(RectD({ 10, 14 }, 6, 7), CLineStyle(true, 0x001122ff, 2), CStyle(false));
	group.InsertShape(rectangle);
	group.InsertShape(ellipse);

	CStyle fillStyle(true, 0x112233aa);
	group.SetFillStyle(fillStyle);

	CHECK(rectangle->GetFillStyle() == fillStyle);
	CHECK(ellipse->GetFillStyle() == fillStyle);

	CHECK(group.GetFillStyle() == fillStyle);
}

TEST_CASE("Draw group shape")
{
	CGroupShape group;
	shared_ptr<IShape> rectangle = make_shared<CRectangle>(RectD({ 2, 3 }, 4, 5), CLineStyle(true), CStyle(true, 0xaa3399dd));
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(RectD({ 10, 14 }, 6, 7), CLineStyle(true, 0x001122ff, 2), CStyle(false));
	group.InsertShape(rectangle);
	group.InsertShape(ellipse);

	ostringstream outStrm;
	CCanvas canvas(outStrm);

	group.Draw(canvas);

	istringstream result(outStrm.str());
	string str;

	getline(result, str);
	CHECK(str == "SetLineColor (#000000ff)");
	getline(result, str);
	CHECK(str == "SetLineWidth (1)");
	getline(result, str);
	CHECK(str == "BeginFill (#aa3399dd)");
	getline(result, str);
	CHECK(str == "MoveTo (2, 3)");
	getline(result, str);
	CHECK(str == "LineTo (6, 3)");
	getline(result, str);
	CHECK(str == "LineTo (6, 8)");
	getline(result, str);
	CHECK(str == "LineTo (2, 8)");
	getline(result, str);
	CHECK(str == "LineTo (2, 3)");
	getline(result, str);
	CHECK(str == "EndFill");

	getline(result, str);
	CHECK(str == "SetLineColor (#001122ff)");
	getline(result, str);
	CHECK(str == "SetLineWidth (2)");
	getline(result, str);
	CHECK(str == "DrawEllipse (10, 14, 6, 7)");

	CHECK_FALSE(getline(result, str));
}

template<typename T>
bool operator==(const Rect<T> &rect1, const Rect<T> &rect2)
{
	return rect1.GetLeftTop().x == rect2.GetLeftTop().x && rect1.GetLeftTop().y == rect2.GetLeftTop().y
		&& rect1.GetWidth() == rect2.GetWidth() && rect1.GetHeight() == rect2.GetHeight();
}

TEST_CASE("Get frame from group shape")
{
	CGroupShape group;
	shared_ptr<IShape> rectangle = make_shared<CRectangle>(RectD({ 2, 4 }, 4, 2), CLineStyle(true), CStyle(true));
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(RectD({ 8, 0 }, 4, 8), CLineStyle(true), CStyle(true));
	group.InsertShape(rectangle);
	group.InsertShape(ellipse);

	CHECK(group.GetFrame() == RectD({ 2, 0 }, 10, 8));
}

TEST_CASE("Set frame to group shape")
{
	CGroupShape group;
	shared_ptr<IShape> rectangle = make_shared<CRectangle>(RectD({ 2, 4 }, 4, 2), CLineStyle(true), CStyle(true));
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(RectD({ 8, 0 }, 4, 8), CLineStyle(true), CStyle(true));
	group.InsertShape(rectangle);
	group.InsertShape(ellipse);

	group.SetFrame(RectD({ 4, 10 }, 5, 4));

	CHECK(rectangle->GetFrame() == RectD({ 4, 12 }, 2, 1));
	CHECK(ellipse->GetFrame() == RectD({ 7, 10 }, 2, 4));

	CHECK(group.GetFrame() == RectD({ 4, 10 }, 5, 4));
}

TEST_CASE("Get frame from empty group")
{
	CGroupShape group1;
	CHECK(group1.GetFrame() == nullopt);

	shared_ptr<IShape> group2 = make_shared<CGroupShape>();
	shared_ptr<IShape> group3 = make_shared<CGroupShape>();
	group1.InsertShape(group2);
	group1.InsertShape(group3);

	CHECK(group1.GetFrame() == nullopt);

	shared_ptr<IShape> rectangle = make_shared<CRectangle>(RectD({ 2, 4 }, 4, 2), CLineStyle(true), CStyle(true));
	group1.InsertShape(rectangle);

	CHECK(group1.GetFrame() == RectD({ 2, 4 }, 4, 2));
}

TEST_CASE("Set frame to empty group")
{
	CGroupShape group1;
	shared_ptr<IShape> group2 = make_shared<CGroupShape>();
	shared_ptr<IShape> rectangle = make_shared<CRectangle>(RectD({ 2, 4 }, 4, 2), CLineStyle(true), CStyle(true));
	group1.InsertShape(group2);
	group1.InsertShape(rectangle);

	group1.SetFrame(RectD({ 4, 10 }, 5, 4));

	CHECK(rectangle->GetFrame() == RectD({ 4, 10 }, 5, 4));
	CHECK(group1.GetFrame() == RectD({ 4, 10 }, 5, 4));
}