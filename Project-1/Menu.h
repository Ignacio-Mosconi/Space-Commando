#ifndef MENU_H
#define MENU_H
#include "Text.h"
#define OPTIONS 2

class Menu
{
private:
	Text* _title = nullptr;
	Text* _options[OPTIONS];
	bool _selected[OPTIONS];
	SDL_Color _color[2];
	int _mouseX;
	int _mouseY;

public:
	Menu();
	~Menu();
	void draw() const;
	void updateMenu(int mouseX, int mouseY);
	bool isSelected(int option) { return _selected[option]; }
	void setMouseX(int mouseX) { _mouseX = mouseX; }
	void setMouseY(int mouseY) { _mouseY = mouseY; }
};

#endif
