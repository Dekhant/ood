#include <SFML/Graphics.hpp>
#include <iostream>
#include "Processing.h"
#include "CBody.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <vector>

using namespace std;

string INPUTFILE = "input.txt";
string OUTPUTFILE = "output.txt";

int main()
{
	vector<sf::Shape*> shapes;
	Reading(shapes, INPUTFILE);
	GetParams(shapes, OUTPUTFILE);
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

    for (sf::Shape* shape : shapes)
    {
        window.draw(*shape);
    }
    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}