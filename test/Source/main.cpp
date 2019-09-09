#include "Game.h"

int main()
{
	Game game(sf::VideoMode(800,800), "Hello, World!");

	while (game.isRunning())
	{
		game.update();
		game.render();
		game.events();
	}

	return 0;
}