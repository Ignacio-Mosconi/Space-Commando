#include "Game.h"

Game::Game()
{
	srand(time(0));
	_window = new Window("Space Commando");
	_player = new Player(32, Window::getWindowHeight() / 2, 3, "Assets/Spaceship.bmp");
	_pBullets = _player->getBullets();
	for (int i = 0; i < ASTEROIDS; i++)
		_asteroids[i] = new Asteroid("Assets/Asteroid.bmp");
	_hud = new HUD();
	_mainMenu = new Menu();
	
	_start = false;
	_paused = false;
	_gameOver = false;
	_score = 0;
	_highestScore = 0;
}

Game::~Game()
{
	if (_player)
		delete _player;
	if (_window)
		delete _window;
	for (int i = 0; i < ASTEROIDS; i++)
	{
		if (_asteroids[i])
			delete _asteroids[i];
	}
	if (_hud)
		delete _hud;
	if (_mainMenu)
		delete _mainMenu;
}

void Game::play()
{
	Mix_PlayMusic(Window::getMix_Music(), -1);

	while (!_gameOver && !_window->isClosed())
	{
		if (!_paused)
		{
			input();
			update();
			draw();
		}
		else
			while (_paused)
			{
				draw();
				resume();
			}
	}
	result();
}

void Game::input()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
		switch (event.type)
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_UP:
						_player->move(Up);
						break;
					case SDLK_DOWN:
						_player->move(Down);
						break;
					case SDLK_LEFT:
						_player->move(Left);
						break;
					case SDLK_RIGHT:
						_player->move(Right);
						break;
					case SDLK_SPACE:
						_player->shoot();
						break;
					case SDLK_ESCAPE:
						Mix_PlayChannel(-1, Window::getMix_Chunk(Select), 0);
						_paused = true;
						break;
				}
				break;
			case SDL_QUIT:
				_window->close();
				break;
		}
}

void Game::update()
{
	Bullet* pAux = _pBullets;

	for (int i = 0; i < PLAYER_BULLETS; i++)
	{
		if (pAux->isEnabled())
			pAux->move();
		pAux++;
	}

	pAux = _pBullets;

	for (int i = 0; i < ASTEROIDS; i++)
		if (_asteroids[i])
		{
			_asteroids[i]->move();
			playerAsteroidCollision(_player, _asteroids[i]);
			for (int j = 0; j < PLAYER_BULLETS; j++)
			{
				if (pAux->isEnabled())
				{
					bulletAsteroidCollision(pAux, _asteroids[i]);
					break;
				}
				pAux++;
			}
		}
}

void Game::draw()
{
	_window->draw();
	if (_player)
		_player->draw();
	
	Bullet* pAux = _pBullets;
	
	for (int i = 0; i < PLAYER_BULLETS; i++)
	{
		if (pAux->isEnabled())
			pAux->draw();
		pAux++;
	}

	for (int i = 0; i < ASTEROIDS; i++)
		if (_asteroids[i])
			_asteroids[i]->draw();
	
	_hud->draw(_paused, _gameOver);
}

void Game::playerAsteroidCollision(Player* p, Asteroid* a)
{
	if ((p->getX() + PLAYER_WIDTH >= a->getX() && p->getX() <= a->getX() + ASTEROID_WIDTH) &&
		(p->getY() + PLAYER_HEIGHT >= a->getY() && p->getY() <= a->getY() + ASTEROID_HEIGHT))
	{
		Mix_PlayChannel(-1, Window::getMix_Chunk(Explosion), 0);

		p->loseLife();
		if (p->getLives() > 0)
		{
			_hud->updateHUD(Lives, p->getLives());
			p->setPosition(PLAYER_MIN_X, Window::getWindowHeight() / 2);
			a->setPosition(ASTEROID_MAX_X, rand() % (ASTEROID_MAX_Y - ASTEROID_MIN_Y - ASTEROID_HEIGHT) + ASTEROID_MIN_Y);
			a->setSpeed(rand() % (ASTEROID_MAX_SPEED - ASTEROID_MIN_SPEED) + ASTEROID_MIN_SPEED);
		}
		else
			_gameOver = true;
	}
}

void Game::bulletAsteroidCollision(Bullet* b, Asteroid* a)
{
	if ((b->getX() + BULLET_WIDTH >= a->getX() && b->getX() <= a->getX() + ASTEROID_WIDTH) &&
		(b->getY() + BULLET_HEIGHT >= a->getY() && b->getY() <= a->getY() + ASTEROID_HEIGHT))
	{
		Mix_PlayChannel(-1, Window::getMix_Chunk(Explosion), 0);

		_score += 5;
		_hud->updateHUD(Score, _score);
		b->disable();
		a->setPosition(ASTEROID_MAX_X, rand() % (ASTEROID_MAX_Y - ASTEROID_MIN_Y - ASTEROID_HEIGHT) + ASTEROID_MIN_Y);
		a->setSpeed(rand() % (ASTEROID_MAX_SPEED - ASTEROID_MIN_SPEED) + ASTEROID_MIN_SPEED);
	}
}

void Game::resume()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
		switch (event.type)
		{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						Mix_PlayChannel(-1, Window::getMix_Chunk(Select), 0);
						_paused = false;
						break;
				}
				break;
			case SDL_QUIT:
				_paused = false;
				_window->close();
				break;
		}
}

void Game::result()
{
	Mix_FadeOutMusic(1000);
	if (_score > _highestScore)
	{
		_highestScore = _score;
		_hud->updateHUD(HighestScore, _highestScore);
	}
	while (_start && !_window->isClosed())
	{
		SDL_Event event;

		draw();
		if (SDL_PollEvent(&event))
			switch (event.type)
			{
				case SDL_QUIT:
					_window->close();
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							_start = false;
							reset();
							showMenu();
							break;
						case SDLK_r:
							reset();
							play();
							break;
					}
					break;
			}
	}
}

void Game::showMenu()
{
	while (!_start && !_window->isClosed())
	{
		menuInput();
		_window->draw();
		_mainMenu->draw();
	}
	if (_start)
		play();
}

void Game::menuInput()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
		switch (event.type)
		{
			case SDL_QUIT:
				_window->close();
				break;
			case SDL_MOUSEMOTION:
				_mainMenu->updateMenu(event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				for (int i = 0; i < OPTIONS; i++)
					if (_mainMenu->isSelected(i))
						switch (i)
						{
							case 0:
								Mix_PlayChannel(-1, Window::getMix_Chunk(Select), 0);
								_start = true;
								break;
							case 1:
								_window->close();
								break;
						}
		}
}

void Game::reset()
{
	Bullet* pAux = _pBullets;

	_player->setLives(3);
	_player->setPosition(PLAYER_MIN_X, Window::getWindowHeight() / 2);
	for (int i = 0; i < PLAYER_BULLETS; i++)
		if (pAux->isEnabled())
			pAux->disable();
	for (int i = 0; i < ASTEROIDS; i++)
	{
		_asteroids[i]->setPosition(ASTEROID_MAX_X - ASTEROID_WIDTH,
								   rand() % (ASTEROID_MAX_Y - ASTEROID_MIN_Y - ASTEROID_HEIGHT) + ASTEROID_MIN_Y);
		_asteroids[i]->setSpeed(rand() % (ASTEROID_MAX_SPEED - ASTEROID_MIN_SPEED) + ASTEROID_MIN_SPEED);
	}

	_paused = false;
	_gameOver = false;
	_score = 0;
	_hud->updateHUD(Lives, _player->getLives());
	_hud->updateHUD(Score, _score);
}