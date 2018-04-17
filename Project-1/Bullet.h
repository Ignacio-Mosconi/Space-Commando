#ifndef BULLET_H
#define BULLET_H
#include "Window.h"
#include "Entity.h"
#define BULLET_WIDTH 48
#define BULLET_HEIGHT 18
#define BULLET_MAX_X Window::getWindowWidth()
#define BULLET_SPEED 32

class Bullet : public Entity
{
private:
	int _speed;
	bool _enabled;

public:
	Bullet();
	void draw() const;
	inline bool isEnabled(){ return _enabled; }
	void enable() { _enabled = true; }
	void disable() { _enabled = false; }
	void move();
};

#endif