#include "Beverages.h"

CLatte::CLatte(Portion portion)
	: CCoffee(portion == Portion::Single ? "Latte" : "Double latte")
{
}

double CLatte::GetCost() const
{
	if (m_portion == Portion::Double)
	{
		return 130;
	}
	return 90;
}