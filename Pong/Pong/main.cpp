#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	int result = game.initialize();
	if (result == 0)
	{
		game.runLoop();
	}

	game.shutdown();
	return 0;
}