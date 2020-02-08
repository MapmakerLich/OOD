#pragma once

#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(const RectD& rect, const CLineStyle& outlineStyle, const CStyle& fillStyle)
		: CShape(outlineStyle, fillStyle)
		, m_rect(rect)
	{
	}

	std::optional<RectD> GetFrame() const override
	{
		return m_rect;
	}
	void SetFrame(const RectD& frame) override
	{
		m_rect = frame;
	}

protected:
	void DoDraw(ICanvas& canvas) const override
	{
		canvas.MoveTo(m_rect.GetLeftTop().x, m_rect.GetLeftTop().y);
		canvas.LineTo(m_rect.GetLeftTop().x + m_rect.GetWidth(), m_rect.GetLeftTop().y);
		canvas.LineTo(m_rect.GetLeftTop().x + m_rect.GetWidth(), m_rect.GetLeftTop().y + m_rect.GetHeight());
		canvas.LineTo(m_rect.GetLeftTop().x, m_rect.GetLeftTop().y + m_rect.GetHeight());
		canvas.LineTo(m_rect.GetLeftTop().x, m_rect.GetLeftTop().y);
	}

private:
	RectD m_rect;
};
