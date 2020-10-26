#pragma once
#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
protected:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee", double cost = 60)
		:CBeverage(description), m_cost(cost)
	{}

	double GetCost() const override
	{
		return m_cost;
	}
protected:
	double m_cost;
};

enum class CoffeeSize
{
	Standart,
	Double
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeeSize size)
		:CCoffee(
			size == CoffeeSize::Double ? "Double Cappuccino" : "Standart Cappuccino",
			size == CoffeeSize::Double ? 120 : 80
		)
	{}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeeSize size)
		:CCoffee(size == CoffeeSize::Double ? "Double Latte" : "Standart Latte",
			size == CoffeeSize::Double ? 130 : 90)
	{
	}
};

enum class TeaGrade
{
	Black,
	Green,
	Fruit,
	Oolong
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaGrade teaGrade)
		:CBeverage("")
	{
		if (teaGrade == TeaGrade::Black)
		{
			m_description = "Black Tea";
		}
		if (teaGrade == TeaGrade::Fruit)
		{
			m_description = "Fruit Tea";
		}
		if (teaGrade == TeaGrade::Green)
		{
			m_description = "Green Tea";
		}
		if (teaGrade == TeaGrade::Oolong)
		{
			m_description == "Oolong Tea";
		}
	}

	double GetCost() const override
	{
		return 30;
	}
};

enum class MilkshakeSize
{
	Small,
	Medium,
	Large
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize milkshakeSize)
		:CBeverage(""), m_cost()
	{
		if (milkshakeSize == MilkshakeSize::Small)
		{
			m_description = "Small Milkshake";
			m_cost = 50;
		}
		if (milkshakeSize == MilkshakeSize::Medium)
		{
			m_description = "Medium Milkshake";
			m_cost = 60;
		}
		if (milkshakeSize == MilkshakeSize::Large)
		{
			m_description = "Large Milkshake";
			m_cost = 80;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}
private:
	double m_cost;
};