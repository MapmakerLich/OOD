#pragma once

#include "IShape.h"
#include "Shapes.h"
#include "GroupShape.h"
#include <set>

using namespace std;

class CSlide : public CShapes, public IDrawable
{
public:
	CSlide(double widht, double height, RGBAColor backgroundColor = 0)
		: m_width(widht)
		, m_height(height)
		, m_backgroundColor(backgroundColor)
	{
	}

	double GetWidth() const
	{
		return m_width;
	}
	double GetHeight() const
	{
		return m_height;
	}

	RGBAColor GetBackgroundColor() const
	{
		return m_backgroundColor;
	}
	void SetBackgroundColor(RGBAColor color)
	{
		m_backgroundColor = color;
	}

	void CreateGroup(const set<size_t>& indexes)
	{
		shared_ptr<CGroupShape> group = make_shared<CGroupShape>();
		for (auto iter = indexes.rbegin(); iter != indexes.rend(); ++iter)
		{
			group->InsertShape(GetShapeAtIndex(*iter), 0);
			RemoveShapeAtIndex(*iter);
		}
		InsertShape(group);
	}
	void UUngroup(size_t index)
	{
		CGroupShape* group = GetShapeAtIndex(index)->GetGroup();

		if (group == nullptr)
		{
			throw runtime_error("This element is not a group");
		}

		for (auto shape : *group)
		{
			InsertShape(shape);
		}

		RemoveShapeAtIndex(index);
	}

	void Draw(ICanvas& canvas) const
	{
		canvas.SetLineWidth(0);
		canvas.BeginFill(m_backgroundColor);
		canvas.MoveTo(0, 0);
		canvas.LineTo(m_width, 0);
		canvas.LineTo(m_width, m_height);
		canvas.LineTo(0, m_height);
		canvas.LineTo(0, 0);
		canvas.EndFill();
		for (size_t i = 0; i < GetShapesCount(); ++i)
		{
			GetShapeAtIndex(i)->Draw(canvas);
		}
	}

private:
	double m_width;
	double m_height;
	RGBAColor m_backgroundColor;
};