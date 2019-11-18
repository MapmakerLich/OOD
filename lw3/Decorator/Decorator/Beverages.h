#pragma once

#include "IBeverage.h"
#include <iostream>

using namespace std;

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	enum Portion { Single, Double };

	CCappuccino(Portion portion = Portion::Single);

	double GetCost() const override;
private:
	Portion m_portion;
};

// Латте
class CLatte : public CCoffee
{
public:
	enum Portion { Single, Double };

	CLatte(Portion portion = Portion::Single);

	double GetCost() const override;
private:
	Portion m_portion;
};

// Чай
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
	CColdTea();
};

class CCeylonTea : public CTea
{
	CCeylonTea();
};

class CMilkTea : public CTea
{
	CMilkTea();
};

class CChineseTea : public CTea
{
	CChineseTea();
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	enum Portion{ Small, Medium, Big };

	double GetCost() const override;

	CMilkshake(Portion portion = Portion::Medium);

private:
	Portion m_portion;

	string PortionToString(Portion portion) const;
};
