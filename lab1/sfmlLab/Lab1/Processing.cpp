#include "Processing.h"
#include "CBody.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <iostream>
#include <fstream>

void Reading(std::vector<sf::Shape*>& shapes, std::string fileName)
{
	std::ifstream input(fileName);
	std::string line;
	while (std::getline(input, line))
	{
		std::string shape = line.substr(0, line.find(":"));
		if (shape == "TRIANGLE")
		{
			sf::ConvexShape* triangle = new sf::ConvexShape();
			std::pair<int, int> points[3];
			triangle->setPointCount(3);
			for (int i = 0; i < 3; i++)
			{
				std::string coords;
				coords = line.substr(line.find("P" + std::to_string(i + 1)) + 3, line.find(";") - line.find("P" + std::to_string(i + 1)) - 3);
				points[i].first = std::stoi(coords.substr(0, coords.find(",")));
				points[i].second = std::stoi(coords.substr(coords.find(",") + 1));
				triangle->setPoint(i, sf::Vector2f(points[i].first, points[i].second));
			}
			triangle->setFillColor(sf::Color::Yellow);
			shapes.push_back(triangle);
		}
		if (shape == "RECTANGLE")
		{
			sf::RectangleShape* rectangle = new sf::RectangleShape();
			sf::ConvexShape* triangle = new sf::ConvexShape();
			std::pair<int, int> points[2];
			for (int i = 0; i < 2; i++)
			{
				std::string coords;
				coords = line.substr(line.find("P" + std::to_string(i + 1)) + 3, line.find(";") - line.find("P" + std::to_string(i + 1)) - 3);
				points[i].first = std::stoi(coords.substr(0, coords.find(",")));
				points[i].second = std::stoi(coords.substr(coords.find(",") + 1));
			}
			rectangle->setSize(sf::Vector2f(abs(points[0].first - points[1].first), abs(points[0].second - points[1].second)));
			rectangle->setPosition(points[0].first, points[0].second);
			rectangle->setFillColor(sf::Color::Green);
			shapes.push_back(rectangle);
		}
		if (shape == "CIRCLE")
		{
			sf::CircleShape* circle = new sf::CircleShape();
			std::string center, radius;
			center = line.substr(line.find_last_of("C") + 2, line.find(";") - line.find_last_of("C") - 2);
			radius = line.substr(line.find_last_of("R") + 2);
			circle->setRadius(std::stoi(radius));
			circle->setPosition(std::stoi(center.substr(0, center.find(","))), std::stoi(center.substr(center.find(",") + 1)));
			circle->setFillColor(sf::Color::Red);
			shapes.push_back(circle);
		}
	}
}

void GetParams(std::vector<sf::Shape*>& shapes, std::string fileName)
{
	std::ofstream output(fileName);
	for (sf::Shape* shape : shapes)
	{
		CBody* body;
		if (dynamic_cast<sf::CircleShape*>(shape))
		{
			body = new CCircle(shape);
			output << "CIRCLE: P=" << body->GetPerimeter() << "; S=" << body->GetArea() << std::endl;
		}
		if (dynamic_cast<sf::RectangleShape*>(shape))
		{
			body = new CRectangle(shape);
			output << "RECTANGLE: P=" << body->GetPerimeter() << "; S=" << body->GetArea() << std::endl;
		}
		if (dynamic_cast<sf::ConvexShape*>(shape))
		{
			body = new CTriangle(shape);
			output << "TRIANGLE: P=" << body->GetPerimeter() << "; S=" << body->GetArea() << std::endl;
		}
	}
}
