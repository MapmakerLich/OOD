#include "pch.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;
using DanceBehavior = function<void()>;
using QuackBehavior = function<void()>;
using FlyBehavior = function<void(int)>;

void DanceMenuet()
{
	cout << "I'm dancing menuet" << endl;
}

void DanceWaltz()
{
	cout << "I'm dancing waltz" << endl;
}

void NoDance()
{
}

void NoFly()
{
}

void FlyWithWings(int &flying)
{
	flying++;
	cout << "Taked off:" << flying << endl;
	cout << "I'm flying with wings" << endl;
}

void MuteQuack()
{
}

void Quack()
{
	cout << "Quack Quack" << endl;
}

void Squeack()
{
	cout << "Squeack" << endl;
}

class Duck
{
public:
	void Dancing() const
	{
		(*m_danceBehavior)();
	}
	void Flying(int &flying)
	{
		(*m_flyBehavior)(flying);
	}
	void Quacking() const
	{
		(*m_quackBehavior)();
	}
	void Swim() const
	{
		cout << "I'm swimming" << endl;
	}

	void SetFlyBehavior(unique_ptr<FlyBehavior> flyBehavior)
	{
		m_flyBehavior = move(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;
protected:
	unique_ptr<QuackBehavior> m_quackBehavior;
	unique_ptr<FlyBehavior> m_flyBehavior;
	unique_ptr<DanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
	{
		m_quackBehavior = make_unique<QuackBehavior>(Quack);
		m_flyBehavior = make_unique<FlyBehavior>(FlyWithWings);
		m_danceBehavior = make_unique<DanceBehavior>(DanceWaltz);
	}

	void Display() const
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
	{
		m_quackBehavior = make_unique<QuackBehavior>(Quack);
		m_flyBehavior = make_unique<FlyBehavior>(FlyWithWings);
		m_danceBehavior = make_unique<DanceBehavior>(DanceMenuet);
	}

	void Display() const
	{
		cout << "I'm redhead duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
	{
		m_quackBehavior = make_unique<QuackBehavior>(Quack);
		m_flyBehavior = make_unique<FlyBehavior>(NoFly);
		m_danceBehavior = make_unique<DanceBehavior>(NoDance);
	}

	void Display() const
	{
		cout << "I'm model duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
	{
		m_quackBehavior = make_unique<QuackBehavior>(MuteQuack);
		m_flyBehavior = make_unique<FlyBehavior>(NoFly);
		m_danceBehavior = make_unique<DanceBehavior>(NoDance);
	}

	void Display() const
	{
		cout << "I'm decoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
	{
		m_quackBehavior = make_unique<QuackBehavior>(Squeack);
		m_flyBehavior = make_unique<FlyBehavior>(NoFly);
		m_danceBehavior = make_unique<DanceBehavior>(NoDance);
	}

	void Display() const
	{
		cout << "I'm rubber duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck, int &flying)
{
	DrawDuck(duck);
	duck.Quacking();
	duck.Flying(flying);
	duck.Dancing();
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
	modelDuck.SetFlyBehavior(make_unique<FlyBehavior>(FlyWithWings));
	PlayWithDuck(modelDuck, flying);
	return 0;
}