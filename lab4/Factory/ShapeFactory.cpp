#include "ShapeFactory.h"
#include <algorithm>
#include <cctype>
#include <sstream>

std::unique_ptr<CShape> CShapeFactory::CreateShape(std::string const& description) const
{
	Params params = ParseParams(description);
	if (params.empty())
	{
		throw std::invalid_argument("Invalid number of parameters");
	}
	std::string shapeName = params[0];

	auto it = SHAPES_CREATION.find(shapeName);
	if (it != SHAPES_CREATION.end())
	{
		return it->second(params);
	}
	throw std::runtime_error("Invalid name of shape");
}

CShapeFactory::Params CShapeFactory::ParseParams(std::string const& str)
{
	std::stringstream ss(str);
	CShapeFactory::Params params;
	std::string param;

	while (ss >> param)
	{
		std::transform(param.begin(), param.end(), param.begin(), [](char c) { return std::tolower(c); });
		params.push_back(param);
	}
	return params;
}

Color CShapeFactory::GetColor(std::string const& color)
{
	if (color == "green")
	{
		return Color::Green;
	}
	else if (color == "red")
	{
		return Color::Red;
	}
	else if (color == "blue")
	{
		return Color::Blue;
	}
	else if (color == "yellow")
	{
		return Color::Yellow;
	}
	else if (color == "pink")
	{
		return Color::Pink;
	}
	else if (color == "black")
	{
		return Color::Black;
	}
	throw std::invalid_argument("Unknown color");
}

double CShapeFactory::ToDouble(std::string const& number)
{
	try
	{
		return std::stod(number);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Failed to create double number");
	}
}

size_t CShapeFactory::ToUnsigned(std::string const& number)
{
	try
	{
		return (size_t)std::stoull(number);
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument("Failed to create unsigned number");
	}
}

std::unique_ptr<CShape> CShapeFactory::CreateRectangle(Params const& params)
{
	if (params.size() != 6)
	{
		throw std::invalid_argument("Invalid number of parameters");
	}

	Color color = GetColor(params[1]);
	Point leftTop = { ToDouble(params[2]), ToDouble(params[3]) };
	double width = ToDouble(params[4]);
	double height = ToDouble(params[5]);

	return std::make_unique<CRectangle>(color, leftTop, width, height);
}

std::unique_ptr<CShape> CShapeFactory::CreateTriangle(Params const& params)
{
	if (params.size() != 8)
	{
		throw std::invalid_argument("Invalid number of parameters");
	}

	Color color = GetColor(params[1]);
	Point vertex1 = { ToDouble(params[2]), ToDouble(params[3]) };
	Point vertex2 = { ToDouble(params[4]), ToDouble(params[5]) };
	Point vertex3 = { ToDouble(params[6]), ToDouble(params[7]) };

	return std::make_unique<CTriangle>(color, vertex1, vertex2, vertex3);
}

std::unique_ptr<CShape> CShapeFactory::CreateEllipse(Params const& params)
{
	if (params.size() != 6)
	{
		throw std::invalid_argument("Invalid number of parameters");
	}

	Color color = GetColor(params[1]);
	Point center = { ToDouble(params[2]), ToDouble(params[3]) };
	double horizontalRadius = ToDouble(params[4]);
	double verticalRadius = ToDouble(params[5]);

	return std::make_unique<CEllipse>(color, center, horizontalRadius, verticalRadius);
}

std::unique_ptr<CShape> CShapeFactory::CreateRegularPolygon(Params const& params)
{
	if (params.size() != 6)
	{
		throw std::invalid_argument("Invalid number of parameters");
	}

	Color color = GetColor(params[1]);
	size_t vertexCount = ToUnsigned(params[2]);
	Point center = { ToDouble(params[3]), ToDouble(params[4]) };
	double radius = ToDouble(params[5]);

	return std::make_unique<CRegularPolygon>(color, vertexCount, center, radius);
}