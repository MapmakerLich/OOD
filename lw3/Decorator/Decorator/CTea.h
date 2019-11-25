#pragma once
#include "Beverages.h"
class CTea : public CBeverage
{
public:
	CTea(const std::string &description = "Tea")
		: CBeverage(description)
	{
	}

	double GetCost() const override
	{
		return 30;
	}
};

class CColdTea : public CTea
{
public:
	CColdTea() : CTea("Cold tea")
	{

	}
};

class CCeylonTea : public CTea
{
public:
	CCeylonTea() : CTea("Ceylon tea")
	{

	}
};

class CMilkTea : public CTea
{
public:
	CMilkTea() : CTea("Milk tea")
	{

	}
};

class CChineseTea : public CTea
{
public:
	CChineseTea() : CTea("Chinese tea")
	{

	}
};
