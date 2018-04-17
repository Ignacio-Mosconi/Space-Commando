#ifndef ENTITY_H
#define ENTITY_H
#include "Window.h"

class Entity
{
protected:
	SDL_Texture* _texture = nullptr;
	int _x;
	int _y;

public:
	Entity(){}
	Entity(const string &imagePath);
	~Entity();
	void loadTexture(const string &imagePath);
	inline int getX() { return _x; }
	inline int getY() { return _y; }
	void setPosition(int x, int y) { _x = x; _y = y; }
	virtual void draw() const = 0;
};

#endif
