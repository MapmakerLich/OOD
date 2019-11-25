#include "Beverages.h"
#include "CMilkshake.h"

CMilkshake::CMilkshake(Portion portion)
	: CBeverage(PortionToString(portion) + " milkshake")
	, m_portion(portion)
{
}

string CMilkshake::PortionToString(Portion portion) const
{
	switch (portion)
	{
	case Portion::Small:
		return "Small";
		break;
	case Portion::Big:
		return "Big";
		break;
	default:
		return "Medium";
		break;
	}
}

double CMilkshake::GetCost() const
{
	switch (m_portion)
	{
	case Portion::Small:
		return 50;

	case Portion::Big:
		return 80;

	default:
		return 60;
	}
}