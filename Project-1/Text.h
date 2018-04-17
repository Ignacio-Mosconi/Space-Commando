#ifndef TEXT_H
#define TEXT_H
#include "Window.h"
using namespace std;

class Text
{
private:
	TTF_Font* _font = nullptr;
	SDL_Texture* _texture = nullptr;
	mutable SDL_Rect _rectangle;
	
public:
	Text(SDL_Renderer* renderer, const string &fontPath, int fontSize, const string &text, const SDL_Color &color);
	~Text();
	SDL_Texture* loadFont(SDL_Renderer* renderer, const string &fontPath, int fontSize, const string &text, const SDL_Color &color);
	void draw(SDL_Renderer* renderer, int x, int y) const;
	void changeText(SDL_Renderer* renderer, const string &text, SDL_Color color);
	inline SDL_Rect getRectangle() { return _rectangle; }
};

#endif
