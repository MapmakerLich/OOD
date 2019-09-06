#include "pch.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly(int &flying) = 0;
};
class FlyWithWings : public IFlyBehavior
{
public:
	void Fly(int &flying) override
	{
		flying++;
		cout << "I'm flying with wings!!" << endl;
	}
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly(int &flying) override {}
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
		cout << "I'm dancing menuer" << endl;
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

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior>&& flyBehavior,
		unique_ptr<IQuackBehavior>&& quackBehavior, unique_ptr<IDanceBehavior>)
		: m_quackBehavior(move(quackBehavior))
	{
		assert(m_quackBehavior);
		SetFlyBehavior(move(flyBehavior));
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly(int &flying)
	{
		m_flyBehavior->Fly(flying);
		cout << "Taked off: " << flying << endl;
	}
	virtual void Dance()
	{
		m_danceBehavior->Dance();
	}
	void SetDanceBehavior(unique_ptr<IDanceBehavior>&& danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = move(danceBehavior);
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
	MallardDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DanceWaltz>())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}

	void Dance()
	{
		cout << "I'm dancing waltz" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DanceMenuet>())
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
	void Dance()
	{
		cout << "I'm dancing menuet" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<MuteQuackBehavior>(), make_unique<NoDancing>())
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
	void Dance() override {}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<SqueakBehavior>(), make_unique<NoDancing>())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
	void Dance() override {}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<QuackBehavior>(), make_unique<NoDancing>())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
	void Dance() override {}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck, int &flying)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly(flying);
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	int flying = 0;
	PlayWithDuck(mallardDuck, flying);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck, flying);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck, flying);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck, flying);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck, flying);
	modelDuck.SetFlyBehavior(make_unique<FlyWithWings>());
	PlayWithDuck(modelDuck, flying);
	return 0;
}