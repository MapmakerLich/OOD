#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		m_flying++;
		cout << "I'm flying with wings!!" << endl;
		cout << "Taked off: " << m_flying << endl;
	}
private:
	int m_flying = 0;
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};

class NoDancing : public IDanceBehavior
{
public:
	void Dance() override {}
};

class DanceWaltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm dancing waltz!" << endl;
	}
};

class DanceMenuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm dancing menuet!" << endl;
	}
};

struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Quack Quack!!!" << endl;
	}
};
class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Squeek!!!" << endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};
