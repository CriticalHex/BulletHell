#pragma once
#include"globals.h"
#include"SFML/Graphics.hpp"

class bullet {
private:
	double xpos;
	double ypos;
	bool isAlive; //kills after edge of screen
	double angle;
	double radius;
	sf::Sprite image;
public:
	bullet();
	bullet(double x, double y, double a);
	bullet(double x, double y, double a, sf::Sprite sprite);
	~bullet();
	void move1();
	void move2();
	void move3();
	void move4();
	void kill();
	void draw(sf::RenderWindow& window);
	bool offScreen();
	bool collide(double x, double y);
};