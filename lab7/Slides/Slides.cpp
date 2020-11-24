#include "Canvas.h"
#include "Ellipse.h"
#include "ShapeGroup.h"
#include "Rectangle.h"
#include "Slide.h"
#include <iostream>
#include "Triangle.h"

const double SLIDE_WIDTH = 800;
const double SLIDE_HEIGHT = 600;

enum HousePalette : RGBAColor
{
	RoofColor = 0x473925FF,
	FacadeColor = 0xB39F82FF,
	WindowColor = 0x7AD2EBFF,
	DoorColor = 0x473925FF,
};

enum WorldPalette : RGBAColor
{
	SunColor = 0xEBE244FF,
	SunRayColor = 0xEBE79D99,
	GrassColor = 0x15A315FF,
};

std::shared_ptr<IShape> CreateHouse()
{
	std::shared_ptr<IShape> roof = std::make_shared<CTriangle>(PointD{ 25, 250 }, PointD{ 150, 150 }, PointD{ 275, 250 });
	roof->GetFillStyle()->Enable(true);
	roof->GetFillStyle()->SetColor(HousePalette::RoofColor);
	roof->GetOutlineStyle()->Enable(true);
	roof->GetOutlineStyle()->SetColor(HousePalette::FacadeColor);
	roof->GetOutlineStyle()->SetThickness(10.0);

	std::shared_ptr<IShape> facade = std::make_shared<CRectangle>(PointD{ 50, 250 }, 200, 200);
	facade->GetFillStyle()->Enable(true);
	facade->GetFillStyle()->SetColor(HousePalette::FacadeColor);
	facade->GetOutlineStyle()->Enable(false);

	std::shared_ptr<IShape> window = std::make_shared<CEllipse>(PointD{ 100, 325 }, 25, 25);
	window->GetFillStyle()->Enable(true);
	window->GetFillStyle()->SetColor(HousePalette::WindowColor);
	facade->GetOutlineStyle()->Enable(false);

	std::shared_ptr<IShape> door = std::make_shared<CRectangle>(PointD{ 150, 325 }, 75, 125);
	door->GetFillStyle()->Enable(true);
	door->GetFillStyle()->SetColor(HousePalette::DoorColor);
	door->GetOutlineStyle()->Enable(false);

	std::shared_ptr<IShape> house = std::make_shared<CShapeGroup>();
	house->GetGroup()->InsertShape(roof);
	house->GetGroup()->InsertShape(facade);
	house->GetGroup()->InsertShape(window);
	house->GetGroup()->InsertShape(door);

	return house;
}

std::shared_ptr<IShape> CreateScaledHouse()
{
	auto scaledHouse = CreateHouse();

	auto empty = std::make_shared<CShapeGroup>();
	scaledHouse->GetGroup()->InsertShape(empty);

	scaledHouse->SetFrame({ { 420, 230 }, 320, 200 });


	scaledHouse->GetFillStyle()->Enable(false);
	scaledHouse->GetOutlineStyle()->Enable(true);
	scaledHouse->GetOutlineStyle()->SetColor(HousePalette::WindowColor);
	scaledHouse->GetOutlineStyle()->SetThickness(3);

	auto rect = *scaledHouse->GetFrame();
	std::cout << rect.leftTop.x << " " << rect.leftTop.y << " " << rect.width << " " << rect.height;

	return scaledHouse;
}

std::shared_ptr<IShape> CreateWorld()
{
	std::shared_ptr<IShape> sun = std::make_shared<CEllipse>(PointD{ 500, 50 }, 50, 50);
	sun->GetFillStyle()->Enable(true);
	sun->GetFillStyle()->SetColor(WorldPalette::SunColor);
	sun->GetOutlineStyle()->Enable(true);
	sun->GetOutlineStyle()->SetColor(WorldPalette::SunRayColor);
	sun->GetOutlineStyle()->SetThickness(30);

	std::shared_ptr<IShape> grass = std::make_shared<CRectangle>(PointD{ 0, 450 }, 800, 150);
	grass->GetFillStyle()->Enable(true);
	grass->GetFillStyle()->SetColor(WorldPalette::GrassColor);
	grass->GetOutlineStyle()->Enable(false);

	std::shared_ptr<IShape> grass2 = std::make_shared<CEllipse>(PointD{ 580, 480 }, 200, 70);
	grass2->GetFillStyle()->Enable(true);
	grass2->GetFillStyle()->SetColor(WorldPalette::GrassColor);
	grass2->GetOutlineStyle()->Enable(false);

	auto house = CreateHouse();
	auto scaledHouse = CreateScaledHouse();

	std::shared_ptr<IShape> world = std::make_shared<CShapeGroup>();

	world->GetGroup()->InsertShape(sun);
	world->GetGroup()->InsertShape(grass);
	world->GetGroup()->InsertShape(grass2);
	world->GetGroup()->InsertShape(house);
	world->GetGroup()->InsertShape(scaledHouse);

	return world;
}

std::shared_ptr<ISlide> CreateSlide()
{
	return std::make_shared<CSlide>(SLIDE_WIDTH, SLIDE_HEIGHT);
}

void Draw(std::shared_ptr<ISlide> slide)
{
	auto width = unsigned(slide->GetWidth());
	auto height = unsigned(slide->GetHeight());

	sf::RenderWindow renderWindow(sf::VideoMode(width, height), "Slide");
	CCanvas sfmlCanvas(renderWindow);

	while (renderWindow.isOpen())
	{
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
		}

		renderWindow.clear(sf::Color::White);
		slide->Draw(sfmlCanvas);
		renderWindow.display();
	}
}

int main()
{
	auto world = CreateWorld();

	auto slide = CreateSlide();
	slide->InsertShape(world);

	Draw(slide);

	return 0;
}