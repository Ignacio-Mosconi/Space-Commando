#include "Player.h"

Player::Player(int x, int y, int lives, const string &imagePath): Entity(imagePath)
{
	_bullets = new Bullet[PLAYER_BULLETS];
	Bullet* pAux = _bullets;
	for (int i = 0; i < PLAYER_BULLETS; i++)
	{
		pAux->loadTexture("Assets/Bullet.bmp");
		pAux++;
	}
		
	_x = PLAYER_MIN_X;
	_y = Window::getWindowHeight() / 2;
	_lives = lives;
	_xSpeed = PLAYER_X_SPEED;
	_ySpeed = PLAYER_Y_SPEED;
	_shotTimer = 0;
}

Player::~Player()
{
	delete[] _bullets;
}

void Player::draw() const
{
	SDL_Rect rectangle;

	rectangle.w = PLAYER_WIDTH;
	rectangle.h = PLAYER_HEIGHT;
	rectangle.x = _x;
	rectangle.y = _y;

	SDL_RenderCopy(Window::getSDL_Renderer(), _texture, nullptr, &rectangle);
}

void Player::move(Direction dir)
{
	switch (dir)
	{
		case Up:
			if (_y - _ySpeed > PLAYER_MIN_Y)
				_y -= _ySpeed;
			else
				_y = PLAYER_MIN_Y;
			break;
		case Down:
			if (_y + PLAYER_HEIGHT + _ySpeed < PLAYER_MAX_Y)
				_y += _ySpeed;
			else
				_y = PLAYER_MAX_Y - PLAYER_HEIGHT;
			break;
		case Left:
			if (_x - _xSpeed > PLAYER_MIN_X)
				_x -= _xSpeed;
			else
				_x = PLAYER_MIN_X;
			break;
		case Right:
			if (_x + PLAYER_WIDTH + _xSpeed < PLAYER_MAX_X)
				_x += _xSpeed;
			else
				_x = PLAYER_MAX_X - PLAYER_WIDTH;
			break;
	}
}

void Player::shoot()
{
	if (_shotTimer == 0)
	{
		Mix_PlayChannel(-1, Window::getMix_Chunk(Shot), 0);
		Bullet* pAux = _bullets;
		_shotTimer = 1;

		for (int i = 0; i < PLAYER_BULLETS; i++)
		{
			if (!pAux->isEnabled())
			{
				pAux->setPosition(_x + PLAYER_WIDTH, _y + PLAYER_HEIGHT / 2);
				pAux->enable();
				break;
			}
			pAux++;
		}
	}
	else
		_shotTimer--;
}