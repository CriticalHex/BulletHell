#pragma once
#include"globals.h"
#include"SFML/Graphics.hpp"

class star {
private:
	double xpos;
	double ypos;
	int RG;
	int blue;
	int size;
public:
	star();
	~star();
	void move();
	void reposition();
	void draw(sf::RenderWindow& window);
};