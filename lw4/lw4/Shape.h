#pragma once

#include "ICanvas.h"

class CShape
{
public:
	virtual ~CShape() = default;

	virtual void Draw(ICanvas& canvas) const = 0;

protected:
	Color GetColor() const
	{
		return m_color;
	}

	CShape(Color color)
		: m_color(color)
	{
	}

private:
	Color m_color;
};
