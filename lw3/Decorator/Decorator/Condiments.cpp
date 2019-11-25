#include "Condiments.h"
#include <algorithm>

//CCinnamon
CCinnamon::CCinnamon(IBeveragePtr && beverage)
		: CCondimentDecorator(move(beverage)){}

double CCinnamon::GetCondimentCost()const
{
	return 20;
}

std::string CCinnamon::GetCondimentDescription()const
{
	return "Cinnamon";
}

//CLemon
CLemon::CLemon(IBeveragePtr && beverage, unsigned quantity)
		: CCondimentDecorator(move(beverage))
		, m_quantity(quantity){}

double CLemon::GetCondimentCost()const
{
	return 10 * m_quantity;
}

std::string CLemon::GetCondimentDescription()const
{
	return "Lemon x " + std::to_string(m_quantity);
}

//CIceCubes
CIceCubes::CIceCubes(IBeveragePtr && beverage, unsigned quantity, IceCubeType type)
		: CCondimentDecorator(move(beverage))
		, m_quantity(quantity)
		, m_type(type){}

double CIceCubes::GetCondimentCost()const
{
	return (m_type == IceCubeType::Dry ? 10 : 5) * m_quantity;
}

std::string CIceCubes::GetCondimentDescription()const
{
	return std::string(m_type == IceCubeType::Dry ? "Dry" : "Water")
		+ " ice cubes x " + std::to_string(m_quantity);
}

//CSyrup
CSyrup::CSyrup(IBeveragePtr && beverage, SyrupType syrupType)
		: CCondimentDecorator(move(beverage))
		, m_syrupType(syrupType){}

double CSyrup::GetCondimentCost()const
{
	return 15;
}

std::string CSyrup::GetCondimentDescription()const
{
	return std::string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple")
		+ " syrup";
}

//CChocolateCrumbs
CChocolateCrumbs::CChocolateCrumbs(IBeveragePtr && beverage, unsigned mass)
		:CCondimentDecorator(move(beverage))
		, m_mass(mass)
{
}

double CChocolateCrumbs::GetCondimentCost()const
{
	return 2 * m_mass;
}

std::string CChocolateCrumbs::GetCondimentDescription()const
{
	return "Chocolate crumbs " + std::to_string(m_mass) + "g";
}

//CCoconutFlakes
CCoconutFlakes::CCoconutFlakes(IBeveragePtr && beverage, unsigned mass)
		: CCondimentDecorator(move(beverage))
		, m_mass(mass){}

double CCoconutFlakes::GetCondimentCost()const
{
		return 1 * m_mass;
}

std::string CCoconutFlakes::GetCondimentDescription()const
{
	return "Coconut flakes " + std::to_string(m_mass) + "g";
}

//CChocolate
CChocolate::CChocolate(IBeveragePtr &&beverage, unsigned quantity)
	: CCondimentDecorator(move(beverage))
	, m_quantity(std::min(quantity, MAX_QUANTITY))
{
}

std::string CChocolate::GetCondimentDescription() const
{
	return "Chocolate x " + std::to_string(m_quantity);
}

double CChocolate::GetCondimentCost() const
{
	return 10 * m_quantity;
}

//CCream
CCream::CCream(IBeveragePtr &&beverage)
	: CCondimentDecorator(move(beverage))
{
}

std::string CCream::GetCondimentDescription() const
{
	return "Cream";
}

double CCream::GetCondimentCost() const
{
	return 25;
}

//CLiquor
CLiquor::CLiquor(IBeveragePtr &&beverage, LiquorType type)
	: CCondimentDecorator(move(beverage))
	, m_type(type)
{
}

std::string CLiquor::GetCondimentDescription() const
{
	return std::string(m_type == LiquorType::Walnut ? "Walnut" : "Chocolate")
		+ " liquor";
}

double CLiquor::GetCondimentCost() const
{
	return 50;
}