#include "Style.h"

bool operator==(const CStyle &style1, const CStyle &style2)
{
	return style1.IsEnabled() == style2.IsEnabled() && style1.GetColor() == style2.GetColor();
}
bool operator!=(const CStyle &style1, const CStyle &style2)
{
	return !(style1 == style2);
}