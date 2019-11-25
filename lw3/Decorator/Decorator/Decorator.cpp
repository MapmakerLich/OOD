#include "CTea.h"
#include "CMilkshake.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;

template <typename Condiment, typename ...Args>
auto DecorateWith(const Args&...args)
{
	return [=](auto &&b) {
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
	return [](IBeveragePtr && b) {
		return make_unique<CCinnamon>(move(b));
	};
}

template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	return [=](auto && b) {
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
	return decorate(forward<Component>(component));
}

int main()
{
	unique_ptr<IBeverage> tea =
		make_unique<CColdTea>()
		<< DecorateWith<CLemon>(1)
		<< DecorateWith<CIceCubes>(2, IceCubeType::Dry);
	cout << tea->GetDescription() << " costs " << tea->GetCost() << endl;

	unique_ptr<IBeverage> coffee =
		make_unique<CCappuccino>(CCappuccino::Portion::Single)
		<< DecorateWith<CCinnamon>()
		<< DecorateWith<CLiquor>(LiquorType::Chocolate)
		<< DecorateWith<CCream>()
		<< DecorateWith<CChocolateCrumbs>(5);
	cout << coffee->GetDescription() << " costs " << coffee->GetCost() << endl;

	unique_ptr<IBeverage> milkshake =
		make_unique<CMilkshake>(CMilkshake::Portion::Big)
		<< DecorateWith<CSyrup>(SyrupType::Chocolate)
		<< DecorateWith<CCoconutFlakes>(1)
		<< DecorateWith<CChocolate>();
	cout << milkshake->GetDescription() << " costs " << milkshake->GetCost() << endl;
}
