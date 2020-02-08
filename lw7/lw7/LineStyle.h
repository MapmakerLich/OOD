#pragma once

#include "Style.h"

using namespace std;

class CLineStyle : public CStyle
{
public:
	CLineStyle() = default;
	CLineStyle(bool enable, RGBAColor color = 0xff, double width = 1);

	std::optional<double> GetWidth() const;

private:
	std::optional<double> m_width;
};

bool operator==(const CLineStyle &style1, const CLineStyle &style2);
bool operator!=(const CLineStyle &style1, const CLineStyle &style2);