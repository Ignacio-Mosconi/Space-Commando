#include "Window.h"

SDL_Renderer* Window::_renderer = nullptr;
// You should make a different class for the sounds!
Mix_Music* Window::_music = nullptr;
Mix_Chunk* Window::_shot = nullptr;
Mix_Chunk* Window::_explosion = nullptr;
Mix_Chunk* Window::_select = nullptr;
// The resolution of the screen has to be higher than 1600x900; otherwise, the title bar won't show up.
int Window::_width = 1600;
int Window::_height = 900;

Window::Window(const string title)
{
	_title = title;
	_closed = !init();
}

Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	Mix_FreeMusic(_music);
	Mix_FreeChunk(_shot);
	Mix_FreeChunk(_explosion);
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		logSDL_Error("Init");
		return false;
	}
	
	if (TTF_Init() == -1)
	{
		logTTF_Error("Init");
		return false;
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		logMix_Error("OpenAudio");
		return false;
	}

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, NULL);

	if (!_window)
	{
		logSDL_Error("CreateWindow");
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (!_renderer)
	{
		logSDL_Error("CreateRenderer");
	}

	_music = Mix_LoadMUS("Sounds/Music.wav");

	if (!_music)
	{
		logMix_Error("LoadMUS");
	}
	
	_shot = Mix_LoadWAV("Sounds/Shot.wav");

	if (!_shot)
	{
		logMix_Error("LoadWAV");
	}

	_explosion  = Mix_LoadWAV("Sounds/Explosion.wav");

	if (!_explosion)
	{
		logMix_Error("LoadWAV");
	}

	_select = Mix_LoadWAV("Sounds/Select.wav");

	if (!_select)
	{
		logMix_Error("LoadWAV");
	}

	return true;
}

void Window::draw() const
{
	SDL_RenderPresent(_renderer);
	SDL_SetRenderDrawColor(_renderer, 32, 32, 32, 255);
	SDL_RenderClear(_renderer);
}

void Window::close()
{
	Mix_PauseMusic();
	_closed = true;
}

Mix_Chunk* Window::getMix_Chunk(Sound sound)
{
	switch (sound)
	{
		case Shot:
			return _shot;
			break;
		case Explosion:
			return _explosion;
			break;
		case Select:
			return _select;
			break;
	}
}