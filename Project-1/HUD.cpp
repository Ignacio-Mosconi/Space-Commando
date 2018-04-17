#include "HUD.h"

HUD::HUD()
{
	_lives = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFA.ttf", 48, "Lives: 3", {32, 128, 32, 255});
	_score = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFA.ttf", 48, "Score: 0", {32, 32, 200, 255});
	_paused = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFO.ttf", 72, "Paused", {32, 128, 32, 255});
	_gameOver = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFO.ttf", 90, "Game Over", {255, 32, 32, 255});
	_highestScore = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFA.ttf", 48, "Highest Score: 0", {200, 200, 200, 255});
	_credits = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFA.ttf", 32, "Made by Ignacio Mosconi - Powered by SDL 2.0",
						{32, 128, 32, 255});
	_escape = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFA.ttf", 48, "ESC: Main Menu", {255, 32, 32, 255});
	_restart = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFA.ttf", 48, "R: Restart", {32, 32, 200, 255});
}

HUD::~HUD()
{
	delete _lives;
	delete _score;
	delete _paused;
	delete _gameOver;
	delete _highestScore;
	delete _credits;
	delete _escape;
	delete _restart;
}

void HUD::updateHUD(Element element, int number)
{
	string text = to_string(number);

	switch (element)
	{
		case Lives:
			if (number > 2)
				_lives->changeText(Window::getSDL_Renderer(), "Lives: " + text, {32, 128, 32, 255});
			else
			{
				if (number == 2)
					_lives->changeText(Window::getSDL_Renderer(), "Lives: " + text, {200, 128, 32, 255});
				else
					_lives->changeText(Window::getSDL_Renderer(), "Lives: " + text, {255, 32, 32, 255});				
			}
			break;
		case Score:
			_score->changeText(Window::getSDL_Renderer(), "Score: " + text, {32, 32, 200, 255});
			break;
		case HighestScore:
			_highestScore->changeText(Window::getSDL_Renderer(), "Highest Score: " + text, {200, 200, 200, 255});
			break;
	}
}

void HUD::draw(bool isPaused, bool isGameOver) const
{
	_lives->draw(Window::getSDL_Renderer(), 64, 0);
	_score->draw(Window::getSDL_Renderer(), Window::getWindowWidth() / 2 - _score->getRectangle().w / 2, 0);
	if (isPaused)
		_paused->draw(Window::getSDL_Renderer(), Window::getWindowWidth() / 2 - _paused->getRectangle().w / 2,
					  Window::getWindowHeight() / 2 - _paused->getRectangle().h / 2);
	if (isGameOver)
	{
		_gameOver->draw(Window::getSDL_Renderer(), Window::getWindowWidth() / 2 - _gameOver->getRectangle().w / 2,
					  Window::getWindowHeight() / 2 - _gameOver->getRectangle().h / 2 - 64);
		_highestScore->draw(Window::getSDL_Renderer(), Window::getWindowWidth() / 2 - _highestScore->getRectangle().w / 2,
							Window::getWindowHeight() / 2 - _highestScore->getRectangle().h / 2 + 128);
		_credits->draw(Window::getSDL_Renderer(), Window::getWindowWidth() / 2 - _credits->getRectangle().w / 2,
							Window::getWindowHeight() * 3 / 4 - _credits->getRectangle().h / 2);
		_escape->draw(Window::getSDL_Renderer(), Window::getWindowWidth() / 4 - _escape->getRectangle().w / 2, 
					  Window::getWindowHeight() * 9 / 10 - _escape->getRectangle().h / 2);
		_restart->draw(Window::getSDL_Renderer(), Window::getWindowWidth() * 3 / 4 - _restart->getRectangle().w / 2,
					   Window::getWindowHeight() * 9 / 10 - _restart->getRectangle().h / 2);
	}
}