#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

enum Sound
{
	Shot, Explosion, Select
};

class Window
{
private:
	SDL_Window* _window = nullptr;
	static SDL_Renderer* _renderer;
	static Mix_Music* _music;
	static Mix_Chunk* _shot;
	static Mix_Chunk* _explosion;
	static Mix_Chunk* _select;
	string _title;
	static int _width;
	static int _height;
	bool _closed;
	
	bool init();

public:
	Window(const string title);
	~Window();
	inline bool isClosed() const { return _closed; }
	static inline int getWindowWidth() { return _width; }
	static inline int getWindowHeight() { return _height; }
	static inline SDL_Renderer* getSDL_Renderer() { return _renderer; }
	static inline Mix_Music* getMix_Music() { return _music; }
	static Mix_Chunk* getMix_Chunk(Sound sound);
	static void logSDL_Error(const string &operation) { cerr << "SDL_" << operation << " Error.\n"; }
	static void logTTF_Error(const string &operation) { cerr << "TTF_" << operation << " Error.\n"; }
	static void logMix_Error(const string &operation) { cerr << "Mix_" << operation << " Error.\n"; }
	void draw() const;
	void close();
};

#endif