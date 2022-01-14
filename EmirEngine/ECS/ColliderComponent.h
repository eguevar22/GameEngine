#pragma once
#include "Components.h"
#include "../Src/Collision.h"
class Collision;

class TileCollider : public Component
{
public:
	SDL_Rect collider;
	SDL_Rect srcRect, dstRect;
	SDL_Texture* tex;
	std::string tag;
	TransformComponent* transform;
	//SpriteComponent* sprite;


	TileCollider(std::string t)
	{
		tag = t;
	}

	TileCollider(std::string t, int x, int y, int size)
	{
		tag = t;
		collider.x = x;
		collider.y = y;
		collider.h = collider.w = size;
	}

	TileCollider(std::string t, int x, int y, int w, int h)
	{
		tag = t;
		collider.x = x;
		collider.y = y;
		collider.h = h;
		collider.w = w;
	}

	~TileCollider()
	{
		//SDL_DestroyTexture(tex);
	}

	void init() override
	{
		/*if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}*/
		transform = &entity->getComponent<TransformComponent>();




		tex = TextureManager::LoadTexture("assets/collider.png");



		srcRect = { 0 , 0 , Game::tileSize , Game::tileSize };
		dstRect = { collider.x ,  collider.y ,  collider.w ,  collider.h };





	}

	void update() override
	{


		dstRect.x = collider.x - Game::camera.x;
		dstRect.y = collider.y - Game::camera.y;
	}


	void draw() override
	{

		TextureManager::Draw(tex, srcRect, dstRect, SDL_FLIP_NONE);

	}
};


class CharacterCollider : public Component
{


public:


	SDL_Rect collider;
	SDL_Rect srcRect, dstRect;
	SDL_Texture* tex;
	std::string tag;
	TransformComponent* transform;
	int heightDiff = 0;
	int widthDiff = 0;
	SpriteComponent* sprite;
	int centeredXPos = 0;


	CharacterCollider(std::string t, int x, int y, int w, int h)
	{
		tag = t;
		collider.x = x;
		collider.y = y;
		collider.h = h;
		collider.w = w;
	}

	void init() override
	{

		//transform = &entity->getComponent<TransformComponent>();
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		tex = TextureManager::LoadTexture("assets/collider.png");

		heightDiff = collider.y - transform->position.y;
		widthDiff = collider.x - transform->position.x;
		srcRect = { 0 , 0 , transform->w  , transform->h };
		dstRect = { collider.x  ,  collider.y , collider.w, collider.h };

	}

	void update() override


	{

		//widthDiff = collider.x - transform->position.x;

		if (sprite->flip == SDL_FLIP_NONE)
		{
			collider.x = static_cast<int> (transform->position.x - widthDiff - collider.w + transform->w*transform->sc);

		}

		else
		{
			collider.x = static_cast<int> (transform->position.x + widthDiff);

		}


		collider.y = static_cast<int>(transform->position.y + heightDiff);
		dstRect.x = collider.x - Game::camera.x;
		dstRect.y = collider.y - Game::camera.y;

		dstRect.w = collider.w;
		//collider.h = transform->h* transform->sc;
		dstRect.h = collider.h;
		//centeredXPos = (dstRect.x + dstRect.w) / 2;
		//std::cout << transform->position.y << std::endl;


			//std::cout <<transform->h <<std::endl;		
	}

	void draw() override
	{
		//TextureManager::Draw(tex, srcRect, dstRect, SDL_FLIP_NONE);
	}

	void checkCollision(Entity* enemy);

};