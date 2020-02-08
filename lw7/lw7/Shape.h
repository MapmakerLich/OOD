#pragma once

#include "IShape.h"
#include <stdexcept>

using namespace std;

class CShape : public IShape
{
public:
	CShape(const CLineStyle& outlineStyle, const CStyle& fillStyle)
		: m_outlineStyle(outlineStyle)
		, m_fillStyle(fillStyle)
	{
		if (!m_outlineStyle.GetColor() || !m_fillStyle.GetColor())
		{
			throw std::invalid_argument("Only non nullopt values should be passed");
		}
	}

	CLineStyle GetOutlineStyle() const override
	{
		return m_outlineStyle;
	}
	void SetOutlineStyle(const CLineStyle& outlineStyle) override
	{
		m_outlineStyle = outlineStyle;
	}

	CStyle GetFillStyle() const override
	{
		return m_fillStyle;
	}
	void SetFillStyle(const CStyle& fillStyle) override
	{
		m_fillStyle = fillStyle;
	}

	CGroupShape* GetGroup() override
	{
		return nullptr;
	}
	const CGroupShape* GetGroup() const override
	{
		return nullptr;
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetLineColor(m_outlineStyle.GetColor().value());
		if (!m_outlineStyle.IsEnabled().value())
		{
			canvas.SetLineWidth(0);
		}
		else
		{
			canvas.SetLineWidth(m_outlineStyle.GetWidth().value());
		}

		if (!m_fillStyle.IsEnabled().value())
		{
			canvas.EndFill();
		}
		else
		{
			canvas.BeginFill(m_fillStyle.GetColor().value());
		}

		DoDraw(canvas);

		canvas.EndFill();
	}

protected:
	virtual void DoDraw(ICanvas& canvas) const = 0;

private:
	CLineStyle m_outlineStyle;
	CStyle m_fillStyle;
};
