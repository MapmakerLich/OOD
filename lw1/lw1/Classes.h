#pragma once
#include "Behaviors.h"

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior>&& flyBehavior,
		unique_ptr<IDanceBehavior>&& danceBehavior, unique_ptr<IQuackBehavior>&& quackBehavior)
		: m_quackBehavior(move(quackBehavior)), m_danceBehavior(move(danceBehavior))
	{
		assert(danceBehavior);
		assert(quackBehavior);
		SetFlyBehavior(move(flyBehavior));
	}
	void Quack()
	{
		m_quackBehavior->Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior->Fly();
	}
	void Dance()
	{
		m_danceBehavior->Dance();
	}
	void SetFlyBehavior(unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;
private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck() : Duck (make_unique<FlyWithWings>(),
		make_unique<DanceWaltz>(), make_unique<QuackBehavior>())
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
	RedheadDuck() : Duck(make_unique<FlyWithWings>(),
		make_unique<DanceMenuet>(), make_unique<QuackBehavior>()) 
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck() : Duck(make_unique<FlyNoWay>(),
		make_unique<NoDancing>(), make_unique<MuteQuackBehavior>())
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
	RubberDuck() : Duck(make_unique<FlyNoWay>(),
		make_unique<NoDancing>(), make_unique<SqueakBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck() : Duck(make_unique<FlyNoWay>(),
		make_unique<NoDancing>(), make_unique<QuackBehavior>())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

