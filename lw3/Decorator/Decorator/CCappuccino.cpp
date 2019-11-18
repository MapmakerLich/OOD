#include "Beverages.h"

CCappuccino::CCappuccino(Portion portion)
	: CCoffee(portion == Portion::Single ? "Cappuccino" : "Double cappuccino")
{
}

double CCappuccino::GetCost() const
{
	if (m_portion == Portion::Double)
	{
		return 120;
	}
	return 80;
}