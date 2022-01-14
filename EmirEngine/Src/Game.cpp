#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "../ECS/Components.h"	
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include "Clock.h"
//comment

Manager manager;
AssetManager* Game::assets = new AssetManager(&manager);
SDL_Event Game::event;
bool Game::isRunning = false;
SDL_Rect Game::camera{ 0,0,1200, 640 };
//SDL_Rect camera2{ 0,0,100*16, 80*16 };
int Game::tileSize = 16;
int Game::worldWidth = 3500;

SDL_Renderer* Game::renderer = nullptr;
Map* map = nullptr;
auto& player(manager.addEntity());
auto& werewolf(manager.addEntity());
auto& werewolf2(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	//flags = SDL_WINDOW_RESIZABLE;
	/*if (!fullscreen)
	{

	}*/



	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		SDL_SetWindowSize(window, 800, 640);
		//SDL_SetWindowFullscreen(window, 0);
		//SDL_SetWindowSize(window, width, height);



		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		SDL_RenderSetLogicalSize(renderer, 1280, 1024);

		isRunning = true;
	}
	assets->AddTexture("terrain", "C:/Dev/EmirEngine/EmirEngine/EmirEngine/assets/myTerrain_ss.png");
	//assets->AddTexture("water", "C:/Dev/EngineTester/Tester/Tester/water.png");

	assets->AddTexture("player", "assets/player_animation.png");
	//assets->AddTexture("werewolf", "assets/werewolf_animation.png");
	assets->AddTexture("werewolf", "assets/werewolf.png");
	assets->AddTexture("arrow", "assets/arrow.png");
	std::cout << assets->GetTexture("arrow");

	map = new Map(100, 22);
	map->LoadMap(Level1);

	player.addComponent<TransformComponent>(300, 0, 50, 37, 5);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<CharacterCollider>("player", 380, 40, 80, 150);
	//player.addComponent<CharacterCollider>("player", 300, 0, 50*5, 37*5);
	player.addGroup(groupPlayers);


	assets->CreateWolf(werewolf, player, 480, 532, 5);
	/*werewolf.addComponent<TransformComponent>(480, 532, 73, 43, 5);
	werewolf.addComponent<SpriteComponent>("werewolf", true);
	werewolf.addComponent<CharacterCollider>("werewolf", 530, 562, 140, 180);
	werewolf.addComponent<AutoController>(1125, &player);
	werewolf.addGroup(groupEnemies);*/
		





	//arrow.addComponent<CharacterCollider>("projectile");
	//arrow.addGroup(Game::groupProjectiles);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));
auto& enemies(manager.getGroup(Game::groupEnemies));

void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}
Clock clock;
void Game::update()
{
	SDL_GetWindowSize(window, &wWidth, &wHeight);
	//std::cout << wWidth << " " << wHeight << std::endl;
	SDL_Rect playerCol = player.getComponent<CharacterCollider>().collider;
	//std::cout <<"player col is "<< playerCol.y + playerCol.h << std::endl;
	//SDL_Rect werewolfCol = werewolf.getComponent<CharacterCollider>().collider;	
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	int playerH = player.getComponent<TransformComponent>().h;;

	manager.refresh();
	manager.update();
	player.getComponent<TransformComponent>().isColliding = false;
	for (auto& c : colliders)	
	{


		SDL_Rect cCol = c->getComponent<TileCollider>().collider;
		//int colY = c->getComponent<TransformComponent>().position.y;

		//check if any of the ground blocks is colliding with the player
		//here I erased cCol.y > playerCol.y +50
		cCol.y -= cCol.h;
		//std::cout << cCol.y << std::endl;;
		if ((Collision::AABB(cCol, playerCol)) && (playerPos.y + playerH < cCol.y))
		{

			//std::cout << playerCol.h << std::endl;
			// if so, prevent the player from falling

			player.getComponent<TransformComponent>().collide();
		}	
	}

	if (!player.getComponent<TransformComponent>().isColliding && !player.getComponent<TransformComponent>().isAttacking)
	{
		player.getComponent<TransformComponent>().Fall();
	}
	/*if (werewolf.isActive() && !werewolf.getComponent<TransformComponent>().isColliding && !werewolf.getComponent<TransformComponent>().isAttacking)
	{
		werewolf.getComponent<TransformComponent>().Fall();
	}*/
	camera.x = player.getComponent<TransformComponent>().position.x - camera.w / 2;
	//camera.y = player.getComponent<TransformComponent>().position.y - 320;

	//camera.h = 0;
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.x > worldWidth)
	{
		camera.x = worldWidth;
	}

	if (player.getComponent<TransformComponent>().position.x > camera.w + camera.x + 400)
	{
		player.getComponent<TransformComponent>().position.x = 0;
		for (auto& t : tiles)
		{
			t->destroy();
		}

		for (auto& c : colliders)
		{
			c->destroy();
		}



		assets->DeleteWolf(werewolf);
		//assets->CreateWolf(werewolf, player, 480, 532, 5);
		werewolf2.addComponent<TransformComponent>(2500, 732, 73, 43, 5);
		werewolf2.addComponent<SpriteComponent>("werewolf", true);
		werewolf2.addComponent<CharacterCollider>("werewolf2", 2650, 762, 140, 180);
		werewolf2.addComponent<AutoController>(900, &player);
		werewolf2.addGroup(groupEnemies);


		map->LoadMap(Level2);
		render();

	}
}
void Game::render()
{
	SDL_RenderClear(renderer);


	for (auto& t : tiles)
	{
		t->draw();
	}

	/*for (auto& c : colliders)
	{
		c->draw();
	}*/

	for (auto& p : players)
	{
		p->draw();


	}

	for (auto& p : projectiles)
	{
		p->draw();
		//p->delGroup(Game::groupProjectiles);
		//std::cout << p->isActive() << std::endl;
	
		for (auto& e : enemies)
		{


			p->getComponent<ProjectileComponent>().checkCollision(e);

		}
	}

	for (auto& e : enemies)
	{
		//std::cout << "enemy is being drawn" << std::endl;
		//std::cout << "the position of the werewolf is " <<e->getComponent < SpriteComponent >().dRec.x << std::endl;
		//std::cout << "the position of the player  is " << player.getComponent < SpriteComponent >().dRec.x << std::endl;
		//std::cout <<"and the camera is at "<< Game::camera.x << std::endl;
		e->draw();
		player.getComponent<CharacterCollider>().checkCollision(e);
	}

	//werewolf.draw();
	//arrow.draw();

	//werewolf2.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
