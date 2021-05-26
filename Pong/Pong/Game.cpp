#include "Game.h"

Game::Game()
{
	isRunning = true;
	window = nullptr;
}

int Game::initialize()
{
	SDL_Log("Iniitializing SDL...");
	int result = SDL_Init(SDL_INIT_EVERYTHING);
	if (result != 0)
	{
		SDL_Log("Failed to initialize SDL. Error: %s", SDL_GetError());
	}

	window = SDL_CreateWindow("Pong Thing", 100, 100, 1024, 768, 0);

	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
	}
	return result;
}

void Game::runLoop()
{
	while (isRunning)
	{
		processInput();
		update();
		generateOutput();
		// Adding this so it doesn't freeze up LOL
		isRunning = false;
	}
}


void Game::shutdown(){

}

void Game::processInput()
{
}

void Game::update()
{
}

void Game::generateOutput()
{
}
