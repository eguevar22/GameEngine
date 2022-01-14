#pragma once
#include <map>
//#include "Game.h"
#include "TextureManager.h"
#include <array>
#include <vector>
#include "../ECS/Components.h"

class CharacterCollider;
class AutoController;
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


	void CreateWolf(Entity& werewolf, Entity& target, int posX, int posY, int sc)
	{
		Vector2D textureSize{ 73,43 };
		Vector2D colliderSize{ 140,140 };
		
		werewolf.addComponent<TransformComponent>(posX, posY, textureSize.x, textureSize.y, sc);		
		werewolf.addComponent<SpriteComponent>("werewolf", true);		
		werewolf.addComponent<CharacterCollider>("werewolf", posX+50, posY+50, colliderSize.x, colliderSize.y);
		werewolf.addComponent<AutoController>(1125,20, &target);
		werewolf.addGroup(Game::groupEnemies);
		
		

	}

	void DeleteWolf(Entity& werewolf)
	{
		werewolf.delGroup(Game::groupEnemies);
		werewolf.destroy();
		


	}



private:
	std::map< std::string, SDL_Texture*> textures;
	Manager* manager;

};