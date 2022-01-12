#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();
	game->init("GameWindow", 800, 640, true);
	//game->init("GameWindow", 1500, 10, false);
	//SDL_SetWindowSize

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	int frameTime;
	Uint32 frameStart;




	while (game->running())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}