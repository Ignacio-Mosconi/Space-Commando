#ifndef ASTEROID_H
#define ASTEROID_H
#include "Window.h"
#include "Entity.h"
#define ASTEROID_WIDTH 64
#define ASTEROID_HEIGHT 45
#define ASTEROID_MIN_X 0
#define ASTEROID_MIN_Y 135
#define ASTEROID_MAX_X Window::getWindowWidth()
#define ASTEROID_MAX_Y Window::getWindowHeight() - 45
#define ASTEROID_MIN_SPEED 2
#define ASTEROID_MAX_SPEED 16

class Asteroid : public Entity
{
private:
	int _speed;

public:
	Asteroid(const string &imagePath);
	void setSpeed(int speed) { _speed = speed; }
	void draw() const;
	void move();
};

#endif