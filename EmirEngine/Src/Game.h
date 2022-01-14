#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class TileCollider;
class AssetManager;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();



	static SDL_Renderer* renderer;

	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static int tileSize;
	static int worldWidth;
	static AssetManager* assets;
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupEnemies,
		groupTileColliders



	};

	enum Levels : std::size_t
	{
		Level1,
		Level2

	};

private:


	SDL_Window *window;
	Uint32 pixelFormat;
	SDL_Texture* layerTex;
	int wWidth;
	int wHeight;

};