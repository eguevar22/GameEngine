#pragma once
#include "Components.h"

#include "../Src/TextureManager.h"
#include "../Src/Game.h"
#include "../Src/AssetManager.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;
	Vector2D position;
	int movementRatio = 1;
	bool isOnScreen = false;

	TileComponent() = default;
	TileComponent(std::string id, int srcX, int srcY, int xPos, int yPos, int size, int scale, int ratio)
	{
		texture = Game::assets->GetTexture(id);
		srcRect.x = srcX;
		srcRect.y = srcY;
		position.x = xPos;
		position.y = yPos;
		dstRect.x = xPos;
		dstRect.y = yPos;
		srcRect.w = size; // remember to change map.cpp line 32 as well
		srcRect.h = size;
		dstRect.w = dstRect.h = size * scale;
		movementRatio = ratio;



	}



	~TileComponent()
	{
		
	}

	void update() override
	{
		
		dstRect.x = static_cast<int>(position.x) - Game::camera.x / movementRatio;
		dstRect.y = static_cast<int>(position.y) - Game::camera.y;


		
	}

	void draw() override
	{
	
			TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
		
		
		
	}


};
