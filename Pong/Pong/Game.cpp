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
	}
}


void Game::shutdown(){

}

void Game::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	//Get keyboard state
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

}

void Game::update()
{
}

void Game::generateOutput()
{
}
