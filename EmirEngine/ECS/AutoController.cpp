#include "AutoController.h"



AutoController::AutoController(int mdst,int strength, Entity* mTarget)
{
	target = mTarget;
	movementDist = mdst;
	hitStrength = strength;
	//collider = entity->ge tComponent<CharacterCollider>().collider;

}


void AutoController::init() 
{
	if (!entity->hasComponent<TransformComponent>())
	{
		std::cout << "ERROR: Need a transformComponent before creating an AutoController" << std::endl;
	}

	else
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	if (!entity->hasComponent<SpriteComponent>())
	{
		std::cout << "ERROR: Need a SpriteComponent before creating an AutoController" << std::endl;
	}
	else
	{
		sprite = &entity->getComponent<SpriteComponent>();
	}

	if (!entity->hasComponent<CharacterCollider>())
	{
		std::cout << "ERROR: Need a ColliderComponent before creating an AutoController" << std::endl;
	}

	collider = entity->getComponent<CharacterCollider>().collider;
	colliderX = collider.x;
	originPos = transform->position.x;
	transform->speed = 6;

}

void AutoController::Attack()
{
	transform->velocity.x = 0;
	if (transform->isAttacking == false)
	{
		transform->isAttacking = true;

		sprite->timeA = SDL_GetTicks() / sprite->aSpeed;
		transform->velocity.x = 0;
		stayIdle(0, 0);
	}


}

void AutoController::stayIdle(int x, int y)

{

	transform->velocity.x *= x;
	transform->velocity.y *= y;

	sprite->Play("Idle");
	sprite->lastAction = "Idle";

}


void AutoController::update()
{
	//std::cout << entity->getComponent<CharacterCollider>().collider.x << std::endl;

	if (!transform->isbeingAnimated && !transform->isAttacking)
	{

		if (NearTarget())
		{
			//	AttackingMode();

			AttackingMode();

			//sprite->timeA = SDL_GetTicks() / sprite->aSpeed;
		}
		/*else if (!transform->isbeingAnimated && !transform->isAttacking)
		{
			PatrollingMode();
		}*/

		else
		{
			PatrollingMode();

		}


	}

	else
	{
		transform->velocity.x = 0;
	}












}

void AutoController::PatrollingMode()
{
	entity->getComponent<CharacterCollider>().collider.w = collider.w;
	transform->speed = 3;
	//	entity->getComponent<CharacterCollider>().collider.x = colliderX;

	switch (sprite->flip)
	{

	case SDL_FLIP_NONE:

		transform->velocity.x = -1;
		sprite->Play("Walk");
		sprite->lastAction = "Walk";

		if (transform->position.x <= originPos - movementDist)
		{
			sprite->flip = SDL_FLIP_HORIZONTAL;
		}

		break;

	case SDL_FLIP_HORIZONTAL:
		transform->velocity.x = 1;
		sprite->Play("Walk");
		sprite->lastAction = "Walk";

		if (transform->position.x >= originPos + movementDist)
		{
			sprite->flip = SDL_FLIP_NONE;
		}

		break;

	default:
		break;
	}


}

void AutoController::AttackingMode()
{
	transform->speed = 6;
	//	stayIdle(0, 0);

		//entity->getComponent<CharacterCollider>().dstRect.x = collider.x -80-Game::camera.x;
	entity->getComponent<CharacterCollider>().collider.w = collider.w;
	int targetXPos = target->getComponent<TransformComponent>().centeredXPos;
	//int targetXPos = target->getComponent<CharacterCollider>().centeredXPos;

	int entityXPos = transform->centeredXPos;
	//int entityXPos = entity->getComponent<CharacterCollider>().centeredXPos;

	//std::cout << transform->position.x << "  " << entityXPos << std::endl;


	//std::cout << targetXPos << std::endl;
	if (targetXPos > entityXPos + 100)
	{


		transform->velocity.x = 1;
		sprite->flip = SDL_FLIP_HORIZONTAL;
		//std::cout << "at right" << std::endl;
	}




	else if (targetXPos < entityXPos - 100)
	{

		transform->velocity.x = -1;
		sprite->flip = SDL_FLIP_NONE;
	}

	else
	{

		//std::cout << "at center" << std::endl;
		transform->velocity.x = 0;
		Attack();
		entity->getComponent<CharacterCollider>().collider.w = collider.w + 150;

		//return;

	}
	sprite->Play("Walk");
	sprite->lastAction = "Walk";

}
bool AutoController::NearTarget()
{
	int targetXPos = target->getComponent<TransformComponent>().position.x;

	if (originPos + movementDist >= targetXPos && originPos - movementDist <= targetXPos)
	{
		return true;
	}

	return false;
}


int AutoController::GetStrength()
{
	return hitStrength;
}




