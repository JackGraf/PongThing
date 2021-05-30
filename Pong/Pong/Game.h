#pragma once
#include <SDL.h>

struct Vector2 {
	float x;
	float y;
};

class Game
{
public:
	Game();
	int initialize();
	void runLoop();
	void shutdown();

private:
	void processInput();
	void update();
	void generateOutput();

	// Window created by SDL
	SDL_Window* window;

	bool isRunning;
};