#include "ColliderComponent.h"

void CharacterCollider::checkCollision(Entity * enemy)
{

	SDL_Rect characterCol = entity->getComponent<CharacterCollider>().collider;
	SDL_Rect enemyCol = enemy->getComponent<CharacterCollider>().collider;
	bool blocking = entity->getComponent<TransformComponent>().isbeingHit;
	//std::cout << blocking;
	if (!blocking && Collision::AABB(characterCol, enemyCol ) )

	{

		entity->getComponent<TransformComponent>().currentHealth -= 1;
		//entity->getComponent<TransformComponent>().isbeingHit = true;
		entity->getComponent<TransformComponent>().receivePunch(enemy);


		if (entity->getComponent<TransformComponent>().currentHealth <= 0)
		{
			
			entity->getComponent<SpriteComponent>().Animate("playerDie", 100);
			std::cout << "the entity " << "player " << "destroyed" << std::endl;

		}
		else
		{
			//std::cout << enemy->getComponent<TransformComponent>().currentHealth;
			entity->getComponent<SpriteComponent>().Animate("playerHurt", 75);
		}


	}


}
