#ifndef GAME_H
#define GAME_H
#include <ctime>
#include "Window.h"
#include "Player.h"
#include "Asteroid.h"
#include "HUD.h"
#include "Menu.h"
#define ASTEROIDS 5

class Game
{
private:
	Window* _window = nullptr;
	Player* _player = nullptr;
	Bullet* _pBullets = nullptr;
	Asteroid* _asteroids[ASTEROIDS];
	HUD* _hud = nullptr;
	Menu* _mainMenu = nullptr;
	
	bool _start;
	bool _gameOver;
	bool _paused;
	int _score;
	int _highestScore;

	void input();
	void update();
	void draw();

	void playerAsteroidCollision(Player* p, Asteroid* a);
	void bulletAsteroidCollision(Bullet* b, Asteroid* a);
	
	void resume();
	void result();
	void reset();
	void menuInput();

public:
	Game();
	~Game();
	void showMenu();
	void play();
};

#endif