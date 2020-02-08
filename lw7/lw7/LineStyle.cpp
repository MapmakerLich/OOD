#include "LineStyle.h"

using namespace std;

CLineStyle::CLineStyle(bool enable, RGBAColor color, double width)
	: CStyle(enable, color)
	, m_width(width)
{
	if (m_width < 0)
	{
		invalid_argument("The line width cannot be negative");
	}
}

optional<double> CLineStyle::GetWidth() const
{
	return m_width;
}

bool operator==(const CLineStyle &style1, const CLineStyle &style2)
{
	return style1.IsEnabled() == style2.IsEnabled() && style1.GetColor() == style2.GetColor()
		&& style1.GetWidth() == style2.GetWidth();
}

bool operator!=(const CLineStyle &rational1, const CLineStyle &rational2)
{
	return !(rational1 == rational2);
}