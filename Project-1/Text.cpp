#include "Text.h"

Text::Text(SDL_Renderer* renderer, const string &fontPath, int fontSize, const string &text, const SDL_Color &color)
{
	_texture = loadFont(renderer, fontPath, fontSize, text, color);
	SDL_QueryTexture(_texture, nullptr, nullptr, &_rectangle.w, &_rectangle.h);
}

Text::~Text()
{
	SDL_DestroyTexture(_texture);
}

SDL_Texture* Text::loadFont(SDL_Renderer* renderer, const string &fontPath, int fontSize, const string &text, const SDL_Color &color)
{
	_font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!_font)
	{
		Window::logTTF_Error("OpenFont");
		return nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(_font, text.c_str(), color);
	if (!surface)
	{
		Window::logTTF_Error("RenderText_Solid");
		TTF_CloseFont(_font);
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture)
		Window::logSDL_Error("CreateTextureFromSurface");

	SDL_FreeSurface(surface);
	return texture;
}

void Text::draw(SDL_Renderer* renderer, int x, int y) const
{
	_rectangle.x = x;
	_rectangle.y = y;
	SDL_RenderCopy(renderer, _texture, nullptr, &_rectangle);
}

void Text::changeText(SDL_Renderer* renderer, const string &text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(_font, text.c_str(), color);
	if (!surface)
	{
		Window::logTTF_Error("RenderText_Solid");
		TTF_CloseFont(_font);
	}

	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!_texture)
		Window::logSDL_Error("CreateTextureFromSurface");

	SDL_FreeSurface(surface);
	SDL_QueryTexture(_texture, nullptr, nullptr, &_rectangle.w, &_rectangle.h);
}