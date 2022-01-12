#pragma once
#include <map>
//#include "Game.h"
#include "TextureManager.h"
#include <array>
#include <vector>
#include "../ECS/Components.h"

class AssetManager
{
public:
	AssetManager(Manager* man) : manager(man) {}
	~AssetManager()
	{


	}
	/*void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
	{
		auto& projectile(manager->addEntity());
		projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
		//projectile.addComponent<SpriteComponent>(id);
		//projectile.addComponent<ProjectileComponent>(range, speed, vel);
		//projectile.addComponent<ColliderComponent>("projectile");
		//projectile.addGroup(Game::groupProjectiles);
	}*/
	void AddTexture(std::string tag, const char* path)
	{
		textures.emplace(tag, TextureManager::LoadTexture(path));

	}

	SDL_Texture* GetTexture(std::string tag)
	{
		return textures[tag];
	}


private:
	std::map< std::string, SDL_Texture*> textures;
	Manager* manager;

};