#ifndef PLAYER_H
#define PLAYER_H
#include "Window.h"
#include "Entity.h"
#include "Bullet.h"
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 90
#define PLAYER_MIN_X 32
#define PLAYER_MIN_Y 135
#define PLAYER_MAX_X Window::getWindowWidth() - 32
#define PLAYER_MAX_Y Window::getWindowHeight() - 45
#define PLAYER_X_SPEED 64
#define PLAYER_Y_SPEED 45
#define PLAYER_BULLETS 10

enum Direction
{
	Up, Down, Left, Right
};

class Player : public Entity
{
private:
	Bullet* _bullets;
	int _lives;
	int _xSpeed;
	int _ySpeed;
	int _shotTimer;

public:
	Player(int x, int y, int lives, const string &imagePath);
	~Player();
	void draw() const;
	void move(Direction dir);
	void shoot();
	inline int getLives(){ return _lives; }
	Bullet* getBullets(){ return _bullets; }
	void loseLife() { _lives--; }
	void setLives(int lives) { _lives = lives; }
};

#endif