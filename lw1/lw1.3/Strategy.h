#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;
using DanceBehavior = function<void()>;
using QuackBehavior = function<void()>;
using FlyBehavior = function<void()>;

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

function<void()> FlyWithWings()
{
	size_t flying = 0;
	return[flying]() mutable
	{
		flying++;
		cout << "Taked off: " << flying << endl;
		cout << "I'm flying with wings" << endl;
	};
}

void MuteQuack()
{
}

void Quack()
{
	cout << "Quack Quack" << endl;
}

void Squeak()
{
	cout << "Squeak" << endl;
}
