#include "Projectile.h"
#include "../Src/Game.h"
#include "../Src/Collision.h"
//#include "Components.h"
ProjectileComponent::ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel)
{
}

ProjectileComponent::~ProjectileComponent()
{
}

void ProjectileComponent::init()
{
	transform = &entity->getComponent<TransformComponent>();
	sprite = &entity->getComponent<SpriteComponent>();
	transform->velocity = velocity;
}

void ProjectileComponent::update()
{
	distance += speed;
	transform->position.x += speed; ;

	if (distance > range)
	{
		std::cout << "Out of Range" << std::endl;
		entity->destroy();
		entity->delGroup(Game::groupProjectiles);
	}
	else if (transform->position.x > Game::camera.x + Game::camera.w ||
		transform->position.x < Game::camera.x )
	{
		std::cout << "Out of bounds!" << std::endl;
		entity->destroy();
		entity->delGroup(Game::groupProjectiles);
	}
}


void ProjectileComponent::checkCollision(Entity* enemy)
{
	SDL_Rect arrowCol = entity->getComponent<CharacterCollider>().collider;
	SDL_Rect enemyCol = enemy->getComponent<CharacterCollider>().collider;
	if (Collision::AABB(arrowCol, enemyCol))

	{
		std::cout << "arrow hit enemy!!!" <<"its current life is" << --enemy->getComponent<TransformComponent>().currentHealth<< std::endl;
		entity->destroy();
		enemy->getComponent<TransformComponent>().currentHealth -= 1;
		if (enemy->getComponent<TransformComponent>().currentHealth <= 0)

		{
			enemy->getComponent<TransformComponent>().isAlive = false;
			enemy->getComponent<SpriteComponent>().Animate("Die", 250);

		}
		else
		{
			std::cout << enemy->getComponent<TransformComponent>().currentHealth;
			enemy->getComponent<SpriteComponent>().Animate("Hurt", 75);
		}


	}


}