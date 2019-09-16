#pragma once
#include "Strategy.h"

class Duck
{
public:
	Duck(const function<void()> &flyBehavior, const function<void()> &danceBehavior, const function<void()> &quackBehavior)
		: m_quackBehavior(quackBehavior), m_danceBehavior(danceBehavior), m_flyBehavior(flyBehavior)
	{
	}
	void Dancing() const
	{
		m_danceBehavior();
	}
	void Flying() const
	{
		m_flyBehavior();
	}
	void Quacking() const
	{
		m_quackBehavior();
	}
	void Swim() const
	{
		cout << "I'm swimming" << endl;
	}

	void SetFly(const function<void()> &flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;
private:
	function<void()> m_quackBehavior;
	function<void()> m_flyBehavior;
	function<void()> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck() : Duck (FlyWithWings(), DanceWaltz, Quack)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck() : Duck(FlyWithWings(), DanceMenuet, Quack)
	{
	}

	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck() : Duck (NoFly, NoDance, Quack)
	{
	}

	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck() : Duck (NoFly, NoDance, MuteQuack)
	{
	}

	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck() : Duck (NoFly, NoDance, Squeak)
	{
	}

	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};
