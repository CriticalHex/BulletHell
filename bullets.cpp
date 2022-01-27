#include"bullets.h"
#include"globals.h"
#include"SFML/Graphics.hpp"
#include<math.h>
bullet::bullet() { //default constructor
	xpos = 0;
	ypos = 0;
	isAlive = true;
	angle = 0;
	radius = 0;

}
bullet::bullet(double x, double y, double a, sf::Sprite sprite) {//constructor
	xpos = x;
	ypos = y;
	isAlive = true;
	angle = a;
	radius = 10;
	image = sprite;
}
bullet::~bullet() {//destructor

}
bullet::bullet(double x, double y, double a) {
	xpos = x;
	ypos = y;
	isAlive = true;
	angle = a;
	radius = 10;
}

void bullet::move1() {
	angle += .1;
	if (angle > 6.28)
		angle = 0;
	xpos = xpos + cos(angle) * (radius) / 2;
	ypos = ypos + sin(angle) * (radius) / 2 + 1;
	
}


void bullet::move2() {
	angle += .01;
	if (angle > 6.28)
		angle = 0;
	xpos = xpos - cos(angle) * (radius) / 2;
	ypos = ypos + sin(angle) * (radius) / 6;
}
void bullet::move3() {
	angle += .01;
	if (angle > 6.28)
		angle = 0;
	xpos = xpos + cos(angle) * (radius) / 4;
	ypos++;
}
void bullet::move4() {
	angle += .3;
	if (angle > 6.28)
		angle = 0;
	xpos = xpos + cos(angle) * (radius) / 4;
	ypos = ypos + sin(angle) * (radius) / 2 + 1;
}
void bullet::kill() {
	isAlive = false;
}

void bullet::draw(sf::RenderWindow& window) {
	sf::CircleShape shape(5);
	shape.setFillColor(sf::Color(100, 250, 50));

	if (isAlive) {
		shape.setPosition(xpos, ypos);
		window.draw(shape);
	}
}

bool bullet::offScreen() {
	if (xpos > (SCREEN_W + 400) || ypos > SCREEN_H || ypos < -400 || xpos < -400)
		return true;
	else
		return false;

}
bool bullet::collide(double x, double y) {
	if (sqrt((x - xpos) * (x - xpos) + (y - ypos) * (y - ypos)) < 15) {

		return true;
	}
	else
		return false;

}