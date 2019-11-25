#pragma once

#include "IBeverage.h"

class CCondimentDecorator : public IBeverage
{
public:
	std::string GetDescription()const override
	{
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	double GetCost()const override
	{
		return m_beverage->GetCost() + GetCondimentCost();
	}
	virtual std::string GetCondimentDescription()const = 0;
	virtual double GetCondimentCost()const = 0;
protected:
	CCondimentDecorator(IBeveragePtr && beverage)
		: m_beverage(move(beverage))
	{
	}
private:
	IBeveragePtr m_beverage;
};

class CCinnamon : public CCondimentDecorator
{
public:
	CCinnamon(IBeveragePtr && beverage);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
};

class CLemon : public CCondimentDecorator
{
public:
	CLemon(IBeveragePtr && beverage, unsigned quantity = 1);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	unsigned m_quantity;
};

enum class IceCubeType
{
	Dry,	
	Water	
};

class CIceCubes : public CCondimentDecorator
{
public:
	CIceCubes(IBeveragePtr && beverage, unsigned quantity, IceCubeType type = IceCubeType::Water);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	unsigned m_quantity;
	IceCubeType m_type;
};

enum class SyrupType
{
	Chocolate,	
	Maple,		
};

class CSyrup : public CCondimentDecorator
{
public:
	CSyrup(IBeveragePtr && beverage, SyrupType syrupType);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	SyrupType m_syrupType;
};

class CChocolateCrumbs : public CCondimentDecorator
{
public:
	CChocolateCrumbs(IBeveragePtr && beverage, unsigned mass);
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	unsigned m_mass;
};

class CCoconutFlakes : public CCondimentDecorator
{
public:
	CCoconutFlakes(IBeveragePtr && beverage, unsigned mass);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	unsigned m_mass;
};

class CChocolate : public CCondimentDecorator
{
public:
	static const unsigned MAX_QUANTITY = 5;

	CChocolate(IBeveragePtr &&beverage, unsigned quantity = 1);

protected:
	std::string GetCondimentDescription() const override;
	double GetCondimentCost() const override;

private:
	unsigned m_quantity;
};

class CCream : public CCondimentDecorator
{
public:
	CCream(IBeveragePtr &&beverage);

protected:
	std::string GetCondimentDescription() const override;
	double GetCondimentCost() const override;
};

enum class LiquorType
{
	Walnut,
	Chocolate
};


class CLiquor : public CCondimentDecorator
{
public:
	CLiquor(IBeveragePtr &&beverage, LiquorType type);

protected:
	std::string GetCondimentDescription() const override;
	double GetCondimentCost() const override;

private:
	LiquorType m_type;
};