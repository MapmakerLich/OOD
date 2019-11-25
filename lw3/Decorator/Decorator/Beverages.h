#pragma once

#include "IBeverage.h"
#include <iostream>

using namespace std;

// ������� ���������� �������, ��������������� ��� ��������
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

// ����
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

// ���������
class CCappuccino : public CCoffee
{
public:
	enum Portion { Single, Double };

	CCappuccino(Portion portion = Portion::Single);

	double GetCost() const override;
private:
	Portion m_portion;
};

// �����
class CLatte : public CCoffee
{
public:
	enum Portion { Single, Double };

	CLatte(Portion portion = Portion::Single);

	double GetCost() const override;
private:
	Portion m_portion;
};
