#include"globals.h"
#include"SFML/Graphics.hpp"
#include"stars.h"
#include<random>


star::star() {
	xpos = rand() % 800 + 1;
	ypos = rand() % 800 + 1;
	RG = rand() % 201;
	blue = rand() % 151 + 100;
	size = rand() % 2 + 1;
}

star::~star() {

}

void star::move() {
	ypos += 10;
}

void star::reposition() {
	if (ypos > 800) {
		ypos = 0;
		xpos = rand() % 800 + 1;
		RG = rand() % 201;
		blue = rand() % 151 + 100;
	}
}

void star::draw(sf::RenderWindow& window) {
	sf::CircleShape shape(size);
	shape.setFillColor(sf::Color(RG, RG, blue));
	shape.setPosition(xpos, ypos);
	window.draw(shape);
}
