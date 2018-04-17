#include "Asteroid.h"

Asteroid::Asteroid(const string &imagePath): Entity(imagePath)
{
	_x = ASTEROID_MAX_X - ASTEROID_WIDTH;
	_y = rand() % (ASTEROID_MAX_Y - ASTEROID_MIN_Y - ASTEROID_HEIGHT) + ASTEROID_MIN_Y;
	_speed = rand() % (ASTEROID_MAX_SPEED - ASTEROID_MIN_SPEED) + ASTEROID_MIN_SPEED;
}

void Asteroid::draw() const
{
	SDL_Rect rectangle;

	rectangle.w = ASTEROID_WIDTH;
	rectangle.h = ASTEROID_HEIGHT;
	rectangle.x = _x;
	rectangle.y = _y;

	SDL_RenderCopy(Window::getSDL_Renderer(), _texture, nullptr, &rectangle);
}

void Asteroid::move()
{
	if (_x > ASTEROID_MIN_X)
		_x -= _speed;
	else
	{
		_x = ASTEROID_MAX_X;
		_y = rand() % (ASTEROID_MAX_Y - ASTEROID_MIN_Y - ASTEROID_HEIGHT) + ASTEROID_MIN_Y;
		_speed = rand() % (ASTEROID_MAX_SPEED - ASTEROID_MIN_SPEED) + ASTEROID_MIN_SPEED;
	}
}