#include "Game.h"

SDL_Renderer* renderer;
const int thickness = 15;
const int screenHeight = 768;
const int screenWidth = 1024;
Vector2 paddlePos, ballPos, ballVelocity;
int paddleDir, paddleHeight, paddleWidth;
int ballHeight, ballWidth;
Uint32 ticksCount;

Game::Game()
{
	isRunning = true;
	window = nullptr;
	ticksCount = 0;

	// Set paddle and ball position
	paddleHeight = thickness * 5;
	paddleWidth = thickness;
	paddlePos.x = thickness;
	paddlePos.y = (screenHeight / 2) - (paddleHeight / 2);

	ballHeight = ballWidth = thickness;
	ballPos.x = screenWidth / 2;
	ballPos.y = screenHeight / 2;
	ballVelocity.x = -200.0f;
	ballVelocity.y = 235.0f;

}

int Game::initialize()
{
	// Init SDL
	SDL_Log("Iniitializing SDL...");
	int result = SDL_Init(SDL_INIT_EVERYTHING);
	if (result != 0)
	{
		SDL_Log("Failed to initialize SDL. Error: %s", SDL_GetError());
	}

	// Create window
	window = SDL_CreateWindow("Pong Thing", 100, 100, 1024, 768, 0);
	if (!window)
	{
		result = -1;
		SDL_Log("Failed to create window: %s", SDL_GetError());
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		result = -1;
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
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
	SDL_DestroyRenderer(renderer);
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
	
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	paddleDir = 0;
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		paddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		paddleDir += 1;
	}
}

void Game::update()
{
	// Wait until 16ms has passed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	// delta time is the number of ticks since last frame (converted to seconds)
	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	ticksCount = SDL_GetTicks();

	// Clamp maximum delta time
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Paddle movement
	if (paddleDir != 0)
	{
		paddlePos.y += paddleDir * 300.0f * deltaTime;

		// If paddle would go off screen, move it back
		if (paddlePos.y < thickness)
		{
			paddlePos.y = thickness;
		}
		else if ((paddlePos.y + paddleHeight) > (screenHeight - thickness))
		{
			paddlePos.y = screenHeight - thickness - paddleHeight;
		}
	}

	// Ball movement
	ballPos.x += ballVelocity.x * deltaTime;
	ballPos.y += ballVelocity.y * deltaTime;

	// Collision detection
	if (ballPos.y <= thickness && ballVelocity.y < 0.0f)
	{
		ballVelocity.y *= -1;
	}
	else if ((ballPos.y + ballHeight) > (screenHeight - thickness) && (ballVelocity.y > 0.0f))
	{
		ballVelocity.y *= -1;
	}
	else if ((ballPos.x + ballWidth) > (screenWidth - thickness) && (ballVelocity.x > 0.0f))
	{
		ballVelocity.x *= -1;
	} else if (	
				// Ball is moving to the left
				(ballVelocity.x < 0.0f) &&
				// Ball is at correct X position
				(ballPos.x <= paddlePos.x + paddleWidth) && (ballPos.x >= paddlePos.x - paddleWidth) &&
				// Ball is at correct Y position
				(ballPos.y >= paddlePos.y) && (ballPos.y <= paddlePos.y + paddleHeight))
	{ 
		ballVelocity.x *= -1;
	}

}

void Game::generateOutput()
{
	// Draw background
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw walls
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_Rect topWall{
		0,
		0,
		1024,
		thickness
	};
	SDL_RenderFillRect(renderer, &topWall);

	SDL_Rect bottomWall{
		0,
		screenHeight-thickness,
		screenWidth,
		thickness
	};
	SDL_RenderFillRect(renderer, &bottomWall);

	SDL_Rect rightWall{
		screenWidth-thickness,
		0,
		thickness,
		screenHeight
	};
	SDL_RenderFillRect(renderer, &rightWall);

	// Drawing paddle and ball
	SDL_Rect ball{
		static_cast<int>(ballPos.x),
		static_cast<int>(ballPos.y),
		ballWidth,
		ballHeight
	};
	SDL_RenderFillRect(renderer, &ball);

	SDL_Rect paddle{
		static_cast<int>(paddlePos.x),
		static_cast<int>(paddlePos.y),
		paddleWidth,
		paddleHeight
	};
	SDL_RenderFillRect(renderer, &paddle);



	SDL_RenderPresent(renderer);
}
