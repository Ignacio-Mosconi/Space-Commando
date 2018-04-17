#include "Menu.h"

Menu::Menu()
{
	_title = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFO.ttf", 132, "Space Commando", {32, 128, 32, 255});
	_options[0] = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFA.ttf", 72, "Play", {255, 255, 255, 255});
	_options[1] = new Text(Window::getSDL_Renderer(), "Fonts/BatmanFA.ttf", 72, "Exit", {255, 255, 255, 255});
	_color[0] = {255, 255, 255, 255};
	_color[1] = {32, 128, 32, 255};
	_selected[0] = false;
	_selected[1] = false;
}

Menu::~Menu()
{
	delete _title;
	for (int i = 0; i < OPTIONS; i++)
		if (_options[i])
			delete _options[i];
}

void Menu::draw() const
{
	_title->draw(Window::getSDL_Renderer(), Window::getWindowWidth() / 2 - _title->getRectangle().w / 2,
					  Window::getWindowHeight() / 3 - _title->getRectangle().h / 2);
	_options[0]->draw(Window::getSDL_Renderer(), Window::getWindowWidth() / 2 - _options[0]->getRectangle().w / 2,
					  Window::getWindowHeight() / 2 - _options[0]->getRectangle().h / 2 + 64);
	_options[1]->draw(Window::getSDL_Renderer(), Window::getWindowWidth() / 2 - _options[1]->getRectangle().w / 2,
					  Window::getWindowHeight() / 2 - _options[1]->getRectangle().h / 2 + 192);
}

void Menu::updateMenu(int mouseX, int mouseY)
{
	string text;
	_mouseX = mouseX;
	_mouseY = mouseY;

	for (int i = 0; i < OPTIONS; i++)
	{
		switch (i)
		{
			case 0:
				text = "Play";
				break;
			case 1:
				text = "Exit";
				break;
		}

		if ((_mouseX >= _options[i]->getRectangle().x && _mouseX <= _options[i]->getRectangle().x + _options[i]->getRectangle().w) &&
			(_mouseY >= _options[i]->getRectangle().y && _mouseY <= _options[i]->getRectangle().y + _options[i]->getRectangle().h))
		{
			if (!_selected[i])
			{
				Mix_PlayChannel(-1, Window::getMix_Chunk(Select), 0);
				_selected[i] = true;
				_options[i]->changeText(Window::getSDL_Renderer(), text, _color[1]);
			}
		}
		else
			if (_selected[i])
			{
				_selected[i] = false;
				_options[i]->changeText(Window::getSDL_Renderer(), text, _color[0]);
			}
	}
}