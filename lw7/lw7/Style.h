#pragma once

#include "CommonTypes.h"
#include <optional>

using namespace std;

class CStyle
{
public:
	CStyle() = default;
	CStyle(bool enable, RGBAColor color = 0xff)
		: m_enable(enable)
		, m_color(color)
	{
	}

	optional<bool> IsEnabled() const
	{
		return m_enable;
	}
	optional<RGBAColor> GetColor() const
	{
		return m_color;
	}

private:
	optional<bool> m_enable;
	optional<RGBAColor> m_color;
};

bool operator==(const CStyle &style1, const CStyle &style2);
bool operator!=(const CStyle &style1, const CStyle &style2);