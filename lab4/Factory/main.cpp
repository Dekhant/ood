#include "CCanvas.h"
#include "Designer.h"
#include "Painter.h"
#include "ShapeFactory.h"
#include <iostream>

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

int main()
{

	std::cout << "Use:\n"
		"rectangle <color> <left top vertex> <width> <height>\n"
		"triangle <color> <vertex 1> <vertex 2> <vertex3>\n"
		"ellipse <color> <center point> <horizontal radius> <vertical radius>\n"
		"regularPolygon <color> <vertexe count> <center point> <radius>\n"
		"to stop enter shapes write \"exit\"\n\n";

	CShapeFactory factory;
	CDesigner designer(factory);
	CPictureDraft draft;

	draft = designer.CreateDraft(std::cin);
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Shapes");
	CCanvas canvas(window);

	CPainter painter;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::White);
		painter.DrawPicture(draft, canvas);
		window.display();
	}
	

	return 0;
}