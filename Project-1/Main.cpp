#include "Game.h"

int main(int argc, char* argv[])
{
	Game* game = new Game();

	game->showMenu();

	delete game;
	return 0;
}