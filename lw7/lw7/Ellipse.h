#pragma once

#include "Shape.h"

using namespace std;

class CEllipse : public CShape
{
public:
	CEllipse(const RectD& ellipse, const CLineStyle& outlineStyle, const CStyle& fillStyle)
		: CShape(outlineStyle, fillStyle)
		, m_ellipse(ellipse)
	{
	}

	optional<RectD> GetFrame() const override
	{
		return m_ellipse;
	}
	void SetFrame(const RectD& frame) override
	{
		m_ellipse = frame;
	}

protected:
	void DoDraw(ICanvas& canvas) const override
	{
		canvas.DrawEllipse(m_ellipse.GetLeftTop().x, m_ellipse.GetLeftTop().y, m_ellipse.GetWidth(), m_ellipse.GetHeight());
	}

private:
	RectD m_ellipse;
};
