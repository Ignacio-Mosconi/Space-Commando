#include "Entity.h"

Entity::Entity(const string &imagePath)
{
	loadTexture(imagePath);
}

Entity::~Entity()
{
	SDL_DestroyTexture(_texture);
}

void Entity::loadTexture(const string &imagePath)
{
	SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str());
	if (!surface)
		Window::logSDL_Error("LoadBMP");
	_texture = SDL_CreateTextureFromSurface(Window::getSDL_Renderer(), surface);
	if (!_texture)
		Window::logSDL_Error("CreateTextureFromSurface");
	SDL_FreeSurface(surface);
}