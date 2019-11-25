#pragma once
#include "Beverages.h"
class CMilkshake : public CBeverage
{
public:
	enum Portion { Small, Medium, Big };

	double GetCost() const override;

	CMilkshake(Portion portion = Portion::Medium);

private:
	Portion m_portion;

	string PortionToString(Portion portion) const;
};
