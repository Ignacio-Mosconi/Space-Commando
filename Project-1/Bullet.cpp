#include "Bullet.h"

Bullet::Bullet()
{
	_enabled = false;
	_speed = BULLET_SPEED;
}

void Bullet::draw() const
{
	SDL_Rect rectangle;

	rectangle.w = BULLET_WIDTH;
	rectangle.h = BULLET_HEIGHT;
	rectangle.x = _x;
	rectangle.y = _y;

	SDL_RenderCopy(Window::getSDL_Renderer(), _texture, nullptr, &rectangle);
}
void Bullet::move()
{
	if (_x < BULLET_MAX_X)
		_x += _speed;
	else
		_enabled = false;
}