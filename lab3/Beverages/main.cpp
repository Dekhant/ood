#include "Beverages.h"
#include "Condiments.h"
#include <iostream>
#include <memory>

int main()
{

	auto latte = std::make_unique<CLatte>(CoffeeSize::Standart);
	auto cinnamon = std::make_unique<CCinnamon>(move(latte));
	auto iceCubes = std::make_unique<CIceCubes>(move(cinnamon), 2, IceCubeType::Dry);
	auto beverage = std::make_unique<CChocolateCrumbs>(move(iceCubes), 2);
	auto liquor = std::make_unique<CLiquor>(move(beverage), LiquorGrade::Nut);
	std::cout << liquor->GetDescription() << " costs " << liquor->GetCost() << std::endl;

	auto blackTea = std::make_unique<CTea>(TeaGrade::Black);
	auto teaWithLemon = std::make_unique<CLemon>(move(blackTea), 3);
	std::cout << teaWithLemon->GetDescription() << " costs " << teaWithLemon->GetCost() << std::endl;
}